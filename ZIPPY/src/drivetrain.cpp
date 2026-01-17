#include "main.h"

float tovolt(float percentage) { return (percentage * 12.0 / 100.0); }

int DriveTrainControls() // we create a integer function named
                         // "DriveTrainControls", later in the code we plan to
                         // turnpid this into a Thread that controls the
                         // drivetrain
{

  while (true) {
    // Read joystick values

    int forward = (master.get_analog(ANALOG_RIGHT_X));
    int turn = (master.get_analog(ANALOG_LEFT_Y));

    float leftVolt = tovolt(forward + turn);
    float rightVolt = tovolt(forward - turn);
/*
    // // Spin only active motors
    auto leftActive = pto.getActiveLeftMotors();
    auto rightActive = pto.getActiveRightMotors();

//////////////////////////////////////////////////////////////////////////
    for (auto m : leftActive)
      m->move(leftVolt);

    for (auto m : rightActive)
      m->move(rightVolt);*/
//////////////////////////////////////////////////////////////////////////

    chassis.curvature(leftVolt, rightVolt);
    
    delay(10);
  }
}

int slavePTOcontrol() {
  while (true) {

     if (slave.get_digital(DIGITAL_R1)) {
        pto.setDriveMode(DRIVE_6_MOTOR);
    }
    delay(10);
  }
}

int slaveWINGcontrol() {
  while (true) {
      if (slave.get_digital(DIGITAL_L2)) {
          Hook.retract();
    }
    delay(10);
  }
}

int slaveLOADERcontrol() {
  while (true) {
    
      if (slave.get_digital(DIGITAL_L1)) {
          Loader.retract();
    }
    delay(10);
  }
}
int IntakeControls() {
  while (true) {

    if (master.get_digital(DIGITAL_R1)) {
      if (pto.getCurrentDriveMode() == DRIVE_6_MOTOR) {
        Funnel.retract();
        Intake2.move(127);
        while (!master.get_digital(DIGITAL_R1)) {
          pros::delay(10);
        } // keeps it spinning until the user let go of R2
        Intake2.brake();
      } else {
        pto.setDriveMode(DRIVE_6_MOTOR);
      }
    }
    delay(10);
  }
}

int IntakerevControls() {
  while (true) {
    if (master.get_digital(DIGITAL_R2)) {
      if (pto.getCurrentDriveMode() == DRIVE_6_MOTOR) {
        Funnel.retract();
        Intake2.move(-127);
        while (!master.get_digital(DIGITAL_R2)) {
          pros::delay(10);
        } // keeps it spinning until the user let go of R2
        Intake2.brake();
      } else {
        pto.setDriveMode(DRIVE_6_MOTOR);
      }
    }
    delay(10);
  }
}

int OutakeControls() {
  while (true) {

    if (master.get_digital(DIGITAL_L1)) {
      if (pto.getCurrentDriveMode() == DRIVE_4_MOTOR) {
        Funnel.extend();
        Intake4.move(127);
        while (!master.get_digital(DIGITAL_L1)) {
          pros::delay(10);
        } // keeps it spinning until the user let go of L1
        Intake4.brake();
      } else {
        pto.setDriveMode(DRIVE_4_MOTOR);
      }
    }
    delay(10);
  }
}

int OutakerevControls() {
  while (true) {
    if (master.get_digital(DIGITAL_L2)) {
      if (pto.getCurrentDriveMode() == DRIVE_4_MOTOR) {
        Funnel.extend();
        Intake4.move(-127);
        while (!master.get_digital(DIGITAL_L2)) {
          pros::delay(10);
        } // keeps it spinning until the user let go of L2
        Intake4.brake();
      } else {
        pto.setDriveMode(DRIVE_4_MOTOR);
      }
    }
    delay(10);
  }
}

int slowOutakeControls() {
  while (true) {
    if (master.get_digital(DIGITAL_UP)) {
      if (pto.getCurrentDriveMode() == DRIVE_4_MOTOR) {
        Funnel.extend();
        Intake4.move(-127);
        while (!master.get_digital(DIGITAL_UP)) {
          pros::delay(10);
        } // keeps it spinning until the user let go of L2
        Intake4.brake();
      } else {
        pto.setDriveMode(DRIVE_4_MOTOR);
      }
    }
    delay(10);
  }
}

int DrivePTOcontrols() {

  bool DrivePTO = false;
  while (true) {
    if (master.get_digital(DIGITAL_RIGHT)) {
      if (DrivePTO) {
        DrivePTO = false;
      } else if (!DrivePTO) {
        DrivePTO = true;
      }
      while (master.get_digital(DIGITAL_RIGHT)) {

        delay(5);
      }

      if (DrivePTO) {
        pto.setDriveMode(DRIVE_8_MOTOR);
      } else {
        pto.setDriveMode(DRIVE_6_MOTOR);
      }
    }
  }
}

int Parkcontrols() {

  bool Park = false;
  while (true) {
    if (master.get_digital(DIGITAL_X)) {
      if (Park) {
        Park = false;
      } else if (!Park) {
        Park = true;
      }
      while (master.get_digital(DIGITAL_X)) {

        delay(5);
      }

      if (Park) {
        Doublepark.extend();
      } else {
        Doublepark.retract();
      }
    }
  }
}

bool Loader1 = false;
int Loadercontrols() {

  while (true) {
    if (master.get_digital(DIGITAL_Y)) {
      if (Loader1) {
        Loader1 = false;
      } else if (!Loader1) {
        Loader1 = true;
      }
      while (master.get_digital(DIGITAL_Y)) {

        delay(5);
      }

      if (Loader1) {
        Lifter.retract();
        Loader.extend();
      } else {
        Loader.retract();
      }
    }
  }
}

bool lifter = false;
int liftercontrols() {

  while (true) {
    if (master.get_digital(DIGITAL_B)) {
      if (lifter) {
        lifter = false;
      } else if (!lifter) {
        lifter = true;
      }
      while (master.get_digital(DIGITAL_B)) {

        delay(5);
      }

      if (lifter) {
        Lifter.extend();
      } else {
        Lifter.retract();
      }
    }
  }
}

int Hookcontrols() {

  bool wing = false;
  while (true) {
    if (master.get_digital(DIGITAL_DOWN)) {
      if (wing) {
        wing = false;
      } else if (!wing) {
        wing = true;
      }
      while (master.get_digital(DIGITAL_DOWN)) {

        delay(10);
      }

      if (wing) {
        Hook.extend();
      } else {
        Hook.retract();
      }
    }
  }
}
drivetrain.cpp