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
  pros::lcd::print(1, "Auton: SAWP");
  pros::lcd::print(2, "IMU ready: %d", !inertial19.is_calibrating());

}

// ----------------- AUTONOMOUS -----------------
void autonomous() { 


  // ////////////////right wing 7/////////////
  // Intake2.move(127);
  // chassis.moveToPoint(13, 27, 1000, {.forwards = true}, true);
  // pros::delay(800);
  // Loader.extend(); 
  // chassis.waitUntilDone();
  // chassis.turnToHeading(150, 900, {.maxSpeed=127}, false);
  // chassis.moveToPoint(38, 3, 1500,{.forwards = true}, false); 
  // chassis.turnToHeading(180, 900, {.maxSpeed = 127}, false);
  // chassis.moveToPoint(38, -20, 1100,{.forwards = true}, false);
  // pros::delay(500);///match loader
  // chassis.moveToPoint(39.5, 22, 1500,{.forwards = false}, false);
  // chassis.cancelMotion();
  // pto.setDriveMode(DRIVE_4_MOTOR);
  // DrivePTO.move(127); // outakes into far long goal 3 blocks
  // pros::delay(1500);
  // DrivePTO.brake();
  // pto.setDriveMode(DRIVE_6_MOTOR);
  // Loader.retract();
  // chassis.moveToPoint(38.5, 3, 1000, {.forwards = true}, false);
  // chassis.turnToHeading(135, 1000);
  // chassis.moveToPoint(28, 18, 1000,{.forwards = false}, false);
  // chassis.turnToHeading(180, 1000);
  // chassis.moveToPoint(32, 33, 1000,{.forwards = false}, false);
  // chassis.turnToHeading(150, 1000);


  /////////////////////left 4 wing//////////////////////

  Intake2.move(127);
  chassis.moveToPoint(-13, 27, 1000, {.forwards = true}, true);
  pros::delay(650);
  Loader.extend();
  chassis.waitUntilDone();
  chassis.turnToHeading(-150, 900, {.maxSpeed=127}, false);
  chassis.moveToPoint(-37, 3, 1500,{.forwards = true}, false);  
  chassis.turnToHeading(-180, 900);
  chassis.moveToPoint(-37, 23, 1500,{.forwards = false}, false);
  chassis.cancelMotion();
  pto.setDriveMode(DRIVE_4_MOTOR);
  DrivePTO.move(127); // outakes into far long goal 3 blocks
  pros::delay(900);
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);
  Loader.retract();
  chassis.swingToHeading(215, lemlib::DriveSide::RIGHT, 1000);
  chassis.moveToPoint(-48, -3, 1500,{.forwards = true
  }, false);  
  chassis.turnToHeading(-180, 900);
  chassis.moveToPoint(-48, 38, 1000, {.forwards = false}, false);
  chassis.turnToHeading(135, 1000);






  ////////////////////////left wing 7/////////////////
  // Intake2.move(127);
  // chassis.moveToPoint(-13, 27, 1000, {.forwards = true}, false);
  // Loader.extend();
  // chassis.turnToHeading(-150, 900, {.maxSpeed=127}, false);
  // chassis.moveToPoint(-39, 3, 1500,{.forwards = true}, false);  
  // chassis.turnToHeading(-180, 900);
  // chassis.moveToPoint(-35, -20, 1100,{.forwards = true}, false);
  // pros::delay(800);///match loader
  // chassis.moveToPoint(-35, 23, 1500,{.forwards = false}, false);
  // chassis.turnToHeading(180, 1000);
  // chassis.cancelMotion();
  // pto.setDriveMode(DRIVE_4_MOTOR);
  // DrivePTO.move(127); // outakes into far long goal 3 blocks













  ////////////////////////SOLO AUTON WIN POINT//////////////////////////////
//   Intake2.move(127);
//   chassis.moveToPoint(0, -40, 1000, {.forwards = false}, false);
//   Loader.extend();
//   pros::delay(100);
//   chassis.turnToHeading(270, 1000, {.maxSpeed = 127}, false);


// /////////////////////// MATCH LOADER//////////////////////////////////

//   chassis.moveToPoint(-17, -42, 1000); /// into match loader
//   pros::Task::delay(800);
//   chassis.moveToPoint(25, -39, 1500, {.forwards = false}, false); /// long goal
  

//   ///////////////////////////LONG GOAL 4 BLOCKS//////////////////////////////
//   chassis.cancelMotion();
//   pto.setDriveMode(DRIVE_4_MOTOR);
//   DrivePTO.move(127); // outakes into far long goal 3 blocks
//   pros::delay(1000);
//   DrivePTO.brake();
//   pto.setDriveMode(DRIVE_6_MOTOR);
//   Loader.retract();


//   ///////////////////////////FIRST 3 BLOCKS//////////////////////////////


// /////TUNE THE MOTION CHAINING PART, JUST ADDED IT NOW, NOT TUNED/////



//   chassis.swingToPoint(31, -16, lemlib::DriveSide::RIGHT, 1500, {.maxSpeed = 127});
//   chassis.moveToPoint(31, -16, 1000, {.forwards = true, .maxSpeed = 127}, true); // 3 bloacks
//   pros::delay(700);
//   Loader.extend();
//   chassis.waitUntilDone();
//   chassis.turnToHeading(0, 1000, {.maxSpeed = 127}, false);
//   Loader.retract();




// /////////////////////////////////////////////FROM HERE ON OUT THE CODE IT IS NOT TUNED/////////////////////////////////////


//   // ///////////////////////////SECOND 3 BLOCKS//////////////////////////////
//    chassis.moveToPoint(28, 29, 1500, {.forwards = true}, true);
//   pros::delay(800);
//   Loader.extend();
//   chassis.waitUntilDone();
//   Intake2.brake();
//   chassis.turnToHeading(315, 1000, {.maxSpeed = 127}, false);



  // //////////////////////////MID GOAL 2 BLOCKS//////////////////////////////
  // chassis.moveToPoint(40, 14, 1200, {.forwards = false},
  //                     false); 
  // chassis.cancelMotion();
  // pto.setDriveMode(DRIVE_4_MOTOR);
  // Intake2.move(-127);
  // pros::delay(300);
  // Midgoal.retract();
  // IntakePTO.move(85);
  // DrivePTO.move(-85); // outakes into mid goal 2-3 blocks
  // pros::delay(500);  
  // IntakePTO.brake();  DrivePTO.brake();
  // pto.setDriveMode(DRIVE_6_MOTOR);
  // Midgoal.extend();
  // ///////////////////SECOND LOADER /////////////////////////
  // chassis.moveToPoint(4, 51, 2000, {.forwards = true}, false);
  // IntakePTO.move(127);
  // chassis.turnToHeading(270, 1000, {.maxSpeed = 127}, false);
  // chassis.moveToPoint(-17, 49, 1000); /// into match loader
  // pros::Task::delay(800);


  // ///////////SECOND LONG GOAL 4 BLOCKS///////////////////////
  // chassis.moveToPoint(25, 49, 1500, {.forwards = false}, false); /// long goal
  // chassis.cancelMotion();
  // pto.setDriveMode(DRIVE_4_MOTOR);
  // DrivePTO.move(127); // outakes into far long goal 3 blocks
  // pros::delay(1000);
  // DrivePTO.brake();
  // pto.setDriveMode(DRIVE_6_MOTOR);
  // Loader.retract();

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