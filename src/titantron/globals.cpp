#include "main.h"
#include <fstream>


Drivetrain drive(-1,-12,10,18, 3.25);

pros::Motor intake(2);
pros::Motor flywheel(15, pros::E_MOTOR_GEAR_BLUE, true);
pros::ADIDigitalOut wings('A', false);

pros::Controller master (CONTROLLER_MASTER);
pros::Imu imu(13);

float flywheelVelocity = 0.5;
bool wingState = 0;

std::ofstream ofs; //Used for recording
bool recording = false;

// TODO: Lifter setup - wait for lifter build