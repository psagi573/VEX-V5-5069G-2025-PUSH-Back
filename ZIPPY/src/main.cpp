#include "main.h"

// ----------------- GLOBALS -----------------
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller slave(pros::E_CONTROLLER_PARTNER);

// Tasks
pros::Task* odomTask = nullptr;

// PTO Manager
PTOManager pto(
    {&L1, &L2, &PTOL3, &LIntake},
    {&R6, &R7, &PTOR8, &RIntake},
    'A',
    'B'
);

// Drivetrain / LemLib config
lemlib::Drivetrain drivetrain(&L, &R, 14.5, lemlib::Omniwheel::NEW_325, 480, 2);

// Odom wheels
lemlib::TrackingWheel horizontal_tracking_wheel(&Xaxis, lemlib::Omniwheel::NEW_2, -0.1875);
lemlib::TrackingWheel vertical_tracking_wheel(&Yaxis, lemlib::Omniwheel::NEW_2, -1.125);

// Odom sensors
lemlib::OdomSensors sensors(&vertical_tracking_wheel, nullptr, &horizontal_tracking_wheel, nullptr, &inertial19);

// PID settings
lemlib::ControllerSettings lateral_controller(10,0,3,3,1,100,3,500,20);
lemlib::ControllerSettings angular_controller(2,0,10,3,1,100,3,500,0);

// Chassis
lemlib::Chassis chassis(drivetrain, lateral_controller, angular_controller, sensors);



// ----------------- ODOM DEBUG TASK -----------------
void odomDebug(void*) {
    while(true) {
        lemlib::Pose pose = chassis.getPose();
        pros::lcd::print(1, "X: %.2f", pose.x);
        pros::lcd::print(2, "Y: %.2f", pose.y);
        pros::lcd::print(3, "H: %.2f", pose.theta);
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
    chassis.setPose(0,0,0);

    // Start Odom debug task
    odomTask = new pros::Task(odomDebug);


}

// ----------------- DISABLED -----------------
void disabled() {}

// ----------------- COMPETITION INIT -----------------
void competition_initialize() {}

// ----------------- AUTONOMOUS -----------------
void autonomous() {
    chassis.setPose(0,0,0);



    pros::delay(15000); // keep auton alive for skills
}

// ----------------- OPERATOR CONTROL -----------------
void opcontrol() {
	new pros::Task(DriveTrainControls);
    new pros::Task(IntakeControls);
    new pros::Task(OutakeControls);
    new pros::Task(DrivePTOcontrols);
    new pros::Task(Loadercontrols);
    new pros::Task(liftercontrols);
    new pros::Task(Hookcontrols);
    while(true) {
        if(master.is_connected()) master.print(0,0,"MASTER");
        if(slave.is_connected()) slave.print(0,0,"SLAVE");
        pros::delay(20);
    }
}