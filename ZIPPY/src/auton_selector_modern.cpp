#include "auton_selector_modern.h"
#include "main.h"
#include "liblvgl/lvgl.h"
#include "liblvgl/lv_api_map_v8.h"

// UI elements
lv_obj_t *currentAutonNameLabel;
lv_obj_t *currentAutonScoreLabel;

static auton_group_t selectedAutonGroup = NONE;

static int selectedAutonIndex = 0;

// Internal lists
static std::vector<auton_descriptor_t> redRightList;
static std::vector<auton_descriptor_t> redLeftList;
static std::vector<auton_descriptor_t> blueRightList;
static std::vector<auton_descriptor_t> blueLeftList;
static auton_descriptor_t skillsDescriptor;

// forward declarations
static void updateAutonInfo();

// Button callbacks
static void redRightAction(lv_event_t *e)
{
    selectedAutonGroup = RED_RIGHT;
    selectedAutonIndex = 0;
    updateAutonInfo();
}
static void redLeftAction(lv_event_t *e)
{
    selectedAutonGroup = RED_LEFT;
    selectedAutonIndex = 0;
    updateAutonInfo();
}
static void blueRightAction(lv_event_t *e)
{
    selectedAutonGroup = BLUE_RIGHT;
    selectedAutonIndex = 0;
    updateAutonInfo();
}
static void blueLeftAction(lv_event_t *e)
{
    selectedAutonGroup = BLUE_LEFT;
    selectedAutonIndex = 0;
    updateAutonInfo();
}
static void skillsAction(lv_event_t *e)
{
    selectedAutonGroup = SKILLS;
    selectedAutonIndex = 0;
    updateAutonInfo();
}

static void backAction(lv_event_t *e)
{
    lv_obj_clean(lv_scr_act());
    modernAutonSelector(redRightList, redLeftList, blueRightList, blueLeftList, skillsDescriptor);
}

static void confirmAction(lv_event_t *e)
{
    switch (selectedAutonGroup)
    {
    case RED_RIGHT:
        selected_auton_global = {RED_RIGHT, redRightList[selectedAutonIndex]};
        break;
    case RED_LEFT:
        selected_auton_global = {RED_LEFT, redLeftList[selectedAutonIndex]};
        break;
    case BLUE_RIGHT:
        selected_auton_global = {BLUE_RIGHT, blueRightList[selectedAutonIndex]};
        break;
    case BLUE_LEFT:
        selected_auton_global = {BLUE_LEFT, blueLeftList[selectedAutonIndex]};
        break;
    case SKILLS:
        selected_auton_global = {SKILLS, skillsDescriptor};
        break;
    default:
        selected_auton_global = {NONE, {""}};
        break;
    }
    lv_obj_clean(lv_scr_act());
}

// Update auton info display
static void updateAutonInfo()
{
    auton_descriptor_t desc;
    switch (selectedAutonGroup)
    {
    case RED_RIGHT:
        desc = redRightList[selectedAutonIndex];
        break;
    case RED_LEFT:
        desc = redLeftList[selectedAutonIndex];
        break;
    case BLUE_RIGHT:
        desc = blueRightList[selectedAutonIndex];
        break;
    case BLUE_LEFT:
        desc = blueLeftList[selectedAutonIndex];
        break;
    case SKILLS:
        desc = skillsDescriptor;
        break;
    default:
        desc = {""};
        break;
    }
    lv_label_set_text(currentAutonNameLabel, desc.name.c_str());
    lv_label_set_text(currentAutonScoreLabel, desc.score.c_str());
}

// Main selector function
void modernAutonSelector(
    const std::vector<auton_descriptor_t> &red_right,
    const std::vector<auton_descriptor_t> &red_left,
    const std::vector<auton_descriptor_t> &blue_right,
    const std::vector<auton_descriptor_t> &blue_left,
    const auton_descriptor_t &skills)
{
    redRightList = red_right;
    redLeftList = red_left;
    blueRightList = blue_right;
    blueLeftList = blue_left;
    skillsDescriptor = skills;

    lv_obj_clean(lv_scr_act());

    // Title
    lv_obj_t *title = lv_label_create(lv_scr_act());
    lv_label_set_text(title, "Select Auton");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_24, LV_PART_MAIN);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 10);

    // Buttons
    auto createBtn = [](lv_obj_t *parent, const char *text, lv_color_t color, lv_event_cb_t cb, int x, int y)
    {
        lv_obj_t *btn = lv_btn_create(parent);
        lv_obj_set_size(btn, 120, 80);
        lv_obj_align(btn, LV_ALIGN_CENTER, x, y);
        lv_obj_add_event_cb(btn, cb, LV_EVENT_CLICKED, nullptr);
        lv_obj_set_style_radius(btn, 10, LV_PART_MAIN);
        lv_obj_set_style_bg_color(btn, color, LV_PART_MAIN);
        lv_obj_t *lbl = lv_label_create(btn);
        lv_label_set_text(lbl, text);
        lv_obj_center(lbl);
        return btn;
    };

    createBtn(lv_scr_act(), "Red Right", lv_palette_main(LV_PALETTE_RED), redRightAction, -120, -40);
    createBtn(lv_scr_act(), "Red Left", lv_palette_main(LV_PALETTE_RED), redLeftAction, -120, 40);
    createBtn(lv_scr_act(), "Blue Right", lv_palette_main(LV_PALETTE_BLUE), blueRightAction, 120, -40);
    createBtn(lv_scr_act(), "Blue Left", lv_palette_main(LV_PALETTE_BLUE), blueLeftAction, 120, 40);
    createBtn(lv_scr_act(), "Skills", lv_palette_main(LV_PALETTE_YELLOW), skillsAction, 0, 120);

    // Back & Confirm
    lv_obj_t *backBtn = lv_btn_create(lv_scr_act());
    lv_obj_set_size(backBtn, 80, 40);
    lv_obj_align(backBtn, LV_ALIGN_BOTTOM_LEFT, 10, -10);
    lv_obj_add_event_cb(backBtn, backAction, LV_EVENT_CLICKED, nullptr);
    lv_obj_t *backLabel = lv_label_create(backBtn);
    lv_label_set_text(backLabel, LV_SYMBOL_LEFT " Back");
    lv_obj_center(backLabel);

    lv_obj_t *confirmBtn = lv_btn_create(lv_scr_act());
    lv_obj_set_size(confirmBtn, 100, 40);
    lv_obj_align(confirmBtn, LV_ALIGN_BOTTOM_RIGHT, -10, -10);
    lv_obj_add_event_cb(confirmBtn, confirmAction, LV_EVENT_CLICKED, nullptr);
    lv_obj_t *confirmLabel = lv_label_create(confirmBtn);
    lv_label_set_text(confirmLabel, LV_SYMBOL_OK " Confirm");
    lv_obj_center(confirmLabel);

    // Info labels
    currentAutonNameLabel = lv_label_create(lv_scr_act());
    lv_obj_set_style_text_font(currentAutonNameLabel, &lv_font_montserrat_20, LV_PART_MAIN);
    lv_label_set_text(currentAutonNameLabel, "None Selected");
    lv_obj_align(currentAutonNameLabel, LV_ALIGN_TOP_MID, 0, 60);

    currentAutonScoreLabel = lv_label_create(lv_scr_act());
    lv_obj_set_style_text_font(currentAutonScoreLabel, &lv_font_montserrat_18, LV_PART_MAIN);
    lv_label_set_text(currentAutonScoreLabel, "0 points");
    lv_obj_align(currentAutonScoreLabel, LV_ALIGN_TOP_MID, 0, 90);
}
