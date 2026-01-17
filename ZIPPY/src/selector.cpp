/*#include "main.h"
#include "selector.h"

#define scr lv_scr_act()


int auton_selection = 0;
const int total_autons = 4;
const char* auton_names[] = {"Red Front", "Red Back", "Blue Front", "Blue Back"};

lv_obj_t * labels[total_autons];
lv_obj_t * selection_rect;
bool confirmed = false;

void init_selector() {
    // LVGL 5.3 uses lv_scr_act() to get the active screen
    lv_obj_t * screen = lv_scr_act(); 

    lv_obj_t * title = lv_label_create(screen, NULL);
    lv_label_set_text(title, "Select Auton (D-Pad)");
    lv_obj_align(title, NULL, LV_ALIGN_IN_TOP_MID, 0, 10);

    // Create the Blue Selection Rectangle
    static lv_style_t style_rect;
    lv_style_copy(&style_rect, &lv_style_plain);
    style_rect.body.empty = 1;         
    style_rect.body.border.color = LV_COLOR_BLUE;
    style_rect.body.border.width = 4;
    style_rect.body.radius = 5;

    selection_rect = lv_obj_create(screen, NULL);
    lv_obj_set_size(selection_rect, 200, 40);
    lv_obj_set_style(selection_rect, &style_rect);

    // Create the list of Auton names
    for (int i = 0; i < total_autons; i++) {
        labels[i] = lv_label_create(screen, NULL);
        lv_label_set_text(labels[i], auton_names[i]);
        lv_obj_align(labels[i], NULL, LV_ALIGN_IN_TOP_MID, 0, 60 + (i * 45));
    }
}

void show_map() {
    lv_obj_t * screen = lv_scr_act();
    lv_obj_clean(screen); // This deletes the selection menu

    lv_obj_t * map_label = lv_label_create(screen, NULL);
    lv_label_set_text(map_label, "MAP LOADED");
    lv_obj_align(map_label, NULL, LV_ALIGN_IN_TOP_MID, 0, 10);

    // Draw a visual path (A line representing the robot moving)
    static lv_point_t path_points[] = { {100, 200}, {100, 100}, {200, 100} };
    lv_obj_t * path_line = lv_line_create(screen, NULL);
    lv_line_set_points(path_line, path_points, 3);
    
    static lv_style_t style_line;
    lv_style_copy(&style_line, &lv_style_plain);
    style_line.line.color = LV_COLOR_MAKE(0, 255, 0); // Green path
    style_line.line.width = 5;
    lv_line_set_style(path_line, &style_line);
}*/
