#include "Autons.h"
#include "Motion.h"
#include "PTO.h"
#include "main.h"
#include "pros/rtos.h"
#include "pros/rtos.hpp"
#include <algorithm>
#include <cmath>


void test() {
  L1.move(127);
  pros::delay(3000);
  L1.brake();
  L1.move(-17);
}

void splitLeft() {
  chassis.setPose(0, -6.5, 0);
  IntakePTO.move(127);
  chassis.moveToPose(0, -41, 90, 1100,{.forwards = false, .horizontalDrift = 8, .lead = 0},true);
  pros::delay(300);
  Loader.extend();
  chassis.waitUntilDone();
  chassis.turnToHeading(90, 1000, {}, false);
  double yhere = chassis.getPose().y;
  chassis2.moveToPoint(28, yhere, 800, {.forwards = true},true); // into match loader
  pto.setDriveMode(DRIVE_4_MOTOR);
  chassis.waitUntilDone();
  pros::delay(300);
  chassis2.moveToPoint(-28, yhere+0.5,1000, {.forwards = false}, false);
  DrivePTO.move(127); // outakes into far long goal 3 blocks
  Drivetrain.move(-127);
  Loader.retract();
  pros::delay(1000);
  Drivetrain.brake();
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);
  chassis.turnToHeading(350, 1000,{.maxSpeed = 127}, false);
  float x = chassis.getPose().x;
  chassis.moveToPose(x-7, -12, 315-180, 1300, {.forwards = true,.horizontalDrift = 8, .lead = 0, .minSpeed = 90, .earlyExitRange = 32}, true);
  pros::delay(350);
  Loader.extend();
  chassis.waitUntilDone();
  chassis2.moveToPoint(-37,0, 1200, {.forwards = false}, true);
  pto.setDriveMode(DRIVE_4_MOTOR);
  IntakePTO.move(-35);
  DrivePTO.move(-30);
  pros::delay(200);
  IntakePTO.brake();
  DrivePTO.brake();
  chassis2.waitUntilDone();
  Midgoal.extend();
  DrivePTO.move(-127);
  IntakePTO.move(60);
  pros::delay(1500);
  Loader.retract();
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);
  IntakePTO.brake();
  Midgoal.retract();
  chassis.moveToPoint(-10, yhere+14, 1500, {.forwards = true, .minSpeed = 100, .earlyExitRange = 9.7}, false);
  chassis.turnToHeading(270, 900);
  chassis.moveToPoint(-33, yhere+10,1500, {.forwards = true, .minSpeed = 100, .earlyExitRange = 9}, false);
  chassis.turnToHeading(315, 1000, {.maxSpeed = 110}, false);
}

