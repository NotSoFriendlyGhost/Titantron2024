#include "main.h"

pros::Motor leftFront(1,pros::E_MOTOR_GEARSET_18,true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor leftBack(12,pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor rightFront(10, pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor rightBack(18, pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor intake(5);
pros::Motor flywheel(15, true);
pros::ADIDigitalOut wings('A', false);

pros::Controller master (CONTROLLER_MASTER);
pros::Imu imu(8);