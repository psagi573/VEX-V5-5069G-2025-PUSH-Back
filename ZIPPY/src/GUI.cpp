#include "GUI.h"
#include "Autons.h"
#include "main.h"
#include "liblvgl/lvgl.h"

// ============================================================
//  GUI.cpp  —  Auton Selector + Debug for ZIPPY
//  LVGL 9.2  (liblvgl, PROS 4 / kernel 4.2.1)
// ============================================================

// ------------------ COLOR HELPER ------------------
static inline lv_color_t C(uint8_t r, uint8_t g, uint8_t b) {
    return lv_color_make(r, g, b);
}

// ------------------ COLORS ------------------
#define CLR_BG       C(13,  13,  13)
#define CLR_TEXT     C(200, 200, 200)
#define CLR_ACCENT   C(0,   212, 255)
#define CLR_WHITE    C(255, 255, 255)
#define CLR_UNSEL    C(50,  50,  75)
#define CLR_GREEN    C(0,   200, 100)
#define CLR_YELLOW   C(255, 215, 0)
#define CLR_RED      C(255, 64,  64)
#define CLR_PANEL    C(20,  20,  45)
#define CLR_ARROW    C(30,  30,  60)

// ------------------ AUTON LIST ------------------
struct AutonEntry {
    AutonomousID id;
    const char*  name;
    const char*  desc;
    lv_color_t   color;
};

static const AutonEntry autonList[] = {
    {AUTON_NONE,        "DO NOTHING",   "Safe fallback",      C(80,  80,  80)},
    {AUTON_SPLIT_LEFT,  "SPLIT LEFT",   "Left side split",    C(30,  120, 200)},
    {AUTON_SPLIT_RIGHT, "SPLIT RIGHT",  "Right side split",   C(30,  120, 200)},
    {AUTON_LEFT_WING,   "LEFT WING",    "Wing push left",     C(160, 50,  200)},
    {AUTON_RIGHT_WING,  "RIGHT WING",   "Wing push right",    C(160, 50,  200)},
    {AUTON_SAWP,        "SAWP",         "Full SAWP routine",  C(200, 140, 0)},
    {AUTON_SKILLS,      "SKILLS",       "Programming skills", C(200, 50,  50)},
};
static const int AUTON_COUNT = sizeof(autonList) / sizeof(autonList[0]);

// ---- Pagination constants ----
#define AUTONS_PER_FIRST_PAGE  4
#define AUTONS_PER_MID_PAGE    3
#define AUTONS_PER_LAST_PAGE   4

// ------------------ GLOBALS ------------------
volatile int selectedAuton = AUTON_RIGHT_WING;

static pros::Task* debugTask  = nullptr;
static int         currentPage = 0;

static lv_obj_t* rp_name = nullptr;
static lv_obj_t* rp_desc = nullptr;
static lv_obj_t* rp_id   = nullptr;

static lv_obj_t *lbl_x, *lbl_y, *lbl_h, *lbl_auton, *lbl_bat, *lbl_pto;

static lv_obj_t* leftColumn = nullptr;

// Layout constants
static const int SW     = 480;
static const int SH     = 272;
static const int TOP    = 29;
static const int LEFT_X = 6;
static const int LEFT_W = 210;
static const int BTN_H  = 36;
static const int GAP    = 4;

// ------------------ HELPERS ------------------
static lv_obj_t* make_label(lv_obj_t* parent, const char* text,
                             int x, int y,
                             lv_color_t col, const lv_font_t* font) {
    lv_obj_t* l = lv_label_create(parent);
    lv_label_set_text(l, text);
    lv_obj_set_pos(l, x, y);
    lv_obj_set_style_text_color(l, col, 0);
    lv_obj_set_style_text_font(l, font, 0);
    lv_obj_set_style_bg_opa(l, LV_OPA_TRANSP, 0);
    return l;
}

