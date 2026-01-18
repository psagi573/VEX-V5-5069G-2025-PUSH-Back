#pragma once
#include "main.h"

// ----------------- AUTON DESCRIPTOR -----------------
struct auton_descriptor_t {
    std::string name;         // Name displayed in selector
    std::string score;        // Predicted score (optional)
    void (*callback)();       // Function pointer to auton routine
};

// Enum for auton groups
enum auton_group_t { RED_RIGHT, RED_LEFT, BLUE_RIGHT, BLUE_LEFT, SKILLS, NONE };

// Selected auton struct
struct selected_auton_t {
    auton_group_t group = NONE;
    int index = 0;
};

// ----------------- AUTON DECLARATIONS -----------------
void runAuton(const auton_descriptor_t& auton);

// Example auton routines
void autonRedRight1();
void autonRedLeft1();
void autonBlueRight1();
void autonBlueLeft1();
void autonSkills();

// Utility
void waitSec(double seconds);
