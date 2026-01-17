#include "main.h"

// Controller definitions
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller slave(pros::E_CONTROLLER_PARTNER);

// Note: Gearsets are ==== pros::E_MOTOR_GEAR_600 (6:1) -- pros::E_MOTOR_GEAR_200 (18:1) -- pros::E_MOTOR_GEAR_100 (36:1)

// Motor definitions
//left side motors
pros::Motor L1(12, pros::MotorGears::blue);
pros::Motor L2(14, pros::MotorGears::blue);
pros::Motor PTOL3(13, pros::MotorGears::blue);
pros::Motor LIntake(11, pros::MotorGears::blue);
//right side motors
pros::Motor R6(-16, pros::MotorGears::blue);
pros::Motor R7(-19, pros::MotorGears::blue);
pros::Motor PTOR8(-18, pros::MotorGears::blue);
pros::Motor RIntake(-20, pros::MotorGears::blue);


pros::MotorGroup L({12, 14, 13}, pros::MotorGears::blue); //L1, L2, PTOL3
pros::MotorGroup R({-16, -19, -18}, pros::MotorGears::blue); //R6, R7, PTOR8
pros::MotorGroup DrivePTO({13, -18}, pros::MotorGears::blue); //PTOL3, PTOR8
pros::MotorGroup IntakePTO({11, -20}, pros::MotorGears::blue); //LIntake, RIntake
pros::MotorGroup Drivetrain({12, 13, -16, -20}, pros::MotorGears::blue); //L1, L2, R6, R7
pros::MotorGroup Left({12, 13}, pros::MotorGears::blue); //L1, L2
pros::MotorGroup Right({-19, -20}, pros::MotorGears::blue); //R6, R7
pros::MotorGroup Intake2({-18, 3}, pros::MotorGears::blue); //LIntake, RIntake
pros::MotorGroup Intake4({-18, 3, 1, -14}, pros::MotorGears::blue); //LIntake, RIntake, PTOR8, PTOL3

// Sensor definitions
pros::Imu inertial19(6);
pros::Rotation Yaxis(-21);
pros::Rotation Xaxis(-9);
pros::Optical Color(4);

// Pneumatic definitions
pros::adi::Pneumatics DrivePTOPiston('H', true);
pros::adi::Pneumatics IntakePTOPiston('G', true);
pros::adi::Pneumatics Funnel('F', true);
pros::adi::Pneumatics Doublepark('E', true);
pros::adi::Pneumatics Lifter('D', true);
pros::adi::Pneumatics Loader('C', true);
pros::adi::Pneumatics Hook('B', true);


robot-config.cpp