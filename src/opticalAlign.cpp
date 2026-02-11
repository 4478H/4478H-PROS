#include "devices.h"
#include "opticalAlign.h"
#include "pros/distance.hpp"
#include "movement.h"
#include "pros/imu.hpp"
#include <cmath>
using namespace pros;

// All distances in mm, angles in degrees
const double minGoalDist = 500.0;     // Min valid goal distance
const double maxGoalDist = 1000.0;    // Max valid goal distance
const double turnSpd = 30.0;          // Normal turn speed
const double backupSpd = 100.0;        // Speed for backing into goal
const double alignTolerance = 4.0;    // Max heading error allowed
const double maxscanAngle = 40.0;     // How far to scan each way
const double scanStartAngle = 260.0;  // Left scan limit
const double scanEndAngle = 360.0;    // Right scan limit
const double extraTurnAngle = 0.5;    // Small extra turn for centering

bool detectsGoal() {
    int objSize = backDistance.get_object_size();
    const int minMediumSize = 40;     // Filter out small objects/noise
    const int maxMediumSize = 120;    // Filter out large objects/walls
    return (objSize >= minMediumSize && objSize <= maxMediumSize);
}

bool scanForGoal(double& targetHeading) {
    // Sweep from left to right looking for goal
    double startHeading = scanStartAngle;
    double endHeading = scanEndAngle;
    bool goalFound = false;

    // Turn to start then begin async scan to end
    turnToHeadingSmart(startHeading, 500, {.minSpeed = 100});
    turnToHeadingSmart(endHeading, 1000, {.maxSpeed = 28});

    while (chassis.isInMotion()) {
        double dist = backDistance.get();
        int objSize = backDistance.get_object_size();
        double currHeading = imu.get_heading();
        bool isDetected = detectsGoal();

        pros::lcd::clear_line(0);
        pros::lcd::print(0, "Detected: %s", isDetected ? "YES" : "NO");
        pros::lcd::clear_line(1);
        pros::lcd::print(1, "Size: %d  Dist: %.0fmm", objSize, dist);
        pros::lcd::clear_line(2);
        pros::lcd::print(2, "Heading: %.1f -> %.1f", currHeading, endHeading);

        if (isDetected) {
            chassis.cancelAllMotions();
            targetHeading = currHeading;
            goalFound = true;
            left_motors.brake();
            right_motors.brake();
            pros::delay(150);
            return true;
        }

        pros::delay(20);
    }

    left_motors.brake();
    right_motors.brake();
    return goalFound;
}

void backIntoGoal(double targetHeading) {
    const double backupTimeout = 1000;    // Max time for backup attempt
    double startTime = pros::millis();
    int lostObjCount = 0;                 // Count frames where goal isn't seen
    const int lostObjThreshold = 5;       // Try recovery after this many lost frames
    
    while (pros::millis() - startTime < backupTimeout) {
        int objDetected = backDistance.get_object_size();
        
        if (objDetected == 0) {
            lostObjCount++;
            
            if (lostObjCount >= lostObjThreshold) {
                // Lost goal - stop and try recovery
                left_motors.brake();
                right_motors.brake();
                pros::delay(100);
                
                // Drive forward briefly to get better view
                left_motors.move(70);
                right_motors.move(70);
                pros::delay(300);
                left_motors.brake();
                right_motors.brake();
                pros::delay(100);
                
                if (scanForGoal(targetHeading)) {
                    startTime = pros::millis();
                    lostObjCount = 0;
                    continue;
                } else {
                    return;
                }
            }
        } else {
            lostObjCount = 0;
        }
        
        double currHeading = imu.get_heading();
        double headingErr = targetHeading - currHeading;
        
        // Normalize heading error to [-180, 180]
        while (headingErr > 180) headingErr -= 360;
        while (headingErr < -180) headingErr += 360;
        
        // Simple proportional correction (1.5 = P gain)
        double correction = headingErr * 1.5;
         
        // Limit correction power
        if (correction > 30) correction = 30;
        if (correction < -30) correction = -30;
        
        // Slow down to 30 after 1 second has elapsed
        double elapsedTime = pros::millis() - startTime;
        double currentSpeed = (elapsedTime >= 600) ? 30.0 : backupSpd;
        
        // Apply correction differentially
        double leftPwr = -currentSpeed + correction;
        double rightPwr = -currentSpeed - correction;
        
        left_motors.move(leftPwr);
        right_motors.move(rightPwr);
 
        
        pros::delay(20);
    }
    
    left_motors.brake();
    right_motors.brake();
}

