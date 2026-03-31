#include "PTO.h"
#include "main.h"
#include "pros/abstract_motor.hpp"
#include "pros/misc.h"

float tovolt(float percentage) { return (percentage * 12000.0 / 100.0); }

bool drivetrainEnabled = true;

// --------- DRIVETRAIN ---------
int DriveTrainControls() {
  while (true) {
    if (!drivetrainEnabled) {
      if (pto.getCurrentDriveMode() == DRIVE_4_MOTOR) {
        Left.brake();
        Right.brake();
      } else if (pto.getCurrentDriveMode() == DRIVE_6_MOTOR) {
        L.brake();
        R.brake();
      } else if (pto.getCurrentDriveMode() == DRIVE_8_MOTOR) {
        DrivetrainL.brake();
        DrivetrainR.brake();
      }
      pros::delay(10);
      continue;
    }

    int forward = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
    float leftVolt = tovolt(forward + turn);
    float rightVolt = tovolt(forward - turn);

    if (pto.getCurrentDriveMode() == DRIVE_4_MOTOR) {
      Left.move_voltage(leftVolt);
      Right.move_voltage(rightVolt);
    } else if (pto.getCurrentDriveMode() == DRIVE_6_MOTOR) {
      L.move_voltage(leftVolt);
      R.move_voltage(rightVolt);
    } else if (pto.getCurrentDriveMode() == DRIVE_8_MOTOR) {
      DrivetrainL.move_voltage(leftVolt);
      DrivetrainR.move_voltage(rightVolt);
    }

    pros::delay(10); 
  }
}

// --------- PTO CONTROL ---------
int DrivePTOcontrols() {
  while (true) {
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
      pto.setDriveMode(DRIVE_8_MOTOR);
    }
    pros::delay(10);
  }
}

// --------- INTAKE ---------
int IntakeControls() {
  while (true) {
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
      if (pto.getCurrentDriveMode() != DRIVE_6_MOTOR) { 
        pto.setDriveMode(DRIVE_6_MOTOR);
      }
      IntakePTO.move(127);
      while (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        pros::delay(10);
      }
      IntakePTO.brake();
      pto.setDriveMode(DRIVE_6_MOTOR);
    }
    pros::delay(10);
  }
}

// --------- INTAKE REVERSE ---------
int IntakeRevControls() {
  while (true) {
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
      if (pto.getCurrentDriveMode() != DRIVE_6_MOTOR) {
        pto.setDriveMode(DRIVE_6_MOTOR);
      }
      IntakePTO.move(-127);
      while (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        pros::delay(10);
      }
      IntakePTO.brake();
      pto.setDriveMode(DRIVE_6_MOTOR);
    }
    pros::delay(10);
  }
}

// --------- OUTAKE/SCORE ---------
int OutakeControls() {
  while (true) {
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
      if (pto.getCurrentDriveMode() != DRIVE_4_MOTOR) { 
        drivetrainEnabled = false;
        pto.setDriveMode(DRIVE_4_MOTOR);
        pros::delay(1); 
        drivetrainEnabled = true;
      }
      IntakePTO.move(127);
      DrivePTO.move(127);
      while (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        pros::delay(10);
      }
      IntakePTO.brake();
      DrivePTO.brake();
      pto.setDriveMode(DRIVE_6_MOTOR);
    }
    pros::delay(10);
  }
}

// --------- MID GOAL ---------
int skillsMidControls() {
  while (true) {
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
      if (pto.getCurrentDriveMode() != DRIVE_4_MOTOR) { 
        drivetrainEnabled = false;
        pto.setDriveMode(DRIVE_4_MOTOR);
        pros::delay(100);
        drivetrainEnabled = true;
      }
      Midgoal.extend();
      IntakePTO.move(85);
      DrivePTO.move(-127);
      while (master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
        pros::delay(10);
      }
      IntakePTO.brake();
      DrivePTO.brake();
      Midgoal.retract();
      pto.setDriveMode(DRIVE_6_MOTOR);
    }
    pros::delay(10);
  }
}

// --------- LOADER ---------
int Loadercontrols() {
  static bool Loader1 = false;
  while (true) {
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
      Loader1 = !Loader1;
      if (Loader1) {
        Loader.extend();
      } else {
        Loader.retract();
      }
    }
    pros::delay(10);
  }
}

// --------- HOOK ---------
int Hookcontrols() {
  static bool wing = false;
  while (true) {
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
      wing = !wing;
      if (wing)
        Hook.extend();
      else
        Hook.retract();
    }
    pros::delay(10);
  }
}

// --------- LOW ---------
int Lowcontrols() {
  while (true) {
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
      Low.extend();
      while (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        IntakePTO.move(-127);
        pros::delay(10);
      }
      IntakePTO.brake();
      Low.retract();
    }
    pros::delay(10);
  }
}
