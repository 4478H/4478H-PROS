#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "auton_routes.h"
#include "devices.h"
#include "movement.h"
#include "opticalAlign.h"






void fullAWPLeft(int i){
chassis.setPose(0,0,180);
loader.set_value(HIGH);
Intake(1);
drivePID(30.053, 100, 3000);
chassis.turnToHeading(270, 1000);
drivePID(10.165, 100, 2000);
drivePID(-2,100,500 );
drivePID(2,100, 500);
pros::delay(200);
drivePID(-28.506, 100, 3000);
loader.set_value(LOW);
hood.set_value(HIGH);
pros::delay(500);
hood.set_value(LOW);
chassis.turnToHeading(163.156, 1000);
drivePID(25.166, 100, 3000);
chassis.turnToHeading(180, 1000);
drivePID(45.087, 100, 3500);
chassis.turnToHeading(45, 1000);
drivePID(13.907, 100, 2000);
Intake(-1);
pros::delay(200);
Intake(1);
drivePID(-13.907, 100, 2000);
chassis.turnToHeading(225.898, 1000);
chassis.moveToPose(0.221, -63.64, 270,3000);
loader.set_value(HIGH);
pros::delay(200);
drivePID(11.491, 100, 1000);
drivePID(-2, 40, 500);
drivePID(2, 70, 500);
pros::delay(200);
drivePID(-27.18, 100);
hood.set_value(HIGH);
}
void fullAWPRight(int i){
chassis.setPose(0,0,180);
loader.set_value(HIGH);
Intake(1);
drivePID(30.1, 100, 3000);
chassis.turnToHeading(270, 900);
drivePID(10.2, 100, 1000);
drivePID(-2, 50, 500);
drivePID(2,50, 500);
pros::delay(200);
drivePID(-28.064, 100, 3000);
hood.set_value(HIGH);
loader.set_value(LOW);
pros::delay(500);
hood.set_value(LOW);
chassis.turnToHeading(18.954, 700);
drivePID(23.13, 70, 3000);
chassis.turnToHeading(0, 1000);
drivePID(48.837, 70, 3000);
chassis.turnToHeading(316.685, 700);
drivePID(-15.628, 100, 2000);
stopIntake();
scoreMid();
pros::delay(50);
Intake(1);
drivePID(15.782, 100, 2000);
chassis.moveToPose(25.854, 40.659, 316, 5000);
chassis.moveToPose(3.977, 63.861, 270, 5000);
loader.set_value(HIGH);
pros::delay(200);
drivePID(14.142, 100, 2000);
drivePID(-2, 50, 500);
drivePID(2,50, 500);
pros::delay(200);
drivePID(-28.726, 100, 3000);
hood.set_value(HIGH);
}
void odomAWP(int i){
    
}
void odomAWPHigh(int i){
drivePID(4, 20,3000);
}
void skills(int i){
chassis.setPose(0,0,180);
wing.set_value(HIGH);
Intake(1);
drivePID(31.8, 50, 3000);
chassis.turnToHeading(270, 1500);
loader.set_value(HIGH);
pros::delay(200);
drivePID(11, 50, 2500);
drivePID(-2, 50, 500);
drivePID(3.1,50, 500);
pros::delay(500);
drivePID(-19.423, 100, 3000);
loader.set_value(LOW);
chassis.turnToHeading(180, 1500);
drivePID(14.5, 50, 5000);
chassis.turnToHeading(90, 1500);
chassis.turnToHeading(108, 1500);
drivePID(25, 50, 2000);
chassis.turnToHeading(93, 1500);
drivePID(68, 50, 6000);
chassis.turnToHeading(180, 1500);
drivePID(-11.5, 50, 3500);
chassis.turnToHeading(90, 1500);
drivePID(-13.5, 50, 3000);
outake(200);
Intake(1);
hood.set_value(HIGH);
pros::delay(1200);
hood.set_value(LOW);
loader.set_value(HIGH);
pros::delay(200);
chassis.turnToHeading(90, 1500);
drivePID(30, 50, 3000);
drivePID(-2, 50, 500);
drivePID(3.3,50, 500);
pros::delay(500);
chassis.moveToPose(23.5, -0.6, 90, 5000);
outake(200);
Intake(1);
hood.set_value(HIGH);
pros::delay(1200);
hood.set_value(LOW);
loader.set_value(HIGH);
chassis.moveToPose(35.5, 27.4, 0, 5000);
drivePID(67.617, 50, 4000);
chassis.turnToHeading(90, 1000);
loader.set_value(HIGH);
pros::delay(200);
drivePID(13.923, 100, 1500);
drivePID(-2, 50, 500);
drivePID(2,50, 500);
pros::delay(200);
drivePID(-28.505, 100, 2500);
loader.set_value(LOW);
hood.set_value(HIGH);
pros::delay(700);
hood.set_value(LOW);
chassis.moveToPose(67.838, 77.119, 270, 5000);
chassis.turnToHeading(270, 1000);
drivePID(61.872, 100, 4000);
chassis.turnToHeading(180, 1000);
drivePID(14.142, 100, 2000);
chassis.turnToHeading(270, 1000);
loader.set_value(HIGH);
pros::delay(200);
drivePID(17.679, 100, 3000);
drivePID(-2, 50, 500);
drivePID(2,50, 500);
pros::delay(200);
drivePID(-29.39, 100, 3000);
loader.set_value(LOW);
hood.set_value(HIGH);
chassis.moveToPose(-12.153, 43.31, 188, 5000);
chassis.turnToHeading(188, 1000);
drivePID(12.938, 100, 2000);
Intake(-1);
chassis.turnToHeading(180, 100);
drivePID(19.004, 100, 2000);
}
void skillsNew(int i){
chassis.setPose(0,0,0);
Intake(1);
//go through prak zone and pick up balls
drivePID(35.937, 100, 5500);


//move to middle picking up one more blue then score 7 mid
chassis.moveToPose(33.146, 41.764, 135, 5000);
stopIntake();
chassis.turnToHeading(315, 1000);
drivePID(-24.219, 50, 3000);
scoreMidSkills();
pros::delay(300);
stopIntake();


//move to first matchloader then hed to other side
drivePID(47.813, 50, 5000);
chassis.turnToHeading(270,1000);
Intake(1);
loader.set_value(HIGH);
pros::delay(200);
drivePID(14.142, 50, 5000);
pros::delay(200);
drivePID(26.075, 50, 3000);
chassis.moveToPose(48.835, 72.258, 270, 5000);
drivePID(-49.721, 50, 5000);


//move into goal and score first matchloader balls
chassis.moveToPose(92.145, 58.337, 90, 5000);
hood.set_value(HIGH);
pros::delay(800);
hood.set_value(LOW);


//move to second matchloader and pick up balls then hed back to long goal to score those balls
drivePID(30.494, 50, 3000);
pros::delay(200);
drivePID(30.053, 50, 3000);
loader.set_value(LOW);
hood.set_value(HIGH);
pros::delay(800);
hood.set_value(LOW);


//move to second park zone then go through and pick up balls
chassis.moveToPose(125.733, 28.063, 180, 5000);
drivePID(32.483, 50, 3000);
drivePID(21.213, 50, 2500);


//move to low middle goal grabing one more red ball on the way
drivePID(-11.27, 50, 1500);
chassis.turnToHeading(270, 1000);
drivePID(15.028, 50, 1500);
chassis.moveToPose(96.344, -11.491, 348, 5000);
stopIntake();
drivePID(48.233, 50, 5000);
chassis.turnToHeading(224.526, 1000);
drivePID(18.907, 50, 1500);
outake(500);


//move to third matchloader
drivePID(-11.567, 50, 1500);
chassis.turnToHeading(165.44, 1000);
drivePID(70.318, 50, 7000);
chassis.turnToHeading(85.764, 1000);
Intake(1);
loader.set_value(HIGH);
pros::delay(200);


//move to first side of feild then score blocks in high goal
drivePID(23.93, 50, 3000);
chassis.moveToPose(81.471, -49.277, 90, 5000);
drivePID(-57.453, 50, 4000);
chassis.moveToPose(33.079, -35.576, 270, 5000);
hood.set_value(HIGH);
pros::delay(700);
hood.set_value(LOW);


//move to last matchloader and get blocks
drivePID(29.389, 50, 3000);
pros::delay(200);
drivePID(-28.947, 50, 3000);


//score final blocks into long goal
hood.set_value(HIGH);
pros::delay(700);
hood.set_value(LOW);


//park
chassis.moveToPose(0.375, -10.165, 0, 5000);
drivePID(20.992, 50, 3000);
}
void leftPush(int i){
wing.set_value(HIGH);
chassis.setPose(0,0,0);
Intake(1);
drivePID(31, 100, 3000);
chassis.turnToHeading(270, 1000);
loader.set_value(HIGH);
drivePID(11.8, 100, 2500);
/*
drivePID(-2, 100, 500);
drivePID(3,100, 500);
*/
alignToLongGoal();
/*
drivePID(-30, 100, 1800);
*/
loader.set_value(LOW);
outake(200);
hood.set_value(HIGH);
Intake(1);
pros::delay(900);
hood.set_value(LOW);
chassis.turnToHeading(154.719, 1500);
drivePID(29.5,40, 3000);
chassis.turnToHeading(180, 1000);
drivePID(-12.5, 80, 3000);
chassis.turnToHeading(-38, 1000);
drivePID(-31, 70, 2000);
stopIntake();
scoreMid();
pros::delay(300);
stopIntake();
chassis.turnToHeading(-60, 1000);
drivePID(30.552, 80, 2000);
chassis.moveToPose(31.5, 13.4, 90, 5000);
}
void rightPush(int i){
chassis.setPose(0,0,180);
Intake(1);
drivePID(32.2, 70, 3000);
chassis.turnToHeading(270, 1000);
loader.set_value(HIGH);
pros::delay(200);
drivePID(12.4, 100, 2000);
/*
drivePID(-14, 70, 3000);
*/
alignToLongGoal();
outake(200);
Intake(1);
loader.set_value(LOW);
hood.set_value(HIGH);
pros::delay(1700);
hood.set_value(LOW);
chassis.turnToHeading(10.281, 2000);
load();
drivePID(26.064, 70, 3000);
drivePID(-7, 80, 500);
chassis.turnToHeading(42.614, 1000);
Intake(-1);
drivePID(17.013, 100, 3000);
pros::delay(100);
drivePID(4.552, 100, 3000);

}
void PIDTesting(int i){

chassis.setPose(0,0,270);
/*
chassis.turnToHeading(180,1000);

pros::delay(1000);
chassis.turnToHeading(180, 1000);
pros::delay(1000);
chassis.turnToHeading(0, 1000);

//drivePID(24, 100, 3000);
drivePID(70, 100, 10000);
*/
alignToLongGoal();
}

void stopAuton(){
	// Stop all motors
	all_motors.brake();
	intake.brake();
	bottomStage.brake();
	midStage.brake();
	topStage.brake();
	
	// Retract all pneumatics
	hood.set_value(LOW);
	loader.set_value(LOW);
	wing.set_value(LOW);
	midDescore.set_value(LOW);
	
	// Halt autonomous
	while(true){
		pros::delay(10);
	}
}