#include "globals.hpp"
#include "main.h"
#include <string>

/**
 *
 * Sets up four motor drive train by inputting port numbers. Entering a negative number reverses the motor.
 *
*/
Drivetrain::Drivetrain(int leftA, int leftB, int rightA, int rightB){
    bool reversed;
    reversed = (leftA<0);
    leftFront = new pros::Motor(leftA,pros::E_MOTOR_GEAR_GREEN,reversed,pros::E_MOTOR_ENCODER_DEGREES);
    reversed = (leftB<0);
    leftBack = new pros::Motor(leftB,pros::E_MOTOR_GEAR_GREEN,reversed,pros::E_MOTOR_ENCODER_DEGREES);
    reversed = (rightA<0);
    rightFront = new pros::Motor(rightA,pros::E_MOTOR_GEAR_GREEN,reversed,pros::E_MOTOR_ENCODER_DEGREES);
    reversed = (rightB<0);
    rightBack = new pros::Motor(rightB,pros::E_MOTOR_GEAR_GREEN,reversed,pros::E_MOTOR_ENCODER_DEGREES);
}

void Drivetrain::resetDriveEncoders(){
    leftFront->tare_position();
    leftBack->tare_position();
    rightBack->tare_position();
    rightFront->tare_position();
};

void Drivetrain::arcadeDrive(){
    int power = master.get_analog(ANALOG_LEFT_Y);
    power = opcontrolLeftCurve(power);
    int turn = master.get_analog(ANALOG_RIGHT_X);
    turn = opcontrolRightCurve(turn);
    int left = power + turn;
    int right = power - turn;
    leftFront->move(left);
    leftBack->move(left);
    rightFront->move(right);
    rightBack->move(right);
}

void Drivetrain::setBrakeMode(pros::motor_brake_mode_e brakeMode){
    leftFront->set_brake_mode(brakeMode);
    leftBack->set_brake_mode(brakeMode);
    rightFront->set_brake_mode(brakeMode);
    rightBack->set_brake_mode(brakeMode);
}

void Drivetrain::driveForward(){
    resetDriveEncoders();
    leftFront->move_absolute(253.864,100);
    leftBack->move_absolute(253.864,100);
    rightFront->move_absolute(253.864,100);
    rightBack->move_absolute(253.864,100);
    master.clear_line(0);
    pros::delay(1000);
    std::string position = std::to_string(leftFront->get_position());
    
    master.set_text(0,0,position);
    pros::delay(100);
}

void Drivetrain::driveBackward(){
    leftFront->move_relative(-360,100);
    leftBack->move_relative(-360,100);
    rightFront->move_relative(-360,100);
    rightBack->move_relative(-360,100);
}