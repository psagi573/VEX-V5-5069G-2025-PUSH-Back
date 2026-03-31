#include "GUI.h"
#include "Autons.h"
#include "main.h"
#include "liblvgl/lvgl.h"

// ------------------ SAFE COLOR WRAPPER ------------------
static inline lv_color_t C(uint8_t r, uint8_t g, uint8_t b) {
    return lv_color_make(r, g, b);
}

// ------------------ AUTON LIST ------------------
struct AutonEntry {
    AutonomousID id;
    const char* name;
    const char* desc;
    lv_color_t color;
};

static const AutonEntry autonList[] = {
    {AUTON_NONE, "DO NOTHING", "Safe fallback", C(80,80,80)},
    {AUTON_SPLIT_LEFT, "SPLIT LEFT", "Left side auton", C(30,120,200)},
    {AUTON_SPLIT_RIGHT, "SPLIT RIGHT", "Right side auton", C(30,120,200)},
    {AUTON_LEFT_WING, "LEFT WING", "Wing push", C(180,60,200)},
    {AUTON_RIGHT_WING, "RIGHT WING", "Wing push", C(180,60,200)},
    {AUTON_SAWP, "SAWP", "Full SAWP", C(200,140,0)},
    {AUTON_SKILLS, "SKILLS", "Programming skills", C(200,50,50)},
};

static const int AUTON_COUNT = sizeof(autonList)/sizeof(autonList[0]);

// ------------------ GLOBAL ------------------
volatile int selectedAuton = AUTON_RIGHT_WING;
static pros::Task* debugTask = nullptr;

// ------------------ COLORS ------------------
#define CLR_BG C(13,13,13)
#define CLR_PANEL C(26,26,46)
#define CLR_ACCENT C(22,33,62)
#define CLR_TEXT C(224,224,224)
#define CLR_SELECTED C(0,212,255)
#define CLR_UNSEL C(42,42,62)
#define CLR_WHITE C(255,255,255)
#define CLR_GREEN C(0,255,136)
#define CLR_YELLOW C(255,215,0)
#define CLR_RED C(255,64,64)
#define CLR_GREY C(128,128,128)

// ------------------ DEBUG LABELS ------------------
static lv_obj_t *lbl_x,*lbl_y,*lbl_h,*lbl_auton,*lbl_bat,*lbl_pto;

// ------------------ HELPERS ------------------
static lv_obj_t* label(lv_obj_t* p,const char* t,int x,int y,lv_color_t c,const lv_font_t* f){
    lv_obj_t* l=lv_label_create(p);
    lv_label_set_text(l,t);
    lv_obj_set_pos(l,x,y);
    lv_obj_set_style_text_color(l,c,0);
    lv_obj_set_style_text_font(l,f,0);
    return l;
}

static lv_color_t tempColor(double t){
    if(t>55) return CLR_RED;
    if(t>40) return CLR_YELLOW;
    return CLR_GREEN;
}

// ------------------ DEBUG SCREEN ------------------
static lv_obj_t* build_debug(){
    lv_obj_t* scr = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(scr, CLR_BG, 0);

    label(scr,"ZIPPY DEBUG",10,5,CLR_SELECTED,&lv_font_montserrat_12);

    lbl_x = label(scr,"X:",10,30,CLR_WHITE,&lv_font_montserrat_12);
    lbl_y = label(scr,"Y:",10,50,CLR_WHITE,&lv_font_montserrat_12);
    lbl_h = label(scr,"H:",10,70,CLR_WHITE,&lv_font_montserrat_12);
    lbl_auton = label(scr,"Auton:",10,100,CLR_SELECTED,&lv_font_montserrat_12);
    lbl_pto = label(scr,"PTO:",10,130,CLR_GREEN,&lv_font_montserrat_12);
    lbl_bat = label(scr,"Bat:",10,160,CLR_GREEN,&lv_font_montserrat_12);

    return scr;
}

// ------------------ DEBUG TASK ------------------
void GUI_debugTask(void*){
    char buf[64];

    while(true){
        auto pose = chassis.getPose();

        snprintf(buf,64,"X: %.1f",pose.x);
        lv_label_set_text(lbl_x,buf);

        snprintf(buf,64,"Y: %.1f",pose.y);
        lv_label_set_text(lbl_y,buf);

        snprintf(buf,64,"H: %.1f",pose.theta);
        lv_label_set_text(lbl_h,buf);

        snprintf(buf,64,"Auton: %d",selectedAuton);
        lv_label_set_text(lbl_auton,buf);

        int batt = pros::battery::get_capacity();
        snprintf(buf,64,"Bat: %d%%",batt);
        lv_label_set_text(lbl_bat,buf);

        pros::delay(200);
    }
}

// ------------------ BUTTON CALLBACK ------------------
static void btn_cb(lv_event_t* e){
    int id = (int)lv_event_get_user_data(e);
    selectedAuton = id;
}

// ------------------ SELECTOR ------------------
static lv_obj_t* build_selector(){
    lv_obj_t* scr = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(scr, CLR_BG, 0);

    label(scr,"SELECT AUTON",10,5,CLR_SELECTED,&lv_font_montserrat_12);

    for(int i=0;i<AUTON_COUNT;i++){
        lv_obj_t* btn = lv_win_create(scr);
        lv_obj_set_size(btn,200,30);
        lv_obj_set_pos(btn,10,30 + i*35);

        lv_obj_add_event_cb(btn,btn_cb,LV_EVENT_CLICKED,(void*)autonList[i].id);

        lv_obj_t* l = lv_label_create(btn);
        lv_label_set_text(l,autonList[i].name);
        lv_obj_center(l);
    }

    return scr;
}

// ------------------ PUBLIC API ------------------
void GUI_initDebugTask(){
    lv_obj_t* scr = build_debug();
    lv_screen_load(scr);

    if(!debugTask){
        debugTask = new pros::Task(GUI_debugTask);
    }
}

void GUI_runAutonSelector(){
    lv_obj_t* scr = build_selector();
    lv_screen_load(scr);

    while(true) pros::delay(20);
}