///Left 4 wing
void LeftWing() {
chassis.setPose(0, -6.5, 0);
  IntakePTO.move(127);
  chassis.moveToPoint(0, -36.5, 1100,{.forwards = false, .minSpeed = 90, .earlyExitRange = 9.5},true);
  pros::delay(300);
  Loader.extend();
  chassis.waitUntilDone();
  chassis.turnToHeading(90, 1000,{.maxSpeed = 127},false);
  double yhere = chassis.getPose().y;
  chassis.moveToPoint(26, yhere, 800, {.forwards = true},false); // into match loader
  //pros::delay(300);
  chassis.moveToPoint(-27.5, yhere-0.5,1000, {.forwards = false}, false);
  pto.setDriveMode(DRIVE_4_MOTOR);
  DrivePTO.move(127); // outakes into far long goal 3 blocks
  Drivetrain.move(-127);
  Loader.retract();
  pros::delay(1000);
  Drivetrain.brake();
  DrivePTO.brake();
  IntakePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);
  chassis.moveToPoint(-14, -30.5, 1500, {.forwards = true, .minSpeed = 100, .earlyExitRange = 4}, false);
  chassis.turnToHeading(270, 900);
  chassis.moveToPoint(-30.5, -32.5,1500, {.forwards = true, .minSpeed = 100, .earlyExitRange = 5}, false);
  chassis.turnToHeading(270+45, 1000, {.maxSpeed = 90}, false);
}
//// right 4 wing
void RightWing() {
  chassis.setPose(0, -6.5, 0);
  IntakePTO.move(127);
  chassis.moveToPoint(0, -35.5, 1100,{.forwards = false, .minSpeed = 90, .earlyExitRange = 9.5},true);
  pros::delay(300);
  Loader.extend();
  chassis.waitUntilDone();
  chassis.turnToHeading(270, 1000,{.maxSpeed = 127},false);
  double yhere = chassis.getPose().y;
  chassis.moveToPoint(-22, yhere, 800, {.forwards = true},false); // into match loader
  //pros::delay(300);
  chassis.moveToPoint(27.5, yhere-1,1000, {.forwards = false}, false);
  pto.setDriveMode(DRIVE_4_MOTOR);
  DrivePTO.move(127); // outakes into far long goal 3 blocks
  Drivetrain.move(-127);
  Loader.retract();
  pros::delay(800);
  Drivetrain.brake();
  DrivePTO.brake();
  IntakePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);
  chassis.moveToPoint(14, -30.5, 1500, {.forwards = true, .minSpeed = 100, .earlyExitRange = 4}, false);
  chassis.turnToHeading(275, 900);
  chassis.moveToPoint(30.5, -32.5,1500, {.forwards = false, .minSpeed = 100, .earlyExitRange = 5}, false);
  chassis.turnToHeading(225, 1000, {.maxSpeed = 90}, false);

  }
// left 7 hood
void left7() {
  chassis.setPose(0,0,0);
  Intake2.move(127);
  chassis.moveToPoint(-12, 24,1500, {.forwards = true, .minSpeed = 90, .earlyExitRange = 10}, true);
  pros::delay(600);
  Loader.extend();
  chassis.waitUntilDone();
  chassis.turnToHeading(225, 1000, {.maxSpeed = 127}, false);
  chassis.moveToPose(-32.5, -5, 180, 1150, {.forwards = true, .horizontalDrift = 8, .lead = 0, .minSpeed = 90, .earlyExitRange = 9}, false);
  chassis.moveToPoint(-32.5, -24, 950, {.forwards = true}, false);
  chassis.moveToPoint(-33, 22,  1000, {.forwards = false}, false);
  pto.setDriveMode(DRIVE_4_MOTOR);
  Intake2.move(-127);
  pros::delay(250);
  Intake2.move(127);
  DrivePTO.move(127); // outakes into far long goal 7 blocks
  Drivetrain.move(-127);
  pros::delay(2000);
  DrivePTO.brake();
  Drivetrain.brake();
  double x = chassis.getPose().x;
  double y = chassis.getPose().y;
  pto.setDriveMode(DRIVE_6_MOTOR);
  Intake2.brake();
  Loader.retract();
  chassis.moveToPoint(x, y-8, 300, {.forwards = true}, false);
  chassis.moveToPoint(x, y, 400, {.forwards = false}, false);
  DrivetrainMain.move(-127);
  
}
///right 7 hood
void right7() {
  chassis.setPose(0,0,0);
  Intake2.move(127);
  chassis.moveToPoint(12, 25,1500, {.forwards = true, .minSpeed = 90, .earlyExitRange = 10}, true);
  pros::delay(600);
  Loader.extend();
  chassis.waitUntilDone();
  chassis.turnToHeading(135, 1000, {.maxSpeed = 127}, false);
  chassis.moveToPose(34, 0, 180, 1150, {.forwards = true, .horizontalDrift = 8, .lead = 0, .minSpeed = 90, .earlyExitRange = 9}, false);
  chassis.moveToPoint(34, -24, 950, {.forwards = true}, false);
  chassis.moveToPoint(34.5, 22,  1000, {.forwards = false, .minSpeed = 90, .earlyExitRange = 9}, false);
  pto.setDriveMode(DRIVE_4_MOTOR);
  // Intake2.move(-127);
  // pros::delay(250);
  // Intake2.move(127);
  DrivePTO.move(127); // outakes into far long goal 7 blocks
  Drivetrain.move(-127);
  pros::delay(1350);
  DrivePTO.brake();
  Drivetrain.brake();
  chassis.setPose(0, 0, chassis.getPose().theta); //temporary make it current theta
  pto.setDriveMode(DRIVE_6_MOTOR);
  Intake2.brake();
  Loader.retract();
  chassis.moveToPoint(0,-6, 700, {.forwards = true, .minSpeed = 90}, false);
  chassis.moveToPoint(0,0, 700, {.forwards = false, .minSpeed = 90}, false);
  DrivetrainMain.move(-127);
}
//left 7 wing
void left7wing() {
  chassis.setPose(0,0,0);
  Intake2.move(127);
  chassis.moveToPose(-8, 24, 225,1500, {.forwards = true, .horizontalDrift = 8, .lead = 0, .minSpeed = 90, .earlyExitRange = 10}, true);
  pros::delay(600);
  Loader.extend();
  chassis.waitUntilDone();
  chassis.moveToPose(-33, -12, 180, 1200, {.forwards = true, .horizontalDrift = 8, .lead = 0, .minSpeed = 90, .earlyExitRange = 9}, false);
  chassis.moveToPoint(-33, -22, 600, {.forwards = true, .minSpeed = 60}, false);
  //pros::delay(350);
  chassis.moveToPoint(-33, 22,  1000, {.forwards = false}, false);
  pto.setDriveMode(DRIVE_4_MOTOR);
  DrivePTO.move(127); // outakes into far long goal 3 blocks
  Drivetrain.move(-127);
  pros::delay(3000);
  Drivetrain.brake();
  DrivePTO.brake();
  Intake2.brake();
  Loader.retract();
  pto.setDriveMode(DRIVE_6_MOTOR);
  chassis.setPose(0,0,180);
  chassis.moveToPoint(11, 14.5, 1000, {.forwards = true, .minSpeed = 90, .earlyExitRange = 9}, false);
  chassis.turnToHeading(180, 900);
  chassis.moveToPoint(11, -9, 500);
}

