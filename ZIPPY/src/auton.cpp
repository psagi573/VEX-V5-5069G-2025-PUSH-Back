#include "auton.h"
#include "main.h"

// ----------------- UTILITY -----------------
void waitSec(double seconds) {
    pros::delay(static_cast<int>(seconds * 1000));
}

// ----------------- RUN SELECTED AUTON -----------------
void runAuton(const auton_descriptor_t& auton) {
    if (auton.callback != nullptr) {
        auton.callback();
    }
}

// ----------------- EXAMPLE AUTONS -----------------
void autonRedRight1() {

}

void autonRedLeft1() {

}

void autonBlueRight1() {

}

void autonBlueLeft1() {

}

void autonSkills() {

