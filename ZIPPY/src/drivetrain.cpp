#include "main.h"

// Helper for voltage
float tovolt(float percentage) { return (percentage * 127.0 / 100.0); }

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
            Left.move(leftVolt);
            Right.move(rightVolt);
        } else if (pto.getCurrentDriveMode() == DRIVE_6_MOTOR) {
            // Handle 6-motor mode
            L.move(leftVolt);
            R.move(rightVolt);
        } else if (pto.getCurrentDriveMode() == DRIVE_8_MOTOR) {
            // Handle 8-motor mode
            DrivetrainL.move(leftVolt);
            DrivetrainR.move(rightVolt);
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
                IntakePTO.move(127);
                DrivePTO.move(127);
            } else {
                pto.setDriveMode(DRIVE_4_MOTOR);
            }
        } else if (master.get_digital(DIGITAL_L2)) {
            if (pto.getCurrentDriveMode() == DRIVE_4_MOTOR) {
                IntakePTO.move(-127);
                DrivePTO.move(-127);
            } else {
                pto.setDriveMode(DRIVE_4_MOTOR);
            }
        } else if (master.get_digital(DIGITAL_UP)) { // slow outake
            if (pto.getCurrentDriveMode() == DRIVE_4_MOTOR) {
                IntakePTO.move(127);
                DrivePTO.move(-127);
            } else {
                pto.setDriveMode(DRIVE_4_MOTOR);
            }
        } else if (master.get_digital(DIGITAL_R1)) {
            if (pto.getCurrentDriveMode() == DRIVE_6_MOTOR) {
                IntakePTO.move(127);
            } else {
                pto.setDriveMode(DRIVE_6_MOTOR);
            }
        } else if (master.get_digital(DIGITAL_R2)) {
            if (pto.getCurrentDriveMode() == DRIVE_6_MOTOR) {
                Intake2.move(-127);
            } else {
                pto.setDriveMode(DRIVE_6_MOTOR);
            }
        } else {
            IntakePTO.brake();
            DrivePTO.brake();
        }



        pros::delay(10);
    }
}


// --------- LOADER + LIFTER ---------
int Loadercontrols() {
    static bool Loader1 = false;

    while (true) {
        if (master.get_digital_new_press(DIGITAL_Y)) {
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
        if (master.get_digital_new_press(DIGITAL_DOWN)) {
            wing = !wing;
            if (wing)
                Hook.extend();
            else
                Hook.retract();
        }
        pros::delay(10);
    }
}
