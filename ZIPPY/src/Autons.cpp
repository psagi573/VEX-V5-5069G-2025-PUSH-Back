#include "Autons.h"
#include "Motion.h"
#include "pros/rtos.hpp"
#include "PTO.h"
#include <cmath>
#include <algorithm>
#include "main.h"


void Skills(){
    drive(24,1000);
    pros::delay(500);
    chassis.turnToHeading(90,1000);
}