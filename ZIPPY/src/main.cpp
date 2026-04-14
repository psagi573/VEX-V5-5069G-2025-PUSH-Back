// ============================================================
//  main.cpp  —  ZIPPY
// ============================================================
#include "main.h"
#include "Autons.h"
#include "Motion.h"
#include "GUI.h"
#include "pros/distance.hpp"
#include "pros/motors.h"

// ----------------- GLOBALS -----------------

pros::Task* odomTask = nullptr;

PTOManager pto(
    {&L1, &L2, &PTOL3, &LIntake},
    {&R6, &R7, &PTOR8, &RIntake},
    'B',
    'F'
);

pros::MotorGroup* leftSide;
pros::MotorGroup* rightSide;

void initialize_drivetrain_selection(bool Drivetrain_Motors) {
    if (pto.getCurrentDriveMode() == DRIVE_4_MOTOR) {
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

// ----------------- LEMLIB CONFIG -----------------

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
//  INITIALIZE — runs once on power-on, must not block
// ============================================================
void initialize() {
    chassis.calibrate(true);  // blocks ~3s while IMU calibrates — normal on real robot
    DrivetrainL.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
    DrivetrainR.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
    chassis.setPose(0, 0, 0);
    // FIX: removed the redundant GUI_initDebugTask() call that was here before.
    // GUI_runAutonSelector() already shows a screen; loading the debug screen
    // immediately after and then switching back caused lbl_* to be built before
    // the selector was even visible, and the debug task was updating labels on
    // the wrong screen. The selector is now the only thing shown on power-on.
    GUI_runAutonSelector();   // builds selector screen and returns immediately
}


// ============================================================
//  COMPETITION_INITIALIZE — runs when connected to field,
//  before autonomous. PROS kills this when match starts.
// ============================================================
void competition_initialize() {
    // FIX: GUI_runAutonSelector() now guards itself — if the selector is
    // already on screen (which it is after initialize()), this is a no-op.
    // No mid-touch teardown, no lost selection.
    GUI_runAutonSelector();
}


// ============================================================
//  DISABLED
// ============================================================
void disabled() {}


// ============================================================
//  AUTONOMOUS — called by field control OR test button
// ============================================================
void autonomous() {
    GUI_showDebugScreen();  // flip to cached debug screen when auton starts
    switch ((AutonomousID)selectedAuton) {
        case AUTON_SPLIT_LEFT:   splitLeft();   break;
        case AUTON_SPLIT_RIGHT:  splitRight();  break;
        case AUTON_LEFT_WING:    LeftWing();    break;
        case AUTON_RIGHT_WING:   RightWing();   break;
        case AUTON_SAWP:         SAWP();        break;
        case AUTON_SKILLS:       skills();      break;
        case AUTON_NONE:
        default:                               break;
    }
}


// ============================================================
//  OPCONTROL
// ============================================================
void opcontrol() {
    GUI_showDebugScreen();
    new pros::Task(DriveTrainControls);
    new pros::Task(OutakeControls);
    new pros::Task(IntakeRevControls);
    new pros::Task(IntakeControls);
    new pros::Task(DrivePTOcontrols);
    new pros::Task(Loadercontrols);
    new pros::Task(Hookcontrols);
    new pros::Task(skillsMidControls);
    new pros::Task(Lowcontrols);

    while (true) {
        pros::delay(20);
    }
}