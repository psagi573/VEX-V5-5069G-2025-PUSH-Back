#include "PTO.h"
#include "main.h"
#include "pros/abstract_motor.hpp"
#include "pros/adi.h"
#include "pros/misc.h"
#include "pros/rtos.hpp"

float tovolt(float percentage) { return (percentage * 12000.0 / 100.0); }

bool drivetrainEnabled = true;
bool formacro = true;


// --------- DRIVETRAIN ---------
void DriveTrainControls() {
  while (true) {

    if (!formacro) {  // macro running — just idle, don't brake
      pros::delay(10);
      continue;
    }

    if (!drivetrainEnabled) {
      // Stop all drivetrain motors
        if (pto.getCurrentDriveMode() == DRIVE_4_MOTOR) {
            // Handle 4-motor mode
            Left.brake();
            Right.brake();
        } else if (pto.getCurrentDriveMode() == DRIVE_6_MOTOR) {
            // Handle 6-motor mode
            L.brake();
            R.brake();
        } else if (pto.getCurrentDriveMode() == DRIVE_8_MOTOR) {
            // Handle 8-motor mode
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
            // Handle 4-motor mode
            Left.move_voltage(leftVolt);
            Right.move_voltage(rightVolt);
        } else if (pto.getCurrentDriveMode() == DRIVE_6_MOTOR) {
            // Handle 6-motor mode
            L.move_voltage(leftVolt);
            R.move_voltage(rightVolt);
        } else if (pto.getCurrentDriveMode() == DRIVE_8_MOTOR) {
            // Handle 8-motor mode
            DrivetrainL.move_voltage(leftVolt);
            DrivetrainR.move_voltage(rightVolt);
        }

    pros::delay(10);
  }
}
// --------- PTO CONTROL ---------
void DrivePTOcontrols() {
  while (true) {
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
      pto.setDriveMode(DRIVE_8_MOTOR);
    }
    pros::delay(10);
  }
}

// --------- INTAKE ---------
void IntakeControls() {
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
void IntakeRevControls() {
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
void OutakeControls() {
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
void skillsMidControls() {
  while (true) {
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
      if (pto.getCurrentDriveMode() != DRIVE_4_MOTOR) { 
        drivetrainEnabled = false;
        pto.setDriveMode(DRIVE_4_MOTOR);
        pros::delay(100);
        drivetrainEnabled = true;
      }
      Midgoal.extend();
      IntakePTO.move(60);
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



////SKILLS MID GOAL CONTROLS//////
// void MidControls() {
//   while (true) {
//     if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
//       if (pto.getCurrentDriveMode() == DRIVE_4_MOTOR) {
//         Midgoal.extend();
//         IntakePTO.move(70);
//         DrivePTO.move(-50);

//         while (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
//           pros::delay(10);
//         }

//         IntakePTO.brake();
//         DrivePTO.brake();
//         Midgoal.retract();
//         pto.setDriveMode(DRIVE_6_MOTOR);
//       } else {
//         pto.setDriveMode(DRIVE_4_MOTOR);
//       }
//     }
//     pros::delay(10);
//   }
// }

// void skillsMidControls() {
//   while (true) {
//     if (master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
//       if (pto.getCurrentDriveMode() == DRIVE_4_MOTOR) {
//         Loader.extend();
//         IntakePTO.move(-127);
//         DrivePTO.move(-127);
//         pros::delay(300);
//         IntakePTO.brake();
//         DrivePTO.brake();
//         Midgoal.extend();

//         IntakePTO.move(70);
//         DrivePTO.move(-110);

//         while (master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
//           pros::delay(10);
//         }

//         IntakePTO.brake();
//         DrivePTO.brake();
//         //Midgoal.retract();
//         //pto.setDriveMode(DRIVE_6_MOTOR);
//       } else {
//         pto.setDriveMode(DRIVE_4_MOTOR);
//       }
//     }
//     pros::delay(10);
//   }
// }

// --------- LOADER ---------
void Loadercontrols() {
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
void Hookcontrols() {
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

//--------- LOW ---------
void Lowcontrols() {
    while (true) {
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
      Low.extend();
      if (pto.getCurrentDriveMode() != DRIVE_6_MOTOR) {
        pto.setDriveMode(DRIVE_6_MOTOR);
      }
      IntakePTO.move(-127);
      while (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        pros::delay(10);
      }
      IntakePTO.brake();
      Low.retract();
      pto.setDriveMode(DRIVE_6_MOTOR);
    }
    pros::delay(10);
  }
}


// void macroWINGleft() {
//   while (true) {
//     if (master.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
//       formacro = false;
//       pros::delay(50); 

//       chassis.setPose(0, 0, 0);
//       chassis.moveToPoint(-10, 12, 1000, {}, false);   // false = blocking, waits to finish
//       chassis.turnToHeading(175, 1000, {}, false);     // false = blocking, waits to finish

//       chassis.cancelAllMotions(); 
//       formacro = true;
//     }
//     pros::delay(10);
//   }
// }


// --------- 7 block macro ---------
void macroMIDGOAL() {
  while (true) {
    static bool stuff = false;
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
      stuff = !stuff;
      if (stuff){
       // formacro = false;
        Loader.extend();
        pto.setDriveMode(DRIVE_4_MOTOR);
        pros::delay(50);
        Midgoal.extend();
        IntakePTO.move(-80);
        DrivePTO.move(-70);
        pros::delay(250);
        IntakePTO.move(65);
        DrivePTO.move(-110);
        pros::delay(1900);
        IntakePTO.brake();
        pros::delay(200);
        IntakePTO.move(55);
        DrivePTO.move(-85);
        pros::delay(1500);
        IntakePTO.brake();
        DrivePTO.brake();
        Midgoal.retract();
        Loader.retract();
        pto.setDriveMode(DRIVE_6_MOTOR);
      }
      else {
        IntakePTO.brake();
        DrivePTO.brake();
        pto.setDriveMode(DRIVE_6_MOTOR);
      }
    }

    pros::delay(10);
  }
}
