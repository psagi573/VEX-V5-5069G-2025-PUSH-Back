#include "Autons.h"
#include "Motion.h"
#include "PTO.h"
#include "main.h"
#include "pros/rtos.h"
#include "pros/rtos.hpp"
#include <algorithm>
#include <cmath>

void skills(){
  Intake2.move(127);
  chassis.moveToPoint(0, -36, 1000, {.forwards = false}, true);
  pros::delay(450);
  Loader.extend();
  chassis.waitUntilDone();
  chassis.turnToHeading(270, 1000, {.maxSpeed = 127}, false);

  /////////////////////// MATCH LOADER//////////////////////////////////
  chassis.moveToPoint(-12, -39.5, 1000, {.forwards = true, .maxSpeed = 55},
                      false); /// into match loader
  pros::Task::delay(1000);
  chassis.moveToPoint(-13.5, -39.5, 800, {.forwards = true},
                      false); /// into match loader
  pros::delay(300);
  // chassis.moveToPoint(0, -38, 1500, {.forwards = false}, false);
  // Intake2.brake();
  // chassis.turnToHeading(315, 1000);
  chassis.moveToPoint(
      13, -55.5, 1500,
      {.forwards = false, .minSpeed = 90, .earlyExitRange = 9.5}, false);

  ///////////////////////////ACROSS FIELD//////////////////////////////
  chassis.turnToHeading(270, 1000, {.maxSpeed = 127}, false);
  Loader.retract();
  Intake2.brake();
  chassis.moveToPoint(73, -53.5, 1800, {.forwards = false}, false);
  chassis.moveToPoint(88, -37.8, 1000, {.forwards = false}, false);
  chassis.turnToHeading(90, 1000, {.maxSpeed = 127}, false);
  chassis.moveToPoint(58, -34.5, 1100, {.forwards = false}, false); //-31.5
  pros::delay(400);
  float yhere = chassis.getPose().y;
  // chassis.turnToHeading(90, 1000, {.maxSpeed = 127}, false);

  /////////////////////////SCORE LONG GOAL 7
  /// BLOCKS//////////////////////////////
  chassis.cancelMotion();
  Loader.extend();
  pto.setDriveMode(DRIVE_4_MOTOR);
  DrivePTO.move(-127); // outakes into far long goal 3 blocks
  Intake2.move(-127);
  pros::delay(100);
  Intake2.move(127);
  DrivePTO.move(127); // outakes into far long goal 3 blocks
  pros::delay(2500);
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);

  // chassis.setPose(65, -34, 90);

  ///////////////////////////MATCH LOADER 2/////////////////////////////////////
  // chassis.moveToPoint(80, -30, 1500, {.forwards = true, .minSpeed =90,
  // .earlyExitRange = 9.5}, false);//////AT LONG GOAL SIDE
  // chassis.turnToHeading(90, 700, {.maxSpeed =127}, false);

  chassis.moveToPoint(100.5, yhere, 1500, {.forwards = true, .maxSpeed = 70},
                      false); //////AT LONG GOAL SIDE //-31
  chassis.moveToPoint(103, yhere, 1500, {.forwards = true},
                      false); //////AT LONG GOAL SIDE //-31
  pros::delay(500);
  chassis.moveToPoint(64, yhere, 1500, {.forwards = false},
                      false); //////AT LONG GOAL SIDE // -31.5

  /////////////////////////SCORE LONG GOAL 6
  /// BLOCKS//////////////////////////////
  chassis.cancelMotion();
  pto.setDriveMode(DRIVE_4_MOTOR);
  DrivePTO.move(-127); // outakes into far long goal 3 blocks
  Intake2.move(-127);
  pros::delay(100);
  Intake2.move(127);
  DrivePTO.move(127); // outakes into far long goal 3 blocks
  pros::delay(3000);
  DrivePTO.brake();
  Intake2.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);

  /////////////////////GOING TO THE NEXT MATCH LOADER 3
  /// 3//////////////////////////
  chassis.moveToPoint(82, yhere, 1500, {.forwards = true}, false);
  chassis.turnToHeading(190, 1500, {.maxSpeed = 127}, false);
  float xhere = chassis.getPose().x;
  //chassis.moveToPoint(81, 59, 2500, {.forwards = false}, false);
  chassis.moveToPoint(xhere, 60, 2500, {.forwards = false}, false);
  chassis.turnToHeading(90, 1000, {.maxSpeed = 127}, false);
  chassis.moveToPoint(60, 59, 1500, {.forwards = false}, false); 
  yhere = chassis.getPose().y;
  Intake2.move(127);



  ////////////////////Match Loader 3/////////////////////////////
  chassis.moveToPoint(100, yhere-0.5, 1000, {.forwards = true, .maxSpeed = 60},
                      false); ////into match loader
  chassis.moveToPoint(105.5, yhere, 700, {.forwards = true},
                      false); ////into match loader
  pros::delay(2000);

  //////////////////////////SET UP TO OTHER SIDE//////////////////////////////
  chassis.moveToPoint(80, 76.5, 1000, {.forwards = false}, false);
  chassis.turnToHeading(90, 1000, {.maxSpeed = 127}, false);
  Loader.retract();
  chassis.moveToPoint(8, 80.5, 1800, {.forwards = false}, false);
  chassis.moveToPoint(1, 68.5, 1500, {.forwards = false}, false);
  chassis.turnToHeading(270, 1000, {.maxSpeed = 127}, false);
  chassis.moveToPoint(37.5, yhere - 7, 1500, {.forwards = false}, ///// note make the y a numerical value
                      false); ////long goal side
  yhere = chassis.getPose().y;
  Loader.extend();
  // yhere = chassis.getPose().y;

  // /////////////////////////SCORE LONG GOAL 6//////////////////////////////////////
  // BLOCKS//////////////////////////////

  chassis.cancelMotion();
  pto.setDriveMode(DRIVE_4_MOTOR);
  DrivePTO.move(-127); // outakes into far long goal 3 blocks
  Intake2.move(-127);
  pros::delay(100);
  Intake2.move(127);
  DrivePTO.move(127); // outakes into far long goal 3 blocks
  pros::delay(3000);
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);

  // ///////////////////////////MATCH LOADER 4
  // /////////////////////////////////////
  chassis.moveToPoint(-10, yhere+2, 1500, {.forwards = true, .maxSpeed = 65},
                      false); ////long goal side
  pros::delay(500);
  chassis.moveToPoint(-13, yhere, 1500, {.forwards = true},
                      false); ////long goal side
  pros::delay(1000);
  chassis.moveToPoint(37, yhere, 1500, {.forwards = false},
                      false); ////long goal side

  ////////////////////Score////////////////
  Loader.retract();
  chassis.cancelMotion();
  pto.setDriveMode(DRIVE_4_MOTOR);
  DrivePTO.move(-127); // outakes into far long goal 3 blocks
  Intake2.move(-127);
  pros::delay(100);
  Intake2.move(127);
  DrivePTO.move(127); // outakes into far long goal 3 blocks
  pros::delay(3000);
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);

  ////////////////////////////over park barriar//////////////////////////////
  chassis.moveToPoint(28, yhere, 1500, {.forwards = true}, false);
  chassis.moveToPoint(-18, 25, 1500, {.forwards = true}, false);
  Drivetrain.move(127);
  pros::delay(1000);
  Drivetrain.brake();


}

