#include "Autons.h"
#include "Motion.h"
#include "pros/rtos.hpp"
#include "PTO.h"
#include <cmath>
#include <algorithm>
#include "main.h"

void skills(){
  Intake2.move(127);
  chassis.moveToPoint(0, -35, 1000, {.forwards = false}, true);
  pros::delay(450);
  Loader.extend();
  chassis.waitUntilDone();
  chassis.turnToHeading(270, 1000, {.maxSpeed = 127}, false);


  /////////////////////// MATCH LOADER//////////////////////////////////
  chassis.moveToPoint(-12, -38, 1000, {.forwards = true}, false); /// into match loader
  pros::Task::delay(2000);
  // chassis.moveToPoint(0, -38, 1500, {.forwards = false}, false); 
  // Intake2.brake();
  // chassis.turnToHeading(315, 1000);
  chassis.moveToPoint(13, -53.5, 1500, {.forwards = false}, false);
  Intake2.brake();

  ///////////////////////////ACROSS FIELD//////////////////////////////
  chassis.turnToHeading(270, 1000, {.maxSpeed = 127}, false);
  chassis.setPose(0, 0, 0);
  Loader.retract();
  chassis.moveToPoint(0, -68, 2000, {.forwards = false}, false);
  chassis.moveToPoint(15, -73, 1000, {.forwards = false}, false);
  chassis.turnToHeading(180, 1000, {.maxSpeed = 127}, false);
  chassis.moveToPoint(15, -53, 1000, {.forwards = false}, false);


  /////////////////////////SCORE LONG GOAL 7 BLOCKS//////////////////////////////
  chassis.cancelMotion();
  Loader.extend();
  pto.setDriveMode(DRIVE_4_MOTOR);
  DrivePTO.move(-127); // outakes into far long goal 3 blocks
  Intake2.move(-127);
  pros::delay(100);
  Intake2.move(127);
  DrivePTO.move(127); // outakes into far long goal 3 blocks
  pros::delay(3000);
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);



  ///////////////////////////MATCH LOADER 2/////////////////////////////////////
  chassis.moveToPoint(16, -84, 1500, {.forwards = true, .maxSpeed = 127}, false);//////AT LONG GOAL SIDE
  pros::delay(2000);
  chassis.moveToPoint(15, -53, 1500, {.forwards = false}, false);//////AT LONG GOAL SIDE



  /////////////////////////SCORE LONG GOAL 6 BLOCKS//////////////////////////////
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

  /////////////////////GOING TO THE NEXT MATCH LOADER 3//////////////////////////
  chassis.moveToPoint(13, -70, 1500, {.forwards = true}, false);
  chassis.turnToHeading(270, 1000, {.maxSpeed = 127}, false);
  chassis.moveToPoint(113, -70, 3500, {.forwards = false}, true); 
  chassis.turnToHeading(180, 1000, {.maxSpeed = 127}, false);
  Intake2.move(127);
  chassis.moveToPoint(113, -85, 1000, {.forwards = true}, false);////into match loader
  pros::delay(2000);


  ///////////////////////////SET UP TO OTHER SIDE//////////////////////////////
  chassis.moveToPoint(113, -70, 1000, {.forwards = false}, false);
  chassis.turnToHeading(225, 1000, {.maxSpeed = 127}, false);
  chassis.moveToPoint(125, -61, 1000, {.forwards = false}, false);
  chassis.turnToHeading(180, 1000, {.maxSpeed = 127}, false);
  chassis.moveToPoint(125, 18, 2500, {.forwards = false}, true);
  Loader.retract();
  chassis.waitUntilDone();
  chassis.turnToHeading(90, 1000, {.maxSpeed = 127}, false);
  chassis.moveToPoint(107, 18, 1500, {.forwards = false}, false);////long goal side
  chassis.turnToHeading(0, 1000, {.maxSpeed = 127}, false);
  chassis.moveToPoint(107, -5, 1500, {.forwards = false}, true);////long goal side
  Loader.extend();
  chassis.waitUntilDone();

  // /////////////////////////SCORE LONG GOAL 6 BLOCKS//////////////////////////////

  // chassis.cancelMotion();
  // pto.setDriveMode(DRIVE_4_MOTOR);
  // DrivePTO.move(-127); // outakes into far long goal 3 blocks
  // Intake2.move(-127);
  // pros::delay(100);
  // Intake2.move(127);
  // DrivePTO.move(127); // outakes into far long goal 3 blocks
  // pros::delay(3000);
  // DrivePTO.brake();
  // pto.setDriveMode(DRIVE_6_MOTOR);

  // ///////////////////////////MATCH LOADER 4 /////////////////////////////////////
  // chassis.moveToPoint(107, 35, 1500, {.forwards = true}, false);////long goal side
  // pros::delay(2000);
  // chassis.moveToPoint(107, -5, 1500, {.forwards = false}, false);////long goal side


  // /////////////////////////SCORE LONG GOAL 6 BLOCKS//////////////////////////////
  // chassis.cancelMotion();
  // pto.setDriveMode(DRIVE_4_MOTOR);
  // DrivePTO.move(-127); // outakes into far long goal 3 blocks
  // Intake2.move(-127);
  // pros::delay(100);
  // Intake2.move(127);
  // DrivePTO.move(127); // outakes into far long goal 3 blocks
  // pros::delay(3000);
  // DrivePTO.brake();
  // pto.setDriveMode(DRIVE_6_MOTOR);





  








}

