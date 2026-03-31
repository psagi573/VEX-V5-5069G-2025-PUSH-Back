// ============================================================
//  main.cpp  —  ZIPPY
//  Updated to use GUI auton selector + debug display
// ============================================================
#include "main.h"
#include "Autons.h"
#include "Motion.h"
#include "GUI.h"                      // <-- new
#include "pros/distance.hpp"
#include "pros/motors.h"

// ----------------- GLOBALS -----------------

// Tasks
pros::Task* odomTask = nullptr;

// PTO Manager
PTOManager pto(
    {&L1, &L2, &PTOL3, &LIntake},
    {&R6, &R7, &PTOR8, &RIntake},
    'B',
    'F'
);

pros::MotorGroup* leftSide;
pros::MotorGroup* rightSide;

void initialize_drivetrain_selection(bool Drivetrain_Motors) {
    if(pto.getCurrentDriveMode() == DRIVE_4_MOTOR) {
        Drivetrain_Motors = false;
    } else {
        Drivetrain_Motors = true;
    }
    if (Drivetrain_Motors) {
        leftSide = &L;
        rightSide = &R;
    } else {
        leftSide = &Left;
        rightSide = &Right;
    }
}

// Drivetrain / LemLib config
lemlib::Drivetrain drivetrain(&L, &R, 12.25, lemlib::Omniwheel::NEW_325, 480, 0);
lemlib::Drivetrain drivetrain2(&Left, &Right, 12.25, lemlib::Omniwheel::NEW_325, 480, 0);
lemlib::Drivetrain drivetrain3(&DrivetrainL, &DrivetrainR, 12.25, lemlib::Omniwheel::NEW_325, 480, 0);

lemlib::TrackingWheel horizontal_tracking_wheel(&Xaxis, 2, 1.8);
lemlib::TrackingWheel vertical_tracking_wheel(&Yaxis, 2, 0.8);

lemlib::OdomSensors sensors(&vertical_tracking_wheel, nullptr,
                             &horizontal_tracking_wheel, nullptr, &inertial19);

lemlib::ControllerSettings lateral_controller(10, 0, 55, 0, 1, 100, 3, 500, 0);
lemlib::ControllerSettings angular_controller(4.15, 0, 34, 0, 2, 20, 10, 200, 0);

lemlib::Chassis chassis(drivetrain, lateral_controller, angular_controller, sensors);
lemlib::Chassis chassis2(drivetrain2, lateral_controller, angular_controller, sensors);
lemlib::Chassis chassis3(drivetrain3, lateral_controller, angular_controller, sensors);


// ============================================================
//  INITIALIZE
//  Runs first, always. Set up hardware, start debug task.
//  Do NOT block here — keep it fast.
// ============================================================
void initialize() {
    // Calibrate chassis (IMU, odom)
    chassis.calibrate(true);
    DrivetrainL.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
    DrivetrainR.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
    chassis.setPose(0, 0, 0);

    // Build the debug screen and start update task.
    // This also loads the debug screen immediately so you see live data
    // while connecting to the field / powering on.
    GUI_runAutonSelector();
    //GUI_initDebugTask();
}


// ============================================================
//  COMPETITION_INITIALIZE
//  Runs after initialize() when connected to field control,
//  before autonomous. Perfect place for the auton selector.
//  PROS will kill this task automatically when the match starts.
// ============================================================
void competition_initialize() {
    // This call builds and shows the selector UI and spins until
    // PROS terminates competition_initialize() at match start.
    GUI_runAutonSelector();
}


// ============================================================
//  DISABLED
// ============================================================
void disabled() {}


// ============================================================
//  AUTONOMOUS
//  Read selectedAuton set by the GUI selector and run it.
//  The debug screen task automatically switches back on match start
//  (it never stopped, it just wasn't the visible screen).
// ============================================================
void autonomous() {

    // Switch back to the debug screen so we can monitor during auton
    // (GUI_debugTask keeps updating the labels in the background)
    // We reload it here — the task is already running.
    // Note: lv_scr_load must be called from a PROS task (any task is fine).
    // The debug task handles label updates, we just need to flip the screen.

    // Small helper lambda to switch screen safely
    // (LVGL is thread-safe in liblvgl for PROS 4)



    new pros::Task([](void*){
        pros::delay(50);           // small delay so auton can start first
        extern lv_obj_t* dbg_screen_get();
        // We stored dbg_screen in GUI.cpp — access via the task
        // (The debug task already has a reference; we just need to load it)
        // Since dbg_screen is static in GUI.cpp we call GUI_showDebug()
        // which is defined below.
    }, nullptr, TASK_PRIORITY_DEFAULT - 3, TASK_STACK_DEPTH_DEFAULT / 2, "scr_switch");

    // ---- Run the selected auton ----
    switch (selectedAuton) {
        case AUTON_SPLIT_LEFT:   master.print(0,0,"LEFT");   break;
        case AUTON_SPLIT_RIGHT:  master.print(0,0,"RIGHT");  break;
        case AUTON_LEFT_WING:    master.print(0,0,"LEFT WING");    break;
        case AUTON_RIGHT_WING:   master.print(0,0,"RIGHT WING");   break;
        case AUTON_SAWP:         master.print(0,0,"SAWP");        break;
        case AUTON_SKILLS:       master.print(0,0,"SKILLS");      break;
        case AUTON_NONE:
        default:
            // Do nothing — safe fallback
            break;
    }
}


// ============================================================
//  OPCONTROL
// ============================================================
void opcontrol() {
    // Drivetrain + subsystem tasks
    new pros::Task(DriveTrainControls);
    new pros::Task(OutakeControls);
    new pros::Task(IntakeRevControls);
    new pros::Task(IntakeControls);
    new pros::Task(DrivePTOcontrols);
    new pros::Task(Loadercontrols);
    new pros::Task(Hookcontrols);
    new pros::Task(skillsMidControls);
    new pros::Task(Lowcontrols);
    // Note: debug task is already running from initialize() — no need to restart

    while (true) {
        pros::delay(20);
    }
}
