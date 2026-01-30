#include "main.h"
#include "Autons.h"
#include "Motion.h"
#include "lemlib/chassis/chassis.hpp"
#include "pros/distance.hpp"
#include "pros/motors.h"
#include "pros/rtos.h"
#include "pros/rtos.hpp"
#include <utility>

// ----------------- GLOBALS -----------------

// Tasks
pros::Task *odomTask = nullptr;
// PTO Manager
PTOManager pto({&L1, &L2, &PTOL3, &LIntake}, {&R6, &R7, &PTOR8, &RIntake}, 'B',
               'A'

);

// Drivetrain / LemLib config
lemlib::Drivetrain drivetrain(&L, &R, 12.25, lemlib::Omniwheel::NEW_325, 480,
                              0.15853);

// Odom wheels
lemlib::TrackingWheel horizontal_tracking_wheel(&Xaxis, 2, 1.7);
lemlib::TrackingWheel vertical_tracking_wheel(&Yaxis, 2, 0.5);

// Odom sensors
lemlib::OdomSensors sensors(&vertical_tracking_wheel, nullptr,
                            &horizontal_tracking_wheel, nullptr,
                            &inertial19); // 6, 5

// PID settings
lemlib::ControllerSettings lateral_controller(4.8, 0, 25, 0, 0, 0, 0, 0,
                                              100); // slew-80

lemlib::ControllerSettings angular_controller(2.15, 0.0001, 15, 15, 0, 0, 0, 0,
                                              0);

// Chassis
lemlib::Chassis chassis(drivetrain, lateral_controller, angular_controller,
                        sensors);

// ----------------- ODOM DEBUG TASK -----------------
void odomDebug(void *) {
  master.clear();
  while (true) {
    lemlib::Pose pose = chassis.getPose();
    pros::lcd::print(1, "X: %.2f", pose.x);
    pros::lcd::print(2, "Y: %.2f", pose.y);
    pros::lcd::print(3, "H: %.2f", pose.theta);
    pros::lcd::print(4, "X true: %.2f", Xaxis.get_position());
    pros::lcd::print(5, "Y true: %.2f", Yaxis.get_position());

    master.print(0, 0, "X:%5.1f Y:%5.1f", pose.x, pose.y);
    master.print(1, 0, "H:%5.1f", pose.theta);
    master.print(2, 0, "X true:%5.1f Y true:%5.1f", Xaxis.get_position(),
                 Yaxis.get_position());
    pros::delay(50);
  }
}

// ----------------- INITIALIZE -----------------
void initialize() {
  pros::lcd::initialize();
  chassis.calibrate(true);

  // Sensors reset
  //   inertial19.reset();
  //   pros::lcd::print(1, "Calibrating IMU...");
  //   while (inertial19.is_calibrating()) {
  //     pros::delay(10);
  // }
  //   pros::lcd::print(1, "IMU Done");

  //   Xaxis.reset_position();
  //   Yaxis.reset_position();
  DrivetrainL.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
  DrivetrainR.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
  chassis.setPose(0, 0, 0);
  // Start Odom debug task
  odomTask = new pros::Task(odomDebug);
}

// ----------------- DISABLED -----------------
void disabled() {}

// ----------------- COMPETITION INIT -----------------
void competition_initialize() {
    pros::lcd::initialize();
  chassis.calibrate(true);
  DrivetrainL.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
  DrivetrainR.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
  chassis.setPose(0, 0, 0);
  
  // Start Odom debug task
  odomTask = new pros::Task(odomDebug);

}

// ----------------- AUTONOMOUS -----------------
void autonomous() { 
  ////////////////////////SOLO AUTON WIN POINT//////////////////////////////
  SAWP(); 
}

// ----------------- OPERATOR CONTROL -----------------
void opcontrol() {
  new pros::Task(DriveTrainControls);
  new pros::Task(OutakeControls);
  new pros::Task(IntakeRevControls);
  new pros::Task(MidControls);
  new pros::Task(IntakeControls);
  new pros::Task(DrivePTOcontrols);
  new pros::Task(Loadercontrols);
  new pros::Task(Hookcontrols);
  new pros::Task(skillsMidControls);
  while (true) {

    pros::delay(20);
  }
}