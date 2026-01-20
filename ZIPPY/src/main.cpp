#include "main.h"
#include "pros/distance.hpp"

// ----------------- GLOBALS -----------------


// Tasks
pros::Task* odomTask = nullptr;
// PTO Manager
PTOManager pto(
    {&L1, &L2, &PTOL3, &LIntake},
    {&R6, &R7, &PTOR8, &RIntake},
    'B',
    'A'
);

// Drivetrain / LemLib config
lemlib::Drivetrain drivetrain(&L, &R, 12.25, lemlib::Omniwheel::NEW_325, 480, 0.15853);

// Odom wheels
lemlib::TrackingWheel horizontal_tracking_wheel(&Xaxis, 2, 1.7);
lemlib::TrackingWheel vertical_tracking_wheel(&Yaxis, 2, 0.1);

// Odom sensors
lemlib::OdomSensors sensors(&vertical_tracking_wheel, nullptr, &horizontal_tracking_wheel, nullptr, &inertial19);

// PID settings
lemlib::ControllerSettings lateral_controller(4,
                                              0,
                                              0,
                                              3,
                                              1,
                                              100,
                                              3,
                                              500,
                                              0);

lemlib::ControllerSettings angular_controller(2,
                                              0,
                                              12,
                                              3,
                                              1,
                                              100,
                                              3,
                                              500,
                                              0);

// Chassis
lemlib::Chassis chassis(drivetrain, lateral_controller, angular_controller, sensors);



// ----------------- ODOM DEBUG TASK -----------------
void odomDebug(void*) {
    master.clear();
    while(true) {
        lemlib::Pose pose = chassis.getPose();
        pros::lcd::print(1, "X: %.2f", pose.x);
        pros::lcd::print(2, "Y: %.2f", pose.y);
        pros::lcd::print(3, "H: %.2f", pose.theta);
        pros::lcd::print(4, "X true: %.2f", Xaxis.get_position());
        pros::lcd::print(5, "Y true: %.2f", Yaxis.get_position());

        master.print(0, 0, "X:%5.1f Y:%5.1f", pose.x, pose.y);
        master.print(1, 0, "H:%5.1f", pose.theta);
        master.print(2, 0, "X true:%5.1f Y true:%5.1f", Xaxis.get_position(), Yaxis.get_position());
        pros::delay(50);
    }
}

// ----------------- INITIALIZE -----------------
void initialize() {
    pros::lcd::initialize();

    // Sensors reset
    inertial19.reset();
    while(inertial19.is_calibrating()) pros::delay(10);
    Xaxis.reset_position();
    Yaxis.reset_position();
    chassis.calibrate();
    DrivetrainL.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
    DrivetrainR.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
    chassis.setPose(0,0,0);

    // Start Odom debug task
    odomTask = new pros::Task(odomDebug);


}
void DistanceCOORDINATE() {

    float Ydist = Yeye.get_distance()*1000;//converts to meters
    float Xdist = Xeye.get_distance()*1000;//converts to meters
    //field dimentions (3.65m x 3.65m)

    float YcurrEYE = 3.65 - Ydist;
    float XcurrEYE = 3.65 - Xdist;

    lemlib::Pose pose = chassis.getPose();
    
}
const double WALL_X_MIN = 0.0;
const double WALL_Y_MAX = 144.0;
const double SENSOR_OFFSET_FRONT = 5.5; // Dist from center to front sensor
const double SENSOR_OFFSET_LEFT = 5.5;  // Dist from center to left sensor

// Median Filter Function
double get_median_distance(pros::Distance& sensor) {
    std::vector<double> readings;
    for(int i = 0; i < 5; i++) {
        readings.push_back(sensor.get_distance());
        pros::delay(10);
    }
    std::sort(readings.begin(), readings.end());
    return readings[2]; // Return the middle value
}
void sensor_correction_task() {
    pros::Distance left_dist(1);  // Port 1
    pros::Distance front_dist(2); // Port 2
    pros::Imu imu(3);             // Port 3

    while (true) {
        double heading = imu.get_heading();
        
        // Only correct if we are facing "North" (approx 0 degrees)
        if (heading < 2 || heading > 358) {
            double raw_ass = get_median_distance(front_dist) / 25.4; // mm to inches
            double raw_buns = get_median_distance(left_dist) / 25.4;

            // Project based on small angle error
            double rad_error = (heading > 180 ? heading - 360 : heading) * (M_PI / 180.0);
            
            double corrected_y = WALL_Y_MAX - (raw_ass * cos(rad_error) + SENSOR_OFFSET_FRONT);
            double corrected_x = WALL_X_MIN + (raw_buns * cos(rad_error) + SENSOR_OFFSET_LEFT);

            // "Nudge" the global odom coordinates (don't teleport)
            // Assuming global_x and global_y are your odom variables
            float global_y = (global_y * 0.9) + (corrected_y * 0.1);
            float global_x = (global_x * 0.9) + (corrected_x * 0.1);

            chassis.setPose(global_x, global_y, heading);
        }
        
        pros::delay(50); // Don't hog the CPU
    }
}

// ----------------- DISABLED -----------------
void disabled() {}

// ----------------- COMPETITION INIT -----------------
void competition_initialize() {}

// ----------------- AUTONOMOUS -----------------
void autonomous() {
    chassis.setPose(0,0,0);
    chassis.turnToHeading(90, 1000);
    chassis.moveToPoint(24,0, 3000);

    pros::delay(15000); // keep auton alive for skills
}

// ----------------- OPERATOR CONTROL -----------------
void opcontrol() {
    Drivetrain.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
    IntakePTO.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
    DrivePTO.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);

    new pros::Task(DriveTrainControls);
    new pros::Task(OutakeControls);
    new pros::Task(DrivePTOcontrols);
    new pros::Task(Loadercontrols);
    new pros::Task(Hookcontrols);
    while(true) {
        if(master.is_connected()) master.print(0,0,"MASTER");
        if(slave.is_connected()) slave.print(0,0,"SLAVE");
        pros::delay(20);
    }
}