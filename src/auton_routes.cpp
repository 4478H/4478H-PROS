#include "main.h"
#include "auton_routes.h"
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
drivePID(63.64, 100, 5000);
chassis.turnToHeading(180, 1000);
drivePID(-12.374, 100, 1500);
chassis.turnToHeading(90, 1000);
drivePID(-11.932, 100, 1500);
hood.set_value(HIGH);
pros::delay(700);
hood.set_value(LOW);
loader.set_value(HIGH);
pros::delay(200);
drivePID(31.16, 100, 3000);
drivePID(-31.379, 100, 3000);
chassis.moveToPose(92.587, -3.315, 0, 5000);
chassis.turnToHeading(0, 1000);
drivePID(67.617, 100, 4000);
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
chassis.setPose(0,0,180);
loader.set_value(HIGH);
Intake(1);
drivePID(30.495, 100, 3000);
chassis.turnToHeading(270, 1000);
drivePID(11.491, 100, 1500);
drivePID(-2, 50, 500);
drivePID(2,50, 500);
pros::delay(200);
loader.set_value(LOW);
drivePID(-20.108, 100, 3000);
chassis.turnToHeading(137.246, 1000);
drivePID(15.95, 100, 2000);
chassis.turnToHeading(90, 1000);
drivePID(68.945, 100, 4000);
chassis.turnToHeading(0, 100);
drivePID(12.374, 100);
chassis.turnToHeading(270, 100);
drivePID(11.932, 100);
chassis.turnToHeading(89.187, 100);
drivePID(31.16, 100);
chassis.turnToHeading(269.597, 100);
drivePID(31.379, 100);
chassis.turnToHeading(31.103, 100);
drivePID(31.227, 100);
chassis.turnToHeading(0, 100);
drivePID(67.617, 100);
chassis.turnToHeading(90.909, 100);
drivePID(13.923, 100);
chassis.turnToHeading(270, 100);
drivePID(28.505, 100);
chassis.turnToHeading(322.058, 100);
drivePID(16.532, 100);
chassis.turnToHeading(270.205, 100);
drivePID(61.872, 100);
chassis.turnToHeading(180, 100);
drivePID(14.142, 100);
chassis.turnToHeading(270.716, 100);
drivePID(17.679, 100);
chassis.turnToHeading(89.569, 100);
drivePID(29.39, 100);
chassis.turnToHeading(235.726, 100);
drivePID(36.1, 100);
chassis.turnToHeading(187.853, 100);
drivePID(12.938, 100);
chassis.turnToHeading(180, 100);
drivePID(19.004, 100);
chassis.turnToHeading(308.077, 100);


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