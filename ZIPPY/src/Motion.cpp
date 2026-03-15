#include "motion.h"
#include "PID.h"
#include "main.h"
#include <cmath>
#include <algorithm>
#include "PTO.h"
#include "pros/abstract_motor.hpp"
#include "pros/rtos.hpp"




const double wheelTrack = 11.75; // in inches (left-right distance)

// PID class values (Existing values)
Praj distPID(0.07, 0, 0.2);
Praj distPIDnew(0.13, 0, 0.9);
Praj fastTurnPID(0.03, 0, 0.23);

Praj slowTurnPID(0.03, 0, 0.28);

Praj arcPID(0.15, 0, 0);
Praj sweepPID(0.05, 0, 0.5);

Praj drivePID(0.05, 0, 0.6);
Praj headingPID(0.03, 0.0001, 0.23);

/**
 * @brief Clamps a value between a minimum and maximum.
 */
template <typename T>
T clamp(T value, T minVal, T maxVal)
{
    if (value < minVal)
        return minVal;
    if (value > maxVal)
        return maxVal;
    return value;
}



// Global or external PTO instance
extern PTOManager pto;

// PTO–aware drive function
void setDrivePTO(double left, double right) {
    left = clamp(left, -12.0, 12.0);
    right = clamp(right, -12.0, 12.0);

    // Get only motors engaged in the current configuration
    auto leftMotors = pto.getActiveLeftMotors();
    auto rightMotors = pto.getActiveRightMotors();

    for (auto* m : leftMotors)
        m->move_voltage(left * 100); // Convert volts to mV

    for (auto* m : rightMotors)
        m->move_voltage(right * 120); // Convert volts to mV
}

void stopsPTO() {
    auto leftMotors = pto.getActiveLeftMotors();
    auto rightMotors = pto.getActiveRightMotors();

    for (auto* m : leftMotors)
        m->brake();

    for (auto* m : rightMotors)
        m->brake();
}


void stopsPTOhold() {
    auto leftMotors = pto.getActiveLeftMotors();
    auto rightMotors = pto.getActiveRightMotors();

    for (auto* m : leftMotors)
        m->brake();

    for (auto* m : rightMotors)
        m->brake();
}

/**
 * @brief Sets left and right motor voltages.
 */
void setDrive(double left, double right)
{
    // Clamp values for safety
    left = clamp(left, -12.0, 12.0);
    right = clamp(right, -12.0, 12.0);

    // Send voltage to motors (volt units)
    L1.move_voltage(left * 120);
    L2.move_voltage(left * 120);
    PTOL3.move_voltage(left * 120);

    R6.move_voltage(right * 120);
    R7.move_voltage(right * 120);
    PTOR8.move_voltage(right * 120);
}


/**
 * @brief Stops all drive motors with brake mode.
 */
void stops()
{
    // Stop all motors
    L1.brake();
    L2.brake();
    PTOL3.brake();
    R6.brake();
    R7.brake();
    PTOR8.brake();
}

/**
 * @brief Applies a minimum voltage threshold to overcome motor friction.
 */
double minVolt(double v)
{
    const double MIN_V = 2.0;
    if (v > -MIN_V && v < 0)
        return -MIN_V;
    if (v > 0 && v < MIN_V)
        return MIN_V;
    return v;
}

double minVoltturn(double v)
{
    const double MIN_V = 3.0;
    if (v > -MIN_V && v < 0)
        return -MIN_V;
    if (v > 0 && v < MIN_V)
        return MIN_V;
    return v;
}

double wrapAngle(double error) {
    while (error > 180) error -= 360;
    while (error < -180) error += 360;
    return error;
}

const float WHEEL_CIRCUMFERENCE = M_PI * 3.25;              // ~12.09 inches
const float INCHES_PER_MOTOR_TURN = WHEEL_CIRCUMFERENCE * 0.8; // Gear ratio is 48:60, so multiply by 0.8

/**
 * @brief Calculates the average distance traveled based on motor rotations.
 */
float getAverageDistance()
{
    // Get positions from all motors (in turns/rotations)
    float left1_pos = L1.get_position();
    float left2_pos = L2.get_position();
    float right1_pos = R6.get_position();
    float right2_pos = R7.get_position();

    // Calculate average motor rotations
    float avg_rotations = (left1_pos + left2_pos +
                           right1_pos + right2_pos) /
                          4.0;

    // Convert average motor rotations to inches traveled
    float distance_inches = avg_rotations * INCHES_PER_MOTOR_TURN;

    return distance_inches;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
    //TUNE HERE// TUNE HERE// TUNE HERE// TUNE HERE// TUNE HERE// TUNE HERE//
//-----------------------------------------------------------------------------------------//
float error = 0 ; // sensor - desired
float prevError = 0; // position from last loop (previous error)
float derivative = 0;
float output = 0; 
float integral = 0;
float prevoutput = 0;
bool enabledrivepid;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 

void driveM6(float targetvalue, float timeout, float kP, float kD){

  float elapsedtime = 0;
  double start = chassis.getPose().y;
  while(true) {
    double current = chassis.getPose().y;//((Yaxis.get_position()/360.0 )* (2 * M_PI));

    float averageposition = current - start;

    error = targetvalue - averageposition;
    derivative = (error - prevError);
    

    output = (kP*error) + (kD*derivative);// kD = 3, Kp = 7

    if (output > 127) output = 127;
    if (output < -127) output = -127;

    chassis.tank(output, output);
 
    if ((fabs(error) < 1) || (elapsedtime >= timeout)) {
      break;
    }

    elapsedtime += 10;
    prevError = error;
    delay(10);
  }
    chassis.tank(0, 0);
}

void driveM8(float targetvalue, float timeout, float kP, float kD){

  float elapsedtime = 0;
    double start = chassis.getPose().y;
  enabledrivepid = true;
  while(enabledrivepid) {
    double current = chassis3.getPose().y;//((Yaxis.get_position()/360.0 )* (2 * M_PI));
    float averageposition = current - start;

    error = targetvalue - averageposition;
    derivative = (error - prevError);
    

    output = (kP*error) + (kD*derivative);// kD = 3, Kp = 7

    if (output > 127) output = 127;
    if (output < -127) output = -127;

    chassis3.tank(output, output);
 
    if ((fabs(error) < 1) || (elapsedtime >= timeout)) {
      break;
    }

    elapsedtime += 10;
    prevError = error;
    delay(10);
  }
    L1.brake();
    L2.brake();
    PTOL3.brake();
    R6.brake();
    R7.brake();
    PTOR8.brake();
}