void wingRIGHT() {

  Intake2.move(127);
  chassis.moveToPoint(8, 22, 1000, {.forwards = true}, true);
  pros::delay(550);
  Loader.extend();
  chassis.waitUntilDone();
  chassis.turnToHeading(315, 1000, {.maxSpeed = 127}, false);
  chassis.moveToPoint(
      30, 0, 1000, {.forwards = false, .minSpeed = 90, .earlyExitRange = 5.5},
      true);
  chassis.turnToHeading(180, 1000, {.maxSpeed = 127}, false);
  chassis.moveToPoint(35, 27, 1000, {.forwards = false}, false);
  chassis.cancelMotion();
  pto.setDriveMode(DRIVE_4_MOTOR);
  DrivePTO.move(127); // outakes into far long goal 3 blocks
  pros::delay(900);
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);
  Loader.retract();
  chassis.swingToHeading(20, lemlib::DriveSide::LEFT, 1500, {.maxSpeed = 127});
  chassis.turnToHeading(345, 1000, {.maxSpeed = 127}, false);
  chassis.moveToPoint(40, 49, 1000, {.forwards = false}, false);
  chassis.turnToHeading(15, 1000);
}

void LeftWing() {

  Intake2.move(127);
  chassis.moveToPoint(
      -13, 27, 1000, {.forwards = true, .minSpeed = 90, .earlyExitRange = 10.5},
      true);
  pros::delay(650);
  Loader.extend();
  chassis.waitUntilDone();
  chassis.turnToHeading(-160, 900, {.maxSpeed = 127}, false);

  chassis.moveToPoint(-32, -4, 1500,
                      {.forwards = true, .minSpeed = 90, .earlyExitRange = 9.5},
                      false);
  Intake2.brake();
  chassis.turnToHeading(-180, 900);
  chassis.moveToPoint(
      -32, 18, 1500, {.forwards = false, .minSpeed = 90, .earlyExitRange = 9.5},
      false);
  chassis.moveToPoint(
      -32, 18.5, 600,
      {.forwards = false, .minSpeed = 100, .earlyExitRange = 9.5}, false);
  chassis.cancelMotion();
  pto.setDriveMode(DRIVE_4_MOTOR);
  DrivePTO.move(127); // outakes into far long goal 3 blocks
  Intake2.move(127);
  pros::delay(1100);
  DrivePTO.brake();
  Intake2.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);
  Loader.retract();
  // chassis.swingToHeading(190, lemlib::DriveSide::RIGHT, 1000);
  chassis.moveToPoint(-45, 5, 1500, {.forwards = true}, false);
  chassis.turnToHeading(180, 900);
  chassis.moveToPoint(-42.5, 33, 1000, {.forwards = false}, false);
  chassis.turnToHeading(135, 1000);
}

