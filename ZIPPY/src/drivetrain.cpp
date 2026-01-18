#include "main.h"

// Helper for voltage
float tovolt(float percentage) { return (percentage * 12.0 / 100.0); }

// --------- DRIVETRAIN ---------
int DriveTrainControls() {
    while (true) {
        int forward = master.get_analog(ANALOG_LEFT_Y); // forward/back
        int turn = master.get_analog(ANALOG_RIGHT_X);  // left/right

        float leftVolt = tovolt(forward + turn);
        float rightVolt = tovolt(forward - turn);

        // PTO-aware drivetrain
        // auto leftActive = pto.getActiveLeftMotors();
        // auto rightActive = pto.getActiveRightMotors();

        // for (auto m : leftActive) m->move_voltage(leftVolt * 1000);
        // for (auto m : rightActive) m->move_voltage(rightVolt * 1000);
        Left.move_voltage(leftVolt * 1000);
        Right.move_voltage(rightVolt * 1000);

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

// --------- INTAKE CONTROLS ---------
int IntakeControls() {
    // while (true) {
    //     if (master.get_digital(DIGITAL_R1)) {
    //         if (pto.getCurrentDriveMode() == DRIVE_6_MOTOR) {
    //             Funnel.retract();
    //             Intake2.move(127);
    //         } else {
    //             pto.setDriveMode(DRIVE_6_MOTOR);
    //         }
    //     } else if (master.get_digital(DIGITAL_R2)) {
    //         if (pto.getCurrentDriveMode() == DRIVE_6_MOTOR) {
    //             Funnel.retract();
    //             Intake2.move(-127);
    //         } else {
    //             pto.setDriveMode(DRIVE_6_MOTOR);
    //         }
    //     } else {
    //         Intake2.brake();
    //     }



        while (true) {
        if (master.get_digital(DIGITAL_R1)) {
                IntakePTO.move(127);
        } else if (master.get_digital(DIGITAL_R2)) {
                IntakePTO.move(-127);
        } else {
            IntakePTO.brake();
        }
        pros::delay(10);
    }
}

// --------- OUTAKE CONTROLS ---------
int OutakeControls() {
    while (true) {
        // if (master.get_digital(DIGITAL_L1)) {
        //     if (pto.getCurrentDriveMode() == DRIVE_4_MOTOR) {
        //         Funnel.extend();
        //         Intake4.move(127);
        //     } else {
        //         pto.setDriveMode(DRIVE_4_MOTOR);
        //     }
        // } else if (master.get_digital(DIGITAL_L2)) {
        //     if (pto.getCurrentDriveMode() == DRIVE_4_MOTOR) {
        //         Funnel.extend();
        //         Intake4.move(-127);
        //     } else {
        //         pto.setDriveMode(DRIVE_4_MOTOR);
        //     }
        // } else if (master.get_digital(DIGITAL_UP)) { // slow outake
        //     if (pto.getCurrentDriveMode() == DRIVE_4_MOTOR) {
        //         Funnel.extend();
        //         Intake4.move(-60);
        //     } else {
        //         pto.setDriveMode(DRIVE_4_MOTOR);
        //     }
        // } else {
        //     Intake4.brake();
        // }




         if (master.get_digital(DIGITAL_L1)) {
                Intake4.move(127);
        } 
        else if (master.get_digital(DIGITAL_R1)) {
                IntakePTO.move(127);
        } else if (master.get_digital(DIGITAL_R2)) {
                IntakePTO.move(-127);
        }
        else if (master.get_digital(DIGITAL_L2)) {
                Intake4.move(-127);
        } else if (master.get_digital(DIGITAL_UP)) { // slow outake
                Intake2.move(60);
                DrivePTO.move(-60);
        } else {
            Intake2.brake();
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
                Lifter.retract();
                Loader.extend();
            } else {
                Loader.retract();
            }
        }
        pros::delay(10);
    }
}

int liftercontrols() {
    static bool lifter = false;

    while (true) {
        if (master.get_digital_new_press(DIGITAL_B)) {
            lifter = !lifter;
            if (lifter)
                Lifter.extend();
            else
                Lifter.retract();
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
