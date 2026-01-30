#include "Autons.h"
#include "Motion.h"
#include "pros/rtos.hpp"
#include "PTO.h"
#include <cmath>
#include <algorithm>
#include "main.h"


void SAWP(){
      ///////////////////////////PUSH//////////////////////////////
  Intake2.move(127);
  chassis.moveToPoint(0, -40, 1000, {.forwards = false}, false);
  Loader.extend();
  pros::delay(100);
  chassis.turnToHeading(270, 1000, {.maxSpeed = 127}, false);


/////////////////////// MATCH LOADER//////////////////////////////////

  chassis.moveToPoint(-17, -42, 1000); /// into match loader
  pros::Task::delay(800);
  chassis.moveToPoint(25, -39, 1500, {.forwards = false}, false); /// long goal
  

  ///////////////////////////LONG GOAL 4 BLOCKS//////////////////////////////
  chassis.cancelMotion();
  pto.setDriveMode(DRIVE_4_MOTOR);
  DrivePTO.move(127); // outakes into far long goal 3 blocks
  pros::delay(1000);
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);
  Loader.retract();


  ///////////////////////////FIRST 3 BLOCKS//////////////////////////////
  chassis.swingToHeading(10, lemlib::DriveSide::RIGHT, 1500, {.maxSpeed = 127});
  chassis.moveToPoint(27, -20, 1000, {.forwards = true}, true); // 3 bloacks
  pros::delay(700);
  Loader.extend();
  chassis.waitUntilDone();
  chassis.turnToHeading(0, 1000, {.maxSpeed = 127}, false);
  Loader.retract();


  ///////////////////////////SECOND 3 BLOCKS//////////////////////////////
  chassis.moveToPoint(27, -25, 1500, {.forwards = false},
                      true); 
  pros::delay(900);
  Loader.extend();
  chassis.waitUntilDone();
  chassis.turnToHeading(315, 1000, {.maxSpeed = 127}, false);



  //////////////////////////MID GOAL 2 BLOCKS//////////////////////////////
  chassis.moveToPoint(40, 14, 1200, {.forwards = false},
                      false); 
  chassis.cancelMotion();
  pto.setDriveMode(DRIVE_4_MOTOR);
  Intake2.move(-127);
  pros::delay(300);
  Midgoal.retract();
  IntakePTO.move(85);
  DrivePTO.move(-85); // outakes into far long goal 3 blocks
  pros::delay(500);
  IntakePTO.brake();  
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);
  Midgoal.extend();
  ///////////////////SECOND LOADER /////////////////////////
  chassis.moveToPoint(4, 51, 2000, {.forwards = true}, false);
  IntakePTO.move(127);
  chassis.turnToHeading(270, 1000, {.maxSpeed = 127}, false);
  chassis.moveToPoint(-17, 49, 1000); /// into match loader
  pros::Task::delay(800);


  ///////////SECOND LONG GOAL 4 BLOCKS///////////////////////
  chassis.moveToPoint(25, 49, 1500, {.forwards = false}, false); /// long goal
  chassis.cancelMotion();
  pto.setDriveMode(DRIVE_4_MOTOR);
  DrivePTO.move(127); // outakes into far long goal 3 blocks
  pros::delay(1000);
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);
  Loader.retract();

}