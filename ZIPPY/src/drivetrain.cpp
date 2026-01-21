#include "main.h"

// Helper for voltage
float tovolt(float percentage) { return (percentage * 12000.0 / 100.0); }

// --------- DRIVETRAIN ---------
int DriveTrainControls() {
    while (true) {
        int forward = master.get_analog(ANALOG_LEFT_Y); // forward/back
        int turn = master.get_analog(ANALOG_RIGHT_X);  // left/right

        float leftVolt = tovolt(forward + turn);
        float rightVolt = tovolt(forward - turn);

        //PTO-aware drivetrain

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
int DrivePTOcontrols() {
    static bool DrivePTO1 = false;

    while (true) {
        if (master.get_digital_new_press(DIGITAL_RIGHT)) {
            DrivePTO1 = !DrivePTO1;
            pto.setDriveMode(DrivePTO1 ? DRIVE_8_MOTOR : DRIVE_6_MOTOR);
        }
        pros::delay(10);
    }
}

// --------- OUTAKE CONTROLS ---------
int OutakeControls() {
    while (true) {
        if (master.get_digital(DIGITAL_L1)) {
            if (pto.getCurrentDriveMode() == DRIVE_4_MOTOR) {
                IntakePTO.move(-127);
                DrivePTO.move(-127);
            } else {
                pto.setDriveMode(DRIVE_4_MOTOR);
            }
        } else if (master.get_digital(DIGITAL_DOWN)) { // slow outake
            if (pto.getCurrentDriveMode() == DRIVE_4_MOTOR) {
                Midgoal.extend();
                IntakePTO.move(60);
                DrivePTO.move(-60);
            } else {
                pto.setDriveMode(DRIVE_4_MOTOR);
            }
        } else if (master.get_digital(DIGITAL_R2)) {
            if (pto.getCurrentDriveMode() == DRIVE_6_MOTOR) {
                IntakePTO.move(127);
            } else {
                pto.setDriveMode(DRIVE_6_MOTOR);
            }
        } else if (master.get_digital(DIGITAL_R1)) {
            if (pto.getCurrentDriveMode() == DRIVE_4_MOTOR) {
                IntakePTO.move(127);
                DrivePTO.move(127);
            } else {
                pto.setDriveMode(DRIVE_4_MOTOR);
            }
        } else {
            IntakePTO.brake();
            DrivePTO.brake();
            Midgoal.retract();
        }



        pros::delay(10);
    }
}


// --------- LOADER ---------
int Loadercontrols() {
    static bool Loader1 = false;

    while (true) {
        if (master.get_digital_new_press(DIGITAL_B)) {
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


// --------- HOOK CONTROL ---------
int Hookcontrols() {
    static bool wing = false;

    while (true) {
        if (master.get_digital_new_press( DIGITAL_L2)) {
            wing = !wing;
            if (wing)
                Hook.extend();
            else
                Hook.retract();
        }
        pros::delay(10);
    }
}
