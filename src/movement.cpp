#include "main.h"
#include "api.h"
#include "pros/motors.hpp"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp"
#include "devices.h"
#include "auton_routes.h"
#include "movement.h"
#include <string>
#include <iostream>
#include <thread>
#include <algorithm>
#include <atomic>
#include <memory>
#include "pros/rtos.hpp"


void Intake(double direction)
{
    bottomStage.set_brake_mode(MOTOR_BRAKE_HOLD);
    midStage.set_brake_mode(MOTOR_BRAKE_HOLD);
    topStage.set_brake_mode(MOTOR_BRAKE_HOLD);
    bottomStage.move(direction * 127);
    midStage.move(direction * 127);
    topStage.move(direction * 127);
}
void scoreMid(){
    bottomStage.set_brake_mode(MOTOR_BRAKE_HOLD);
    midStage.set_brake_mode(MOTOR_BRAKE_HOLD);
    topStage.set_brake_mode(MOTOR_BRAKE_HOLD);
    bottomStage.move(127);
    midStage.move(127);
    topStage.move(-80);
}

void stopIntake()
{
    bottomStage.set_brake_mode(MOTOR_BRAKE_HOLD);
    midStage.set_brake_mode(MOTOR_BRAKE_HOLD);
    topStage.set_brake_mode(MOTOR_BRAKE_HOLD);
    bottomStage.brake();
    midStage.brake();
    topStage.brake();
}
void outake(int time)
{
    bottomStage.move(-127);//intake out then in
    midStage.move(-127);
    topStage .move(-50);

    pros::delay(time);

}
void outakeSkills(int time)
{
    bottomStage.move(-50);//intake out then in
    midStage.move(-50);
    topStage .move(-10);

    pros::delay(time);

}
void scoreMidSkills(){
    bottomStage.set_brake_mode(MOTOR_BRAKE_HOLD);
    midStage.set_brake_mode(MOTOR_BRAKE_HOLD);
    topStage.set_brake_mode(MOTOR_BRAKE_HOLD);
    bottomStage.move(100);
    midStage.move(100);
    topStage.move(-30);
}
// Improved slew rate limiting for smoother control
double slewStep = 30.0;  // Increased for better responsiveness
double slewRate = 0.5; // Maximum change per iteration (15% of difference)

double slew(double val, double fwdVal)
{
    static double prevVal = 0;
    static double prevFwdVal = 0;

    // Reset slew if target direction changes significantly
    if ((fwdVal >= 0 && prevFwdVal < 0) || (fwdVal < 0 && prevFwdVal >= 0))
    {
        prevVal = 0;
    }
    prevFwdVal = fwdVal;

    // Calculate the difference between target and current
    double difference = val - prevVal;

    // If difference is small, just return the target
    if (fabs(difference) < 0.5)
    {
        prevVal = val;
        return val;
    }

    // Calculate slew rate based on difference (adaptive)
    double currentSlewStep = slewStep + (fabs(difference) * slewRate);

    // Apply slew rate limiting
    if (difference > 0)
    {
        // Positive direction
        if (prevVal + currentSlewStep < val)
        {
            prevVal += currentSlewStep;
        }
        else
        {
            prevVal = val;
        }
    }
    else
    {
        // Negative direction
        if (prevVal - currentSlewStep > val)
        {
            prevVal -= currentSlewStep;
        }
        else
        {
            prevVal = val;
        }
    }

    return prevVal;
}

// Drive PID gains (made global for monitoring)
double drive_kP = 0.13; 
double drive_kI = 0.00; 
double drive_kD = 0.41;

void drivePID(double fwdVal, double maxSpeedPercent, double timeout)
{
    
    double kP = drive_kP; 
    double kI = drive_kI; 
    double kD = drive_kD; 

    const double diameter = 3.25;
    const double pi = 3.14159;
    const double outputGear = 48;
    const double inputGear = 36;

    double num = fwdVal;                                       // leave this one alone
    double denom = (diameter * pi) * (inputGear / outputGear); // leave this one alone
    double target = (num / denom) * 360;                       // leave this one alone
    
    // Reset motor positions to zero
    left_motors.tare_position();
    right_motors.tare_position();
    mBackLeft.tare_position();
    mBackRight.tare_position();
    mFrontLeft.tare_position();
    mFrontRight.tare_position();
    mMidLeft.tare_position();
    mMidRight.tare_position();

    double startTime = pros::millis();
    double error = 0;
    double prevError = 0;
    double integral = 0;
    
    // Dynamic goal tracking (proportional to distance)
    const double pollingRate = 20; // ms - consistent with sister team
    
    // Exit conditions: position error only (degrees)
    const double errorThreshold = 6.0; // degrees - position threshold
    int inGoal = 0;
    const int goalsNeeded = 1; // Only need 1 iteration when conditions are met for faster exit
    
    // Clamp and convert maxSpeedPercent (0-100) -> max motor units (0-127)
    if (maxSpeedPercent < 0)
        maxSpeedPercent = 0;
    if (maxSpeedPercent > 100)
        maxSpeedPercent = 100;
    double maxMotor = (maxSpeedPercent / 100.0) * 127.0;

    bool hasMoved = false; // Track if robot has started moving (prevent immediate exit)
    
    while (inGoal < goalsNeeded)
    {
        // Use the MEDIAN of all 6 drivetrain motor positions for robustness
        double positions[6] = {
            mBackLeft.get_position(), mFrontLeft.get_position(), mMidLeft.get_position(),
            mBackRight.get_position(), mFrontRight.get_position(), mMidRight.get_position()
        };
        // partial sort to find middle two for even count (6): indices 2 and 3 after nth_element passes
        std::nth_element(positions, positions + 2, positions + 6);
        std::nth_element(positions + 3, positions + 3, positions + 6);
        double medianPos = (positions[2] + positions[3]) / 2.0;
        double processVariable = medianPos * 360;
        
        error = target - processVariable;
        
        // Track if robot has moved significantly OR is close to target (prevents immediate exit at start)
        // For small movements, check if we're close to target instead of requiring large movement
        // Also check if enough time has passed (prevents false exits at start)
        if (fabs(processVariable) > 20 || fabs(error) < errorThreshold * 2 || (pros::millis() - startTime) > 100) {
            hasMoved = true;
        }

        // Proportional term
        double P = error * kP;
        
        // Integral term with anti-windup 
        integral += error;
        double I = integral * kI;
        I = std::clamp(I, -50.0, 50.0); // Clamp integral contribution
        
        // Derivative term 
        double D = ((error - prevError) / pollingRate) * kD;
        
        // Calculate total PID output
        double motorPower = P + I + D;
        
        // Apply slew only at start for smooth acceleration
        if ((pros::millis() - startTime) < 300) {
            motorPower = slew(motorPower, fwdVal);
        }
        
        // Clamp output
        motorPower = std::clamp(motorPower, -maxMotor, maxMotor);

        // Move motors
        left_motors.move(motorPower);
        right_motors.move(motorPower);

        // Fast exit condition: position error is small AND robot has moved
        // This allows immediate exit when robot has reached the target
        if (hasMoved && fabs(error) < errorThreshold)
        {
            inGoal++;
            // Exit immediately once condition is met (no need to wait for multiple iterations)
            if (inGoal >= goalsNeeded) {
                break;
            }
        }
        else
        {
            inGoal = 0; // Reset if conditions not met
        }

        // Timeout safety - break immediately if timeout reached
        if ((pros::millis() - startTime) >= timeout)
        {
            break;
        }

        prevError = error;
        
        // Consistent polling rate
        pros::delay(pollingRate);
    }
    
    // Stop motors once goal is reached
    left_motors.brake();
    right_motors.brake();
}
void turnToHeadingSmart(float theta, int timeout, TurnToHeadingParams params, bool async)
{
    // Get current heading
    float currentHeading = chassis.getPose().theta;
    
    // Calculate angle difference
    float angleDiff = theta - currentHeading;
    
    // Normalize to [-180, 180]
    while (angleDiff > 180) angleDiff -= 360;
    while (angleDiff < -180) angleDiff += 360;
    
    // For small turns, automatically apply minSpeed if not already set
    // This ensures the robot has enough power to overcome friction and motor deadband
    if (params.minSpeed == 0)
    {
        float absAngleDiff = fabs(angleDiff);
        
        // Very small turns (< 15 degrees) need higher minSpeed to overcome friction
        if (absAngleDiff < 15.0)
        {
            params.minSpeed = 40; // Higher minimum speed for very small turns
            params.earlyExitRange = 2; // Tighter exit range for precision
        }
        // Small to medium turns (15-30 degrees) need moderate minSpeed
        else if (absAngleDiff < 30.0)
        {
            params.minSpeed = 30; // Moderate minimum speed
            params.earlyExitRange = 3;
        }
    }
    
    // Call the actual turnToHeading function with async parameter
    chassis.turnToHeading(theta, timeout, params, async);
}

