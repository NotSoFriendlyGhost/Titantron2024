#include "main.h"

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

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	master.clear();
	master.set_text(0,0,"Calibrating IMU...");
	imu.reset(true);
	master.clear_line(0);
	master.rumble(".");
	master.set_text(0,0,"Ready to roll");

	leftFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	leftBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	rightFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	rightBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

	intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	flywheel.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	pros::lcd::register_btn1_cb(on_center_button);
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
void competition_initialize() {}

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
void autonomous() {}

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
	master.set_text(1,0,"Flywheel Velocity: 50%");
	while (true) {
		arcadeDrive();
		
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
			intake.move_voltage(12000);
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
			intake.move_voltage(-12000);
		else
			intake.brake();

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
			flywheel.move_velocity(600*flywheelVelocity);
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
			flywheel.move_velocity(-600*flywheelVelocity);
		else flywheel.brake();

		if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)){
			if(flywheelVelocity==0.5){
				flywheelVelocity = 0.75;
				master.clear_line(1);
				master.set_text(1,0,"Flywheel Velocity: 75%");
			}
			else{
				flywheelVelocity = 0.5;
				master.clear_line(1);
				master.set_text(1,0,"Flywheel Velocity: 50%");
			}
		}

		if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) 
			wingState = !wingState;
		wings.set_value(wingState);
	
		pros::delay(2);
	}
}