void SAWP() {
  
  ///////////////////////////PUSH//////////////////////////////
  Intake2.move(127);
  chassis.setPose(0, 5, 0);
  chassis.moveToPoint(0, 18, 1000, {.forwards = true}, true);
  pros::delay(500);
  Intake2.brake();
  chassis.moveToPose(0, -38.5, 270, 1500,{.forwards = false, .horizontalDrift = 8, .lead = 0},true);
  pros::delay(300);
  Loader.extend();
  Intake2.move(127);
  chassis.waitUntilDone();
  double yhere = chassis.getPose().y;

  ////Into Loader/////
  chassis.moveToPoint(-20, yhere, 750, {.forwards = true}, false);

  // Into Long Goal/////
  chassis.moveToPoint(23, yhere-1, 1000, {.forwards = false, .minSpeed =90, .earlyExitRange = 11}, false);
  pto.setDriveMode(DRIVE_4_MOTOR);
  DrivePTO.move(127); // outakes into far long goal 3
  Drivetrain.move(-127);
  Loader.retract();
  pros::delay(1000);
  Drivetrain.brake();
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);
  chassis.setPose(0, 0, chassis.getPose().theta); //temporary make it current theta


  ///////////////////////////ALL MIDDLE BLOCKS//////////////////////////////
  chassis.turnToHeading(0, 1000, {.maxSpeed = 127, .minSpeed = 90, .earlyExitRange = 15}, false);
  
  chassis.moveToPoint(6, 65, 2000, {.forwards = true, .minSpeed = 90, .earlyExitRange = 8}, true);
  pros::delay(250);
  Loader.extend();
  pros::delay(350);
  Loader.retract();
  pros::delay(400);
  Loader.extend();
  chassis.waitUntilDone();
  chassis.turnToHeading(300, 1000, {}, false);


  //moving to long goal 2
  chassis.moveToPose(-12 , 90.5069 ,270, 1100, {.forwards = true, .horizontalDrift = 8, .lead = 0, .minSpeed = 95, .earlyExitRange =8}, false);

  double yhere2 = chassis.getPose().y;
  ///////////SECOND LONG GOAL 4 BLOCKS///////////////////////
  chassis.moveToPoint(3, yhere2, 1000, {.forwards = false, .minSpeed = 100, .earlyExitRange = 6},false);
  pto.setDriveMode(DRIVE_4_MOTOR);
  Intake2.move(-127);
  pros::delay(100);
  Intake2.move(127);
  DrivePTO.move(127); // outakes into far long goal 6 blocks
  pros::delay(300);
  Drivetrain.move(-127);
  pros::delay(1300);
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);
  Drivetrain.brake();
  chassis.setPose(0, 0, chassis.getPose().theta); //temporary make it surrent theta
  
  ///into loader
  chassis.moveToPoint(-32, 0, 1100, {.forwards = true}, false);
  pros::delay(250);



  ////////////////////////////MID GOAL 3 BLOCKS//////////////////////////////
  chassis.moveToPoint(22, -43, 2500, {.forwards = false, .minSpeed = 120, .earlyExitRange = 16},true);
  pros::delay(1000);
  IntakePTO.move(-100);
  chassis.waitUntilDone();
  pto.setDriveMode(DRIVE_4_MOTOR);
  Midgoal.extend();
  IntakePTO.brake();
  pros::delay(200);
  DrivePTO.move(-127);
  pros::delay(200);
  IntakePTO.move(60);
  pros::delay(1700);
  Midgoal.retract();
  IntakePTO.brake();
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);
}


