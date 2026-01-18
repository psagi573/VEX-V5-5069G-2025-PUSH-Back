#pragma once
#include "main.h"
#include "auton.h"

// LVGL Auton Selector
void modernAutonSelector(
    const std::vector<auton_descriptor_t> &red_right,
    const std::vector<auton_descriptor_t> &red_left,
    const std::vector<auton_descriptor_t> &blue_right,
    const std::vector<auton_descriptor_t> &blue_left,
    const auton_descriptor_t &skills);