void RightWing() {

  Intake2.move(127);
  chassis.moveToPoint(
      13, 27, 1000, {.forwards = true, .minSpeed = 90, .earlyExitRange = 10.5},
      true);
  pros::delay(650);
  Loader.extend();
  chassis.waitUntilDone();
  chassis.turnToHeading(160, 900, {.maxSpeed = 127}, false);

  chassis.moveToPoint(32, -4, 1500,
                      {.forwards = true, .minSpeed = 90, .earlyExitRange = 9.5},
                      false);
  Intake2.brake();
  chassis.turnToHeading(180, 900);
  chassis.moveToPoint(
      33, 18, 1500, {.forwards = false, .minSpeed = 90, .earlyExitRange = 9.5},
      false);
  chassis.moveToPoint(
      33, 18.5, 600,
      {.forwards = false, .minSpeed = 100, .earlyExitRange = 9.5}, false);
  chassis.cancelMotion();
  pto.setDriveMode(DRIVE_4_MOTOR);
  DrivePTO.move(127); // outakes into far long goal 3 blocks
  Intake2.move(127);
  pros::delay(1100);
  DrivePTO.brake();
  Intake2.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);
  Loader.retract();
  chassis.moveToPoint(22.5, 3, 1000, {.forwards = true}, false);
  chassis.turnToHeading(180, 1000);
  chassis.moveToPoint(23.5, 33, 1000, {.forwards = false}, false);
  chassis.turnToHeading(150, 1000);

  // Intake2.move(127);
  // chassis.moveToPoint(-8, 22, 1000, {.forwards = true}, true);
  // pros::delay(550);
  // Loader.extend();
  // chassis.waitUntilDone();
  // chassis.turnToHeading(45, 1000, {.maxSpeed=127}, false);
  // chassis.moveToPoint(-30,0, 1000,{.forwards = false, .earlyExitRange = 5.5
  // }, true); chassis.turnToHeading(180, 1000, {.maxSpeed=127}, false);
  // chassis.moveToPoint(-35, 27, 1000,{.forwards = false}, false);
  // chassis.cancelMotion();
  // pto.setDriveMode(DRIVE_4_MOTOR);
  // DrivePTO.move(127); // outakes into far long goal 3 blocks
  // pros::delay(900);
  // DrivePTO.brake();
  // pto.setDriveMode(DRIVE_6_MOTOR);
  // Loader.retract();
  // /////////////////// bro IDKabout this part
  // chassis.swingToHeading(340, lemlib::DriveSide::LEFT, 1500,
  // {.maxSpeed=127}); chassis.turnToHeading(15, 1000, {.maxSpeed=127}, false);
  // chassis.moveToPoint(-40, 49, 1000, {.forwards = false}, false);
  // chassis.turnToHeading(345, 1000);
}

void RightLOW() {
  chassis.moveToPoint(0, -36, 1000, {.forwards = false}, true);
  Intake2.move(127);
  pros::delay(225);
  Loader.extend();
  chassis.waitUntilDone();
  chassis.turnToHeading(270, 1000, {.maxSpeed = 127}, false);

  /////////////////////// MATCH LOADER//////////////////////////////////

  chassis.moveToPoint(-12, -39, 1000, {.maxSpeed = 90}); /// into match loader
  // chassis.turnToHeading(270, 800, {.maxSpeed = 127}, false);
  pros::Task::delay(800);
  chassis.moveToPoint(
      23.5, -37.5, 1100, {.forwards = false},
      false); /// long goal   .minSpeed = 90, .earlyExitRange = 9

  ///////////////////////////LONG GOAL 4 BLOCKS//////////////////////////////
  chassis.cancelMotion();
  pto.setDriveMode(DRIVE_4_MOTOR);
  DrivePTO.move(127); // outakes into far long goal 3 blocks
  pros::delay(2000);
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);
  Loader.retract();

  ///////////////////////////FIRST 3 BLOCKS//////////////////////////////
  // chassis.swingToHeading(22, lemlib::DriveSide::RIGHT, 1500, {.maxSpeed =
  // 127, .minSpeed = 90, .earlyExitRange = 20}); chassis.moveToPoint(37, -19.5,
  // 1500, {.forwards = true, .minSpeed = 90, .earlyExitRange = 9.5}, true); //
  // 3 bloacks pros::delay(600); Loader.extend(); chassis.waitUntilDone();
  // chassis.turnToHeading(45, 1000, {.maxSpeed = 127}, false);
  // Loader.retract();

  // chassis.moveToPoint(43, -5, 1000, {.forwards=true}, false);
  // Intake2.move(-127);
}

