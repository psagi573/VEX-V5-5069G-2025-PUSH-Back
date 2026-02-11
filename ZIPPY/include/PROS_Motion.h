#pragma once
#include "pros/motors.hpp"

/**
 * Drive a linear distance using encoder-based PID.
 * @param targetInches Distance to drive (positive = forward, negative = backward)
 * @param timeoutMs Max time before exiting (default 2000 ms)
 */
void drivePID(double targetInches, int timeoutMs = 2000);

/**
 * Reset all drivetrain encoders.
 */
void resetDriveEncoders();

/**
 * Get average drivetrain distance traveled in inches.
 */
double getDriveDistanceInches();
