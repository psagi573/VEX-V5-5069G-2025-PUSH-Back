#pragma once
#include "main.h"

// ============================================================
//  GUI.h  —  Auton Selector + Debug Display for ZIPPY
//  LVGL 8.3  (liblvgl template, PROS 4)
// ============================================================

// -------------------------------------------------------
//  Auton IDs  —  add/remove entries here only
//  (matching string goes in GUI.cpp autonList[])
// -------------------------------------------------------
enum AutonomousID {
    AUTON_NONE        = 0,
    AUTON_SPLIT_LEFT  = 1,
    AUTON_SPLIT_RIGHT = 2,
    AUTON_LEFT_WING   = 3,
    AUTON_RIGHT_WING  = 4,
    AUTON_SAWP        = 5,
    AUTON_SKILLS      = 6,
};

// Global selected auton (read in autonomous())
extern volatile int selectedAuton;

// -------------------------------------------------------
//  Public interface
// -------------------------------------------------------

// Call once inside initialize() — sets up the debug screen task
void GUI_initDebugTask();

// Call inside competition_initialize() — blocks until match starts,
// then switches to the debug overlay
void GUI_runAutonSelector();

// Lightweight debug screen refresh (runs as a task)
void GUI_debugTask(void*);