static lv_obj_t* make_panel(lv_obj_t* parent,
                             int x, int y, int w, int h,
                             lv_color_t bg) {
    lv_obj_t* p = lv_obj_create(parent);
    lv_obj_set_size(p, w, h);
    lv_obj_set_pos(p, x, y);
    lv_obj_set_style_bg_color(p, bg, 0);
    lv_obj_set_style_bg_opa(p, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(p, 0, 0);
    lv_obj_set_style_pad_all(p, 0, 0);
    lv_obj_set_style_radius(p, 0, 0);
    lv_obj_set_scrollbar_mode(p, LV_SCROLLBAR_MODE_OFF);
    lv_obj_remove_flag(p, LV_OBJ_FLAG_SCROLLABLE);
    return p;
}

static void update_right_panel() {
    if (!rp_name || !rp_desc || !rp_id) return;
    for (int i = 0; i < AUTON_COUNT; i++) {
        if (autonList[i].id == (AutonomousID)selectedAuton) {
            lv_label_set_text(rp_name, autonList[i].name);
            lv_label_set_text(rp_desc, autonList[i].desc);
            char buf[16];
            snprintf(buf, sizeof(buf), "ID: %d", (int)autonList[i].id);
            lv_label_set_text(rp_id, buf);
            return;
        }
    }
}

// ------------------ FORWARD DECLARATION ------------------
static void rebuild_left_column();

// ------------------ CALLBACKS ------------------
static void auton_btn_cb(lv_event_t* e) {
    int id = (int)(intptr_t)lv_event_get_user_data(e);
    selectedAuton = id;
    update_right_panel();
    rebuild_left_column();
}

static void up_cb(lv_event_t*) {
    if (currentPage > 0) {
        currentPage--;
        rebuild_left_column();
    }
}

static void down_cb(lv_event_t*) {
    int startIndex = (currentPage == 0) ? 0
        : AUTONS_PER_FIRST_PAGE + (currentPage - 1) * AUTONS_PER_MID_PAGE;
    int slots = (currentPage == 0) ? AUTONS_PER_FIRST_PAGE : AUTONS_PER_MID_PAGE;
    int endIndex = startIndex + slots;
    if (endIndex < AUTON_COUNT) {
        currentPage++;
        rebuild_left_column();
    }
}

static void test_btn_cb(lv_event_t*) {
    new pros::Task([](void*) {
        autonomous();
    }, nullptr, TASK_PRIORITY_DEFAULT + 1, 0x8000, "test_auton");
}

// ------------------ BUTTON BUILDERS ------------------
static lv_obj_t* make_auton_btn(lv_obj_t* parent, int slotY, int autonIndex) {
    const AutonEntry& entry = autonList[autonIndex];
    bool isSel = ((AutonomousID)selectedAuton == entry.id);

    lv_obj_t* btn = lv_obj_create(parent);
    lv_obj_set_size(btn, LEFT_W, BTN_H);
    lv_obj_set_pos(btn, 0, slotY);
    lv_obj_set_style_bg_color(btn, isSel ? entry.color : CLR_UNSEL, 0);
    lv_obj_set_style_bg_opa(btn, LV_OPA_COVER, 0);
    lv_obj_set_style_border_color(btn, isSel ? CLR_ACCENT : C(70, 70, 100), 0);
    lv_obj_set_style_border_width(btn, isSel ? 2 : 1, 0);
    lv_obj_set_style_radius(btn, 6, 0);
    lv_obj_set_style_pad_all(btn, 4, 0);
    lv_obj_set_style_bg_color(btn, C(0, 160, 200), LV_STATE_PRESSED);
    lv_obj_set_scrollbar_mode(btn, LV_SCROLLBAR_MODE_OFF);
    lv_obj_remove_flag(btn, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(btn, LV_OBJ_FLAG_CLICKABLE);

    lv_obj_t* lbl = lv_label_create(btn);
    lv_label_set_text(lbl, entry.name);
    lv_obj_set_style_text_font(lbl, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(lbl, isSel ? CLR_WHITE : CLR_TEXT, 0);
    lv_obj_align(lbl, LV_ALIGN_CENTER, 0, 0);

    lv_obj_add_event_cb(btn, auton_btn_cb, LV_EVENT_CLICKED,
                        (void*)(intptr_t)entry.id);
    return btn;
}

static lv_obj_t* make_arrow_btn(lv_obj_t* parent, int slotY,
                                 bool isUp, lv_event_cb_t cb) {
    lv_obj_t* btn = lv_obj_create(parent);
    lv_obj_set_size(btn, LEFT_W, BTN_H);
    lv_obj_set_pos(btn, 0, slotY);
    lv_obj_set_style_bg_color(btn, CLR_ARROW, 0);
    lv_obj_set_style_bg_opa(btn, LV_OPA_COVER, 0);
    lv_obj_set_style_border_color(btn, C(80, 80, 120), 0);
    lv_obj_set_style_border_width(btn, 1, 0);
    lv_obj_set_style_radius(btn, 6, 0);
    lv_obj_set_style_pad_all(btn, 4, 0);
    lv_obj_set_style_bg_color(btn, C(60, 60, 100), LV_STATE_PRESSED);
    lv_obj_set_scrollbar_mode(btn, LV_SCROLLBAR_MODE_OFF);
    lv_obj_remove_flag(btn, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(btn, LV_OBJ_FLAG_CLICKABLE);

    lv_obj_t* lbl = lv_label_create(btn);
    lv_label_set_text(lbl, isUp ? LV_SYMBOL_UP : LV_SYMBOL_DOWN);
    lv_obj_set_style_text_font(lbl, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(lbl, CLR_ACCENT, 0);
    lv_obj_align(lbl, LV_ALIGN_CENTER, 0, 0);

    lv_obj_add_event_cb(btn, cb, LV_EVENT_CLICKED, nullptr);
    return btn;
}

// ------------------ REBUILD LEFT COLUMN ------------------
static void rebuild_left_column() {
    if (!leftColumn) return;
    lv_obj_clean(leftColumn);

    int startIndex = (currentPage == 0) ? 0
        : AUTONS_PER_FIRST_PAGE + (currentPage - 1) * AUTONS_PER_MID_PAGE;

    bool hasUp     = (currentPage > 0);
    int  autonSlots = hasUp ? AUTONS_PER_MID_PAGE : AUTONS_PER_FIRST_PAGE;
    int  endIndex   = startIndex + autonSlots;
    if (endIndex > AUTON_COUNT) endIndex = AUTON_COUNT;
    bool hasDown   = (endIndex < AUTON_COUNT);

    // Last page: no down arrow, can fit one extra auton row
    if (hasUp && !hasDown) {
        int extra = startIndex + AUTONS_PER_LAST_PAGE;
        if (extra > AUTON_COUNT) extra = AUTON_COUNT;
        endIndex = extra;
    }

    int slot = 0;
    auto slotY = [&](int s) { return s * (BTN_H + GAP); };

    if (hasUp)   { make_arrow_btn(leftColumn, slotY(slot), true,  up_cb);   slot++; }
    for (int i = startIndex; i < endIndex; i++) { make_auton_btn(leftColumn, slotY(slot), i); slot++; }
    if (hasDown) { make_arrow_btn(leftColumn, slotY(slot), false, down_cb); }
}

// ==================== SELECTOR SCREEN ====================
static lv_obj_t* build_selector() {
    lv_obj_t* scr = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(scr, CLR_BG, 0);
    lv_obj_set_style_bg_opa(scr, LV_OPA_COVER, 0);
    lv_obj_set_style_pad_all(scr, 0, 0);
    lv_obj_set_style_border_width(scr, 0, 0);
    lv_obj_set_scrollbar_mode(scr, LV_SCROLLBAR_MODE_OFF);
    lv_obj_remove_flag(scr, LV_OBJ_FLAG_SCROLLABLE);

    // Title bar
    lv_obj_t* titleBar = make_panel(scr, 0, 0, SW, 26, C(0, 55, 90));
    lv_obj_t* titleLbl = lv_label_create(titleBar);
    lv_label_set_text(titleLbl, "ZIPPY  |  SELECT AUTONOMOUS  |  5069G");
    lv_obj_set_style_text_color(titleLbl, CLR_ACCENT, 0);
    lv_obj_set_style_text_font(titleLbl, &lv_font_montserrat_12, 0);
    lv_obj_align(titleLbl, LV_ALIGN_CENTER, 0, 0);

    const int RIGHT_X = LEFT_X + LEFT_W + 8;
    const int RIGHT_W = SW - RIGHT_X - 6;
    const int RIGHT_H = SH - TOP - 6;

    // Left column container
    leftColumn = lv_obj_create(scr);
    lv_obj_set_size(leftColumn, LEFT_W, SH - TOP - 6);
    lv_obj_set_pos(leftColumn, LEFT_X, TOP);
    lv_obj_set_style_bg_opa(leftColumn, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(leftColumn, 0, 0);
    lv_obj_set_style_pad_all(leftColumn, 0, 0);
    lv_obj_set_style_radius(leftColumn, 0, 0);
    lv_obj_set_scrollbar_mode(leftColumn, LV_SCROLLBAR_MODE_OFF);
    lv_obj_remove_flag(leftColumn, LV_OBJ_FLAG_SCROLLABLE);

    currentPage = 0;
    rebuild_left_column();

    // Right info panel
    lv_obj_t* rp = lv_obj_create(scr);
    lv_obj_set_size(rp, RIGHT_W, RIGHT_H);
    lv_obj_set_pos(rp, RIGHT_X, TOP);
    lv_obj_set_style_bg_color(rp, CLR_PANEL, 0);
    lv_obj_set_style_bg_opa(rp, LV_OPA_COVER, 0);
    lv_obj_set_style_border_color(rp, C(0, 100, 160), 0);
    lv_obj_set_style_border_width(rp, 1, 0);
    lv_obj_set_style_radius(rp, 6, 0);
    lv_obj_set_style_pad_all(rp, 10, 0);
    lv_obj_set_scrollbar_mode(rp, LV_SCROLLBAR_MODE_OFF);
    lv_obj_remove_flag(rp, LV_OBJ_FLAG_SCROLLABLE);

    make_label(rp, "SELECTED AUTON",  0,   0, CLR_ACCENT,     &lv_font_montserrat_12);
    make_label(rp, "──────────────",  0,  16, C(60, 60, 100), &lv_font_montserrat_12);

    rp_name = make_label(rp, "",  0,  34, CLR_WHITE,          &lv_font_montserrat_14);
    rp_desc = make_label(rp, "",  0,  56, CLR_TEXT,           &lv_font_montserrat_12);
    rp_id   = make_label(rp, "",  0,  74, C(120, 120, 160),   &lv_font_montserrat_12);

    make_label(rp, "──────────────",  0,  94, C(60, 60, 100), &lv_font_montserrat_12);
    make_label(rp, "TEAM  5069G",     0, 110, CLR_ACCENT,     &lv_font_montserrat_12);
    make_label(rp, "ZIPPY",           0, 128, CLR_WHITE,      &lv_font_montserrat_12);

    // Test button
    lv_obj_t* testBtn = lv_obj_create(rp);
    lv_obj_set_size(testBtn, RIGHT_W - 20, 32);
    lv_obj_set_pos(testBtn, 0, RIGHT_H - 80);
    lv_obj_set_style_bg_color(testBtn, C(0, 140, 0), 0);
    lv_obj_set_style_bg_opa(testBtn, LV_OPA_COVER, 0);
    lv_obj_set_style_bg_color(testBtn, C(0, 100, 0), LV_STATE_PRESSED);
    lv_obj_set_style_border_width(testBtn, 0, 0);
    lv_obj_set_style_radius(testBtn, 5, 0);
    lv_obj_set_style_pad_all(testBtn, 4, 0);
    lv_obj_set_scrollbar_mode(testBtn, LV_SCROLLBAR_MODE_OFF);
    lv_obj_remove_flag(testBtn, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(testBtn, LV_OBJ_FLAG_CLICKABLE);

    lv_obj_t* testLbl = lv_label_create(testBtn);
    lv_label_set_text(testLbl, "RUN AUTON (TEST)");
    lv_obj_set_style_text_font(testLbl, &lv_font_montserrat_12, 0);
    lv_obj_set_style_text_color(testLbl, CLR_WHITE, 0);
    lv_obj_align(testLbl, LV_ALIGN_CENTER, 0, 0);

    lv_obj_add_event_cb(testBtn, test_btn_cb, LV_EVENT_CLICKED, nullptr);

    update_right_panel();
    return scr;
}

// ==================== DEBUG SCREEN ====================
static lv_obj_t* build_debug() {
    lv_obj_t* scr = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(scr, CLR_BG, 0);
    lv_obj_set_style_bg_opa(scr, LV_OPA_COVER, 0);
    lv_obj_set_style_pad_all(scr, 0, 0);
    lv_obj_set_style_border_width(scr, 0, 0);
    lv_obj_set_scrollbar_mode(scr, LV_SCROLLBAR_MODE_OFF);
    lv_obj_remove_flag(scr, LV_OBJ_FLAG_SCROLLABLE);

    make_label(scr, "ZIPPY DEBUG", 8,   5, CLR_ACCENT, &lv_font_montserrat_12);
    lbl_x     = make_label(scr, "X: ---",     8,  26, CLR_WHITE,  &lv_font_montserrat_12);
    lbl_y     = make_label(scr, "Y: ---",     8,  44, CLR_WHITE,  &lv_font_montserrat_12);
    lbl_h     = make_label(scr, "H: ---",     8,  62, CLR_WHITE,  &lv_font_montserrat_12);
    lbl_auton = make_label(scr, "Auton: ---", 8,  86, CLR_ACCENT, &lv_font_montserrat_12);
    lbl_pto   = make_label(scr, "PTO: ---",   8, 106, CLR_GREEN,  &lv_font_montserrat_12);
    lbl_bat   = make_label(scr, "Bat: ---",   8, 126, CLR_GREEN,  &lv_font_montserrat_12);
    return scr;
}

// ==================== DEBUG TASK ====================
void GUI_debugTask(void*) {
    char buf[64];
    while (true) {
        auto pose = chassis.getPose();

        snprintf(buf, sizeof(buf), "X: %.1f", pose.x);   lv_label_set_text(lbl_x, buf);
        snprintf(buf, sizeof(buf), "Y: %.1f", pose.y);   lv_label_set_text(lbl_y, buf);
        snprintf(buf, sizeof(buf), "H: %.1f", pose.theta); lv_label_set_text(lbl_h, buf);

        for (int i = 0; i < AUTON_COUNT; i++) {
            if (autonList[i].id == (AutonomousID)selectedAuton) {
                snprintf(buf, sizeof(buf), "Auton: %s", autonList[i].name);
                lv_label_set_text(lbl_auton, buf);
                break;
            }
        }

        const char* ptoStr =
            (pto.getCurrentDriveMode() == DRIVE_4_MOTOR) ? "4-Motor" :
            (pto.getCurrentDriveMode() == DRIVE_8_MOTOR) ? "8-Motor" : "6-Motor";
        snprintf(buf, sizeof(buf), "PTO: %s", ptoStr);
        lv_label_set_text(lbl_pto, buf);

        int batt = pros::battery::get_capacity();
        lv_color_t bc = (batt > 60) ? CLR_GREEN : (batt > 30 ? CLR_YELLOW : CLR_RED);
        lv_obj_set_style_text_color(lbl_bat, bc, 0);
        snprintf(buf, sizeof(buf), "Bat: %d%%", batt);
        lv_label_set_text(lbl_bat, buf);

        pros::delay(200);
    }
}

// ==================== PUBLIC API ====================
void GUI_initDebugTask() {
    lv_obj_t* scr = build_debug();
    lv_screen_load(scr);
    if (!debugTask)
        debugTask = new pros::Task(GUI_debugTask);
}

void GUI_runAutonSelector() {
    currentPage = 0;
    rp_name = rp_desc = rp_id = nullptr;
    leftColumn = nullptr;

    lv_obj_t* scr = build_selector();
    lv_screen_load(scr);
    // Returns immediately — LVGL handles touch on its own task
}

void GUI_showDebugScreen() {
    GUI_initDebugTask();  // safe to call multiple times — checks if task already running
}