void SAWP(){
      ///////////////////////////PUSH//////////////////////////////
  chassis.moveToPoint(0, -35, 1000, {.forwards = false}, true);
  Intake2.move(127);
  pros::delay(300);
  Loader.extend();
  chassis.waitUntilDone();
  chassis.turnToHeading(270, 1000, {.maxSpeed = 127}, false);


/////////////////////// MATCH LOADER//////////////////////////////////

  chassis.moveToPoint(-15, -35, 1000); /// into match loader
  pros::Task::delay(800);
  chassis.moveToPoint(25, -35, 1500, {.forwards = false}, false); /// long goal
  

  ///////////////////////////LONG GOAL 4 BLOCKS//////////////////////////////
  chassis.cancelMotion();
  pto.setDriveMode(DRIVE_4_MOTOR);
  DrivePTO.move(127); // outakes into far long goal 3 blocks
  pros::delay(1000);
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);
  Loader.retract();


  ///////////////////////////FIRST 3 BLOCKS//////////////////////////////
  chassis.swingToHeading(20, lemlib::DriveSide::RIGHT, 1500, {.maxSpeed = 127});
  chassis.moveToPoint(27, -20, 1500, {.forwards = true, .minSpeed = 90, .earlyExitRange = 9.5}, true); // 3 bloacks
  pros::delay(600);
  Loader.extend();
  chassis.waitUntilDone();
  chassis.turnToHeading(0, 1000, {.maxSpeed = 127}, false);
  Loader.retract();


  ///////////////////////////SECOND 3 BLOCKS//////////////////////////////
  chassis.moveToPoint(25, 22, 1500, {.forwards = true, .minSpeed = 90, .earlyExitRange = 9.5},true); 
  pros::delay(800);
  Loader.extend();
  chassis.waitUntilDone();
  chassis.turnToHeading(315, 1000, {.maxSpeed = 127}, false);



  //////////////////////////MID GOAL 2 BLOCKS//////////////////////////////
  chassis.moveToPoint(35, 10, 1200, {.forwards = false},false); 
  chassis.cancelMotion();
  pto.setDriveMode(DRIVE_4_MOTOR);
  Intake2.move(-127);
  DrivePTO.move(-127);
  pros::delay(200);
  Midgoal.retract();
  IntakePTO.move(75);
  DrivePTO.move(-55); // outakes into far long goal 3 blocks
  pros::delay(900);
  IntakePTO.brake();  
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);
  Loader.retract();



 
  chassis.moveToPoint(4, 48, 1000, {.forwards = true}, true);
  Midgoal.extend();
  pros::delay(300);
  IntakePTO.move(127);
  chassis.waitUntilDone();
  chassis.turnToHeading(270, 1000, {.maxSpeed = 127}, false);


  ///////////SECOND LONG GOAL 4 BLOCKS///////////////////////
  chassis.moveToPoint(25, 47, 1500, {.forwards = false}, false); /// long goal
  chassis.cancelMotion();
  pto.setDriveMode(DRIVE_4_MOTOR);
  DrivePTO.move(127); // outakes into far long goal 3 blocks
  pros::delay(1000);
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);
  Loader.retract();

}