void skills() {
  Intake2.move(127);
  float startx = chassis.getPose().x;
  chassis.moveToPoint(0, -36, 1000, {.forwards = false}, true);
  pros::delay(450);
  Loader.extend();
  chassis.waitUntilDone();
  chassis.turnToHeading(270, 1000, {.maxSpeed = 127}, false);

  /////////////////////// MATCH LOADER//////////////////////////////////
  chassis.moveToPoint(-12, -39.5, 1000, {.forwards = true, .maxSpeed = 55},
                      false); /// into match loader
  pros::Task::delay(950);
  chassis.moveToPoint(-14, -39.5, 800, {.forwards = true},
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
  chassis.moveToPoint(88, -37.5, 1700, {.forwards = false}, false);
  chassis.turnToHeading(90, 1000, {.maxSpeed = 127}, false);
  chassis.moveToPoint(58, -34, 1100, {.forwards = false}, false); //-31.5
  // pros::delay(200);
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
  pros::delay(2200);
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);

  // chassis.setPose(65, -34, 90);

  ///////////////////////////MATCH LOADER 2/////////////////////////////////////
  // chassis.moveToPoint(80, -30, 1500, {.forwards = true, .minSpeed =90,
  // .earlyExitRange = 9.5}, false);//////AT LONG GOAL SIDE
  // chassis.turnToHeading(90, 700, {.maxSpeed =127}, false);

  chassis.moveToPoint(101, yhere + 0.3, 1500,
                      {.forwards = true, .maxSpeed = 60},
                      false); //////AT LONG GOAL SIDE //-31
  chassis.moveToPoint(108.5, yhere, 1500, {.forwards = true, .maxSpeed = 127},
                      false); //////AT LONG GOAL SIDE //-31
  pros::delay(450);
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
  DrivePTO.move(80); // outakes into far long goal 3 blocks
  pros::delay(2500);
  DrivePTO.brake();
  Intake2.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);

  /////////////////////GOING TO THE NEXT MATCH LOADER 3///across field////
  /// 3//////////////////////////
  chassis.moveToPoint(80, yhere, 900, {.forwards = true}, false);
  chassis.turnToHeading(180, 800, {.maxSpeed = 127}, false);
  float xhere = chassis.getPose().x;
  // chassis.moveToPoint(81, 59, 2500, {.forwards = false}, false);
  chassis.moveToPoint(xhere, 60, 2500, {.forwards = false}, false);
  chassis.turnToHeading(90, 1000, {.maxSpeed = 127}, false);
  chassis.moveToPoint(60, 59, 1500, {.forwards = false}, false);
  yhere = chassis.getPose().y;
  Intake2.move(127);

  ////////////////////Match Loader 3/////////////////////////////
  chassis.moveToPoint(106, yhere - 2, 1000, {.forwards = true, .maxSpeed = 55},
                      false); ////into match loader
  chassis.moveToPoint(118, yhere, 1000, {.forwards = true, .maxSpeed = 60},
                      false); ////into match loader
  pros::delay(950);
  chassis.moveToPoint(120, yhere, 800, {.forwards = true},
                      false); ////into match loader

  //////////////////////////SET UP TO OTHER SIDE//////////////////////////////
  chassis.moveToPoint(80, 78, 1100, {.forwards = false}, false);
  chassis.turnToHeading(90, 1000, {.maxSpeed = 127}, false);
  Loader.retract();
  chassis.moveToPoint(15, 83, 1800, {.forwards = false}, false);
  chassis.moveToPoint(startx + 6, 69, 1500, {.forwards = false}, false);
  chassis.turnToHeading(270, 1000, {.maxSpeed = 127}, false);
  chassis.moveToPoint(
      37.5, yhere - 1, 1500,
      {.forwards = false}, ///// note make the y a numerical value
      false);              ////long goal side
  yhere = chassis.getPose().y;
  Loader.extend();
  // yhere = chassis.getPose().y;

  // /////////////////////////SCORE LONG GOAL
  // 6//////////////////////////////////////
  // BLOCKS//////////////////////////////

  chassis.cancelMotion();
  pto.setDriveMode(DRIVE_4_MOTOR);
  DrivePTO.move(-127); // outakes into far long goal 3 blocks
  Intake2.move(-127);
  pros::delay(100);
  Intake2.move(127);
  DrivePTO.move(127); // outakes into far long goal 3 blocks
  pros::delay(2400);
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);

  // ///////////////////////////MATCH LOADER 4
  // /////////////////////////////////////
  chassis.moveToPoint(-10.5, yhere + 1, 1500,
                      {.forwards = true, .maxSpeed = 60},
                      false); ////long goal side
  pros::delay(500);
  chassis.moveToPoint(-15, yhere, 1500, {.forwards = true, .maxSpeed = 60},
                      false); ////long goal side
  pros::delay(950);
  chassis.moveToPoint(36.5, yhere - 0.5, 1500, {.forwards = false},
                      false); ////long goal side

  ////////////////////Score////////////////
  Loader.retract();
  chassis.cancelMotion();
  pto.setDriveMode(DRIVE_4_MOTOR);
  DrivePTO.move(-127); // outakes into far long goal 3 blocks
  Intake2.move(-127);
  pros::delay(100);
  Intake2.move(127);
  DrivePTO.move(80); // outakes into far long goal 3 blocks
  pros::delay(2400);
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);

  ////////////////////////////over park barriar//////////////////////////////
  chassis.moveToPoint(4, yhere, 800,
                      {.forwards = true, .minSpeed = 90, .earlyExitRange = 10},
                      false);
  chassis.turnToHeading(190, 1000, {.maxSpeed = 127}, false);

  // chassis.moveToPose(-20, 25, 360, 1100, {.forwards = true, .lead = 0.8,
  // .minSpeed = 110}, true);
  chassis.moveToPoint(-20, 25, 1000,
                      {.forwards = true, .minSpeed = 90, .earlyExitRange = 9.5},
                      true);
  pros::delay(800);
  Loader.extend();
  chassis.waitUntilDone();
  chassis.turnToHeading(180, 800, {.maxSpeed = 127}, false);
  DrivePTO.brake();
  IntakePTO.brake();
  pto.setDriveMode(DRIVE_8_MOTOR);
  Drivetrainall.move(127);
  pros::delay(1100);
  Drivetrainall.brake();
  Loader.retract();
  pto.setDriveMode(DRIVE_6_MOTOR);
  Intake2.move(127);
}
