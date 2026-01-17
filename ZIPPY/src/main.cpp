#include "main.h"





PTOManager pto(
    {&L1, &L2, &PTOL3, &LIntake},
    {&R6, &R7, &PTOR8, &RIntake},
    'A',
    'B'
);


//lemlib config
///////////////////////config at a later time///////////////////////
// drivetrain
lemlib::Drivetrain drivetrain(&Left, // left motor group
                              &Right, // right motor group
                              14.5, // 14.5 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 3.25" omnis
                              480, // drivetrain rpm is 480
                              0 // horizontal drift is 2 (for now)
);



//////////Configuration of ODOMETRY////////////
// rotaion sensors
// horizontal tracking wheel
lemlib::TrackingWheel horizontal_tracking_wheel(&Xaxis, lemlib::Omniwheel::NEW_2, -0.1875);///the -5.75 is the offset from the center of rotation, needs to be measured
// vertical tracking wheel
lemlib::TrackingWheel vertical_tracking_wheel(&Yaxis, lemlib::Omniwheel::NEW_2, -1.125);///the -4.5 is the offset from the center of rotation, needs to be measured

//////////Configuration of ODOMETRY////////////
lemlib::OdomSensors sensors(&vertical_tracking_wheel, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            &horizontal_tracking_wheel, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &inertial19 // inertial sensor
);




//////////Configuration of PID////////////
// lateral PID controller
lemlib::ControllerSettings lateral_controller(10, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              3, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// create the chassis
lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}
void odomDebug(void*) {
	pros::lcd::clear_line(1);
	pros::lcd::clear_line(2);
	pros::lcd::clear_line(3);
    while (true) {
        lemlib::Pose pose = chassis.getPose();
        pros::lcd::print(1, "X: %.2f", pose.x);
        pros::lcd::print(2, "Y: %.2f", pose.y);
        pros::lcd::print(3, "H: %.2f", pose.theta);
        pros::delay(50);
    }
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */


 pros::Task* odomTask = nullptr;

void initialize() {
    pros::lcd::initialize();

    inertial19.reset();
    while (inertial19.is_calibrating()) {
        pros::delay(10);
    }

    Xaxis.reset_position();
    Yaxis.reset_position();

    chassis.calibrate();



}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {

    if (!odomTask) {
        odomTask = new pros::Task(odomDebug);
    }
    }

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
 

void autonomous() {
if (!odomTask) odomTask = new pros::Task(odomDebug);
chassis.setPose(0, 0, 0);

    // robot movement here if desired
    pros::delay(15000); // keep auton alive for skills
/*
	L.set_brake_mode_all(MotorBrake::brake);
	R.set_brake_mode_all(MotorBrake::brake);

    
    // set position to x:0, y:0, heading:0
    chassis.setPose(0, 0, 0);
    // turn to face heading 90 with a very long timeout
    chassis.turnToHeading(90, 100000);*/
	          
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol() {

    pros::Controller master(pros::E_CONTROLLER_MASTER);

    while (true) {
        if (master.is_connected()) {
            master.print(0, 0, "MASTER");
        }

        if (slave.is_connected()) {
            slave.print(0, 0, "SLAVE");
        }

		
		new pros::Task(DriveTrainControls);
		new pros::Task(IntakeControls);
		new pros::Task(OutakeControls);
		new pros::Task(DrivePTOcontrols);
		new pros::Task(Loadercontrols);
		new pros::Task(liftercontrols);
		new pros::Task(Hookcontrols);

		new pros::Task(slavePTOcontrol);
		new pros::Task(slaveWINGcontrol);
		new pros::Task(slaveLOADERcontrol);
        pros::delay(20);  // REQUIRED
    }
}
