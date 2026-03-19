#include "main.h"
#include "Autons.h"
#include "Motion.h"
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
        leftSide = &L;     // Use the 3-motor groups
        rightSide = &R;
    } else {
        leftSide = &Left;  // Use the 2-motor groups
        rightSide = &Right;
    }
}

// Drivetrain / LemLib config
lemlib::Drivetrain drivetrain(&L, &R, 12.25, lemlib::Omniwheel::NEW_325, 480, 0);
lemlib::Drivetrain drivetrain2(&Left, &Right, 12.25, lemlib::Omniwheel::NEW_325, 480, 0);
lemlib::Drivetrain drivetrain3(&DrivetrainL, &DrivetrainR, 12.25, lemlib::Omniwheel::NEW_325, 480, 0);
// Odom wheels
lemlib::TrackingWheel horizontal_tracking_wheel(&Xaxis, 2, 1.8);
lemlib::TrackingWheel vertical_tracking_wheel(&Yaxis, 2, 0.8);

// Odom sensors
lemlib::OdomSensors sensors(&vertical_tracking_wheel, nullptr, &horizontal_tracking_wheel, nullptr, &inertial19);

//pid constants for auton
lemlib::ControllerSettings lateral_controller(10, 0, 55, 0, 1,100, 3, 500,
                                              0); // slew-80


lemlib::ControllerSettings angular_controller(4.15, 0, 34, 0, 2, 20, 10, 200,
                                              0);

// lemlib::ControllerSettings lateral_controller(8, 0, 40, 0, 0, 0, 0, 0,
//                                               0);

// lemlib::ControllerSettings angular_controller(2.15, 0.0001, 15, 15, 0, 0, 0, 0,
//                                               0);


// Chassis
lemlib::Chassis chassis(drivetrain, lateral_controller, angular_controller, sensors);
lemlib::Chassis chassis2(drivetrain2, lateral_controller, angular_controller, sensors);
lemlib::Chassis chassis3(drivetrain3, lateral_controller, angular_controller, sensors);


// ----------------- INITIALIZE -----------------
void initialize() {
    pros::lcd::initialize();

    // Sensors reset
    // inertial19.reset();
    // while(inertial19.is_calibrating()) pros::delay(10);
    // Xaxis.reset_position();
    // Yaxis.reset_position();
    chassis.calibrate(true);
    DrivetrainL.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
    DrivetrainR.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
    chassis.setPose(0,0,0);


}

// ----------------- DISABLED -----------------
void disabled() {}

// ----------------- COMPETITION INIT -----------------
void competition_initialize() {}

// ----------------- AUTONOMOUS -----------------
void autonomous() {
 new pros::Task(debug);
 //driveM6(24, 2000); // drive forward 36 inches with a timeout of 3 seconds, kP of 7 and kD of 3
 RightWing();
 //LeftWing();
 //splitRight();
 //splitLeft();
 //skills();
 //test();
 //SAWP();


}

// ----------------- OPERATOR CONTROL -----------------
void opcontrol() {
  new pros::Task(debug);
  new pros::Task(DriveTrainControls);
  new pros::Task(OutakeControls);
  new pros::Task(IntakeRevControls);
  //new pros::Task(MidControls);
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