#include "main.h"
#include "auton.h"
#include "devices.h"
#include "movement.h"






void fullAWPLeft(int i){
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
drivePID(29.832, 100, 3000);
chassis.turnToHeading(270, 600);
drivePID(9.723, 100, 1000);
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
drivePID(15.782, 1000);
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
    
}
void tylerAuton(int i){
   
}
void skills(int i){
chassis.setPose(0,0,180);
loader.set_value(HIGH);
Intake(1);
drivePID(30.495, 100, 3000);
chassis.turnToHeading(270, 1000);
drivePID(11.491, 100, 2000);
drivePID(-2, 50, 500);
drivePID(2,50, 500);
pros::delay(200);
drivePID(-23.423, 100, 3000);
loader.set_value(LOW);
chassis.moveToPose(12.153, -30.494, 270, 5000);
chassis.turnToHeading(270, 1000);
drivePID(-63.64, 100, 6500);
chassis.turnToHeading(180, 1000);
drivePID(-12.374, 100, 1500);
chassis.turnToHeading(90, 1000);
drivePID(-18.783, 100, 2000);
hood.set_value(HIGH);
loader.set_value(HIGH);
pros::delay(700);
hood.set_value(LOW);
drivePID(27.842, 100, 3000);
chassis.turnToHeading(29.055, 100);
drivePID(28.438, 100);
chassis.turnToHeading(358.898, 100);
drivePID(68.956, 100);
chassis.turnToHeading(90.807, 100);
drivePID(15.691, 100);
chassis.turnToHeading(270, 100);
drivePID(29.168, 100);
chassis.turnToHeading(339.444, 100);
drivePID(15.104, 100);
chassis.turnToHeading(269.909, 100);
drivePID(69.717, 100);
chassis.turnToHeading(180, 100);
drivePID(13.479, 100);
chassis.turnToHeading(90, 100);
drivePID(14.584, 100);
chassis.turnToHeading(269.549, 100);
drivePID(28.064, 100);
chassis.turnToHeading(89.545, 100);
drivePID(27.843, 100);
chassis.turnToHeading(238.975, 100);
drivePID(35.585, 100);
chassis.turnToHeading(186.546, 100);
drivePID(13.568, 100);
chassis.turnToHeading(180, 100);
drivePID(22.318, 100);
chassis.turnToHeading(0, 100);


}
void skillsNew(int i){
  
}
void leftPush(int i){
chassis.setPose(0,0,0);
loader.set_value(HIGH);
Intake(1);
drivePID(30.494, 100, 3000);
chassis.turnToHeading(270, 1000);
drivePID(10.607, 100, 2000);
drivePID(-2, 50, 500);
drivePID(2,50, 500);
pros::delay(200);
drivePID(-28.505, 100, 2000);
loader.set_value(LOW);
hood.set_value(HIGH);
pros::delay(500);
hood.set_value(LOW);
chassis.turnToHeading(161.719, 1000);
drivePID(26.064, 70, 3000);
chassis.turnToHeading(137.386, 1000);
drivePID(15.013, 100, 2000);
Intake(-1);
pros::delay(300);
stopIntake();
drivePID(-14.552, 80, 2000);
chassis.turnToHeading(330.751, 1000);
chassis.moveToPose(-17.236, -22.097, 90, 5000);
chassis.turnToHeading(90, 1000);
drivePID(20.993, 100, 2000);
}
void rightPush(int i){
chassis.setPose(0,0,180);
loader.set_value(HIGH);
Intake(1);
drivePID(30.494, 100, 3000);
chassis.turnToHeading(270, 1000);
drivePID(10.607, 100, 1000);
drivePID(-2, 50, 500);
drivePID(2,50, 500);
pros::delay(200);
drivePID(-28.505, 100, 3000);
loader.set_value(LOW);
hood.set_value(HIGH);
pros::delay(700);
hood.set_value(LOW);
chassis.turnToHeading(18.281, 1000);
drivePID(26.064, 70, 3000);
chassis.turnToHeading(42.614, 1000);
drivePID(15.013, 100, 3000);
Intake(-1);
pros::delay(100);
drivePID(14.552, 100);
chassis.turnToHeading(205.615, 100);
chassis.moveToPose(17.236, -22.097, 90, 5000);
chassis.turnToHeading(90, 100);
drivePID(20.329, 100, 1000);
}