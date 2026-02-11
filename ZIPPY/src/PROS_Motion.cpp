#include "PROS_Motion.h"
#include "main.h"
#include <cmath>

// ======================
// Motor declarations
// ======================


// ======================
// Utility
// ======================
template <typename T>
T clamp(T value, T minVal, T maxVal) {
    if (value < minVal) return minVal;
    if (value > maxVal) return maxVal;
    return value;
}

// ======================
// Drive constants
// ======================
constexpr double WHEEL_DIAMETER = 3.25; // inches
constexpr double GEAR_RATIO = 0.8;      // 48:60
constexpr double WHEEL_CIRC = M_PI * WHEEL_DIAMETER;
constexpr double INCHES_PER_ROT = WHEEL_CIRC * GEAR_RATIO;

// ======================
// Encoder helpers
// ======================
void resetDriveEncoders() {
    L1.tare_position();
    L2.tare_position();
    R6.tare_position();
    R7.tare_position();
}

double getDriveDistanceInches() {
    double left =
        (fabs(L1.get_position()) + fabs(L2.get_position())) / 2.0;

    double right =
        (fabs(R6.get_position()) + fabs(R7.get_position())) / 2.0;

    return ((left + right) / 2.0) * INCHES_PER_ROT;
}

// ======================
// Low-level drive
// ======================
static void setDriveVoltage(double millivolts) {
    millivolts = clamp(millivolts, -12000.0, 12000.0);

    L.move_voltage(millivolts);
    R.move_voltage(millivolts);
}

static void stopDrive() {
    L.brake();
    R.brake();

}




// ======================
// PID Drive
// ======================
void drivePID(double targetInches, int timeoutMs) {
    // ---- PID constants (tune these) ----
    double kP = 900;   // mV per inch
    double kI = 0;
    double kD = 0;

    double error = 0;
    double lastError = 0;
    double integral = 0;
    double derivative = 0;

    resetDriveEncoders();

    int elapsed = 0;

    while (elapsed < timeoutMs) {
        double position = getDriveDistanceInches();
        error = targetInches - position;
        derivative = error - lastError;

        // Anti-windup
        if (fabs(error) < 5)
            integral += error;
        else
            integral = 0;

        double output =
            (kP * error) +
            (kI * integral) +
            (kD * derivative);

        output = clamp(output, -12000.0, 12000.0);

        // Minimum voltage to overcome friction
        if (fabs(output) < 2000 && fabs(error) > 0.5)
            output = copysign(2000, output);

        setDriveVoltage(output);

        // Exit condition
        if (fabs(error) < 0.5 && fabs(derivative) < 0.05)
            break;

        lastError = error;
        elapsed += 10;
        pros::delay(10);
    }

    stopDrive();
}