void SAWP() {
  ///////////////////////////PUSH//////////////////////////////
  chassis.moveToPoint(0, -36, 1000, {.forwards = false}, true);
  Intake2.move(127);
  pros::delay(225);
  Loader.extend();
  chassis.waitUntilDone();
  chassis.turnToHeading(270, 1000, {.maxSpeed = 127}, false);

  /////////////////////// MATCH LOADER//////////////////////////////////

  chassis.moveToPoint(-12, -39, 1000, {.maxSpeed = 90}); /// into match loader
  // chassis.turnToHeading(270, 800, {.maxSpeed = 127}, false);
  pros::Task::delay(800);
  chassis.moveToPoint(
      23.5, -37.5, 1100, {.forwards = false},
      false); /// long goal   .minSpeed = 90, .earlyExitRange = 9

  ///////////////////////////LONG GOAL 4 BLOCKS//////////////////////////////
  chassis.cancelMotion();
  pto.setDriveMode(DRIVE_4_MOTOR);
  DrivePTO.move(127); // outakes into far long goal 3 blocks
  pros::delay(1100);
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);
  Loader.retract();

  ///////////////////////////FIRST 3 BLOCKS//////////////////////////////
  chassis.swingToHeading(
      22, lemlib::DriveSide::RIGHT, 1500,
      {.maxSpeed = 127, .minSpeed = 90, .earlyExitRange = 20});
  chassis.moveToPoint(37, -19.5, 1500,
                      {.forwards = true, .minSpeed = 90, .earlyExitRange = 8},
                      true); // 3 bloacks
  pros::delay(600);
  Loader.extend();
  chassis.waitUntilDone();
  chassis.turnToHeading(0, 1000, {.maxSpeed = 127}, false);
  Loader.retract();

  ///////////////////////////SECOND 3 BLOCKS//////////////////////////////
  chassis.moveToPoint(36, 20, 1500,
                      {.forwards = true, .minSpeed = 90, .earlyExitRange = 10},
                      true);
  pros::delay(800);
  Loader.extend();
  chassis.waitUntilDone();
  pros::delay(100);
  chassis.turnToHeading(310, 1000, {.maxSpeed = 127}, false);

  //////////////////////////MID GOAL 2 BLOCKS//////////////////////////////
  Intake2.brake();
  chassis.moveToPoint(47, 9, 1200, {.forwards = false}, false);
  chassis.turnToHeading(310, 1000,
                        {.maxSpeed = 127, .minSpeed = 90, .earlyExitRange = 20},
                        false);
  chassis.cancelMotion();
  pto.setDriveMode(DRIVE_4_MOTOR);
  Intake2.move(-127);
  DrivePTO.move(-127);
  Midgoal.extend();
  pros::delay(300);
  IntakePTO.move(80);
  DrivePTO.move(-80);
  pros::delay(1100);
  IntakePTO.brake();
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);
  Loader.retract();

  // chassis.moveToPoint(0, 42, 1000, {.forwards = true, .minSpeed = 90,
  // .earlyExitRange = 9}, true); Midgoal.retract(); pros::delay(300);
  // IntakePTO.move(127);
  // chassis.waitUntilDone();
  // chassis.turnToHeading(270, 1000, {.maxSpeed = 127}, false);

  // ///////////SECOND LONG GOAL 4 BLOCKS///////////////////////
  // chassis.moveToPoint(28, 41.5, 1000, {.forwards = false}, false); /// long
  // goal chassis.cancelMotion(); pto.setDriveMode(DRIVE_4_MOTOR);
  // DrivePTO.move(127); // outakes into far long goal 3 blocks
  // pros::delay(1000);
  // DrivePTO.brake();
  // pto.setDriveMode(DRIVE_6_MOTOR);
  // Loader.retract();
}