void alignToLongGoal() {
    double targetHeading = 0;
    // Try to find goal, if found back into it
    if (scanForGoal(targetHeading)) {
        backIntoGoal(targetHeading);
    } else {
        // No goal found - stop safely
        left_motors.brake();
        right_motors.brake();
    }
}

bool scanForGoalOpposite(double& targetHeading) {
    // Sweep from left to right looking for goal (opposite side - centered around 180)
    double startHeading = 70.0;  // Left scan limit (180 - 35)
    double endHeading = 150;     // Right scan limit (180 + 35)
    bool goalFound = false;

    // Turn to start then begin async scan to end
    turnToHeadingSmart(startHeading, 500, {.minSpeed = 100});
    turnToHeadingSmart(endHeading, 1000, {.maxSpeed = 28});

    while (chassis.isInMotion()) {
        double dist = backDistance.get();
        int objSize = backDistance.get_object_size();
        double currHeading = imu.get_heading();
        bool isDetected = detectsGoal();

        pros::lcd::clear_line(0);
        pros::lcd::print(0, "Detected: %s", isDetected ? "YES" : "NO");
        pros::lcd::clear_line(1);
        pros::lcd::print(1, "Size: %d  Dist: %.0fmm", objSize, dist);
        pros::lcd::clear_line(2);
        pros::lcd::print(2, "Heading: %.1f -> %.1f", currHeading, endHeading);

        if (isDetected) {
            chassis.cancelAllMotions();
            targetHeading = currHeading;
            goalFound = true;
            left_motors.brake();
            right_motors.brake();
            pros::delay(150);
            return true;
        }

        pros::delay(20);
    }

    left_motors.brake();
    right_motors.brake();
    return goalFound;
}

void backIntoGoalOpposite(double targetHeading) {
    const double backupTimeout = 900;    // Max time for backup attempt
    double startTime = pros::millis();
    int lostObjCount = 0;                 // Count frames where goal isn't seen
    const int lostObjThreshold = 5;       // Try recovery after this many lost frames
    
    while (pros::millis() - startTime < backupTimeout) {
        int objDetected = backDistance.get_object_size();
        
        if (objDetected == 0) {
            lostObjCount++;
            
            if (lostObjCount >= lostObjThreshold) {
                // Lost goal - stop and try recovery
                left_motors.brake();
                right_motors.brake();
                pros::delay(100);
                
                // Drive forward briefly to get better view
                left_motors.move(70);
                right_motors.move(70);
                pros::delay(300);
                left_motors.brake();
                right_motors.brake();
                pros::delay(100);
                
                if (scanForGoalOpposite(targetHeading)) {
                    startTime = pros::millis();
                    lostObjCount = 0;
                    continue;
                } else {
                    return;
                }
            }
        } else {
            lostObjCount = 0;
        }
        
        double currHeading = imu.get_heading();
        double headingErr = targetHeading - currHeading;
        
        // Normalize heading error to [-180, 180]
        while (headingErr > 180) headingErr -= 360;
        while (headingErr < -180) headingErr += 360;
        
        // Simple proportional correction (1.5 = P gain)
        double correction = headingErr * 1.5;
         
        // Limit correction power
        if (correction > 30) correction = 30;
        if (correction < -30) correction = -30;
        
        // Slow down to 30 after 1 second has elapsed
        double elapsedTime = pros::millis() - startTime;
        double currentSpeed = (elapsedTime >= 650) ? 30.0 : backupSpd;
        
        // Apply correction differentially
        double leftPwr = -currentSpeed + correction;
        double rightPwr = -currentSpeed - correction;
        
        left_motors.move(leftPwr);
        right_motors.move(rightPwr);
 
        
        pros::delay(20);
    }
    
    left_motors.brake();
    right_motors.brake();
}

void alignToLongGoalOpposite() {
    double targetHeading = 180.0;  // Default target heading for opposite side
    // Try to find goal, if found back into it
    if (scanForGoalOpposite(targetHeading)) {
        backIntoGoalOpposite(targetHeading);
    } else {
        // No goal found - stop safely
        left_motors.brake();
        right_motors.brake();
    }
}