#include "Autons.h"
#include "Motion.h"
#include "PTO.h"
#include "main.h"
#include "pros/rtos.h"
#include "pros/rtos.hpp"
#include <algorithm>
#include <cmath>

void skills() {
  Intake2.move(127);
  chassis.moveToPoint(0, -36, 1000, {.forwards = false}, true);
  pros::delay(450);
  Loader.extend();
  chassis.waitUntilDone();
  chassis.turnToHeading(270, 1000, {.maxSpeed = 127}, false);

  /////////////////////// MATCH LOADER//////////////////////////////////
  chassis.moveToPoint(-12.5, -38, 1000, {.forwards = true},
                      false); /// into match loader
  pros::Task::delay(1000);
  chassis.moveToPoint(-12.5, -39, 800, {.forwards = true},
                      false); /// into match loader
  pros::delay(300);
  // chassis.moveToPoint(0, -38, 1500, {.forwards = false}, false);
  // Intake2.brake();
  // chassis.turnToHeading(315, 1000);
  chassis.moveToPoint(
      13, -54.5, 1500,
      {.forwards = false, .minSpeed = 90, .earlyExitRange = 9.5}, false);

  ///////////////////////////ACROSS FIELD//////////////////////////////
  chassis.turnToHeading(270, 1000, {.maxSpeed = 127}, false);
  Loader.retract();
  Intake2.brake();
  chassis.moveToPoint(73, -53.5, 1800, {.forwards = false}, false);
  chassis.moveToPoint(88, -35, 1000, {.forwards = false}, false);
  chassis.turnToHeading(90, 1000, {.maxSpeed = 127}, false);
  chassis.moveToPoint(58, -35, 1100, {.forwards = false}, false); //-31.5
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

  chassis.moveToPoint(98, yhere, 1500, {.forwards = true, .maxSpeed = 90},
                      false); //////AT LONG GOAL SIDE //-31
  chassis.moveToPoint(102, yhere, 1500, {.forwards = true},
                      false); //////AT LONG GOAL SIDE //-31
  pros::delay(1500);
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

  /////////////////////GOING TO THE NEXT MATCH LOADER
  /// 3//////////////////////////
  chassis.moveToPoint(82, yhere, 1500, {.forwards = true}, false);
  chassis.turnToHeading(180, 1500, {.maxSpeed = 127}, false);
  chassis.moveToPoint(81, 61, 2500, {.forwards = false}, false);
  chassis.turnToHeading(90, 1000, {.maxSpeed = 127}, false);
  yhere = chassis.getPose().y;
  Intake2.move(127);
  chassis.moveToPoint(101, yhere - 3, 1000, {.forwards = true, .maxSpeed = 75},
                      false); ////into match loader
  pros::delay(800);
  chassis.moveToPoint(104, yhere - 3, 700, {.forwards = true},
                      false); ////into match loader
  pros::delay(8000);

  //////////////////////////SET UP TO OTHER SIDE//////////////////////////////
  chassis.moveToPoint(80, 75, 1000, {.forwards = false}, false);
  chassis.turnToHeading(90, 1000, {.maxSpeed = 127}, false);
  Loader.retract();
  chassis.moveToPoint(10, 77, 1000, {.forwards = false}, false);
  chassis.moveToPoint(8, 52, 2500, {.forwards = false}, false);
  chassis.turnToHeading(270, 1000, {.maxSpeed = 127}, false);
  chassis.moveToPoint(35.5, yhere - 10, 1500, {.forwards = false},
                      false); ////long goal side
  Loader.extend();
  // yhere = chassis.getPose().y;

  // /////////////////////////SCORE LONG GOAL 6
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
  chassis.moveToPoint(-8, yhere, 1500, {.forwards = true},
                      false); ////long goal side
  pros::delay(500);
  chassis.moveToPoint(-11, yhere, 1500, {.forwards = true},
                      false); ////long goal side
  pros::delay(1000);
  chassis.moveToPoint(30, yhere, 1500, {.forwards = false},
                      false); ////long goal side

  ////////////////////Score////////////////
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