#include "colorSort.h"
#include "devices.h"
#include "pros/optical.hpp"
#include "pros/misc.hpp"
#include <cmath>

using namespace pros;

// External declarations for auton selector color logic
extern bool red;
extern bool colorSortEnabled;

// Constants for color detection
const double RED_HUE_MIN = 0.0;
const double RED_HUE_MAX = 30.0;
const double BLUE_HUE_MIN = 200.0;
const double BLUE_HUE_MAX = 260.0;
const double MIN_SATURATION = 50.0;  // Minimum saturation to consider it a valid color
const double MIN_BRIGHTNESS = 50.0;  // Minimum brightness to detect a ball

// Intake reversal settings
const int REVERSE_SPEED = -127;  // Full reverse speed
const int FORWARD_SPEED = 127;   // Forward intake speed
const int REVERSE_TIME_MS = 300; // How long to reverse intake when wrong color detected

// State tracking for non-blocking reversal
static bool isReversing = false;
static uint32_t reverseStartTime = 0;
static bool lastBallDetected = false;

/**
 * @brief Get the currently selected color to keep
 * @return true for red, false for blue
 */
bool getSelectedColor() {
    return red;
}

/**
 * @brief Set the selected color to keep
 * @param isRed true for red, false for blue
 */
void setSelectedColor(bool isRed) {
    red = isRed;
}

/**
 * @brief Toggle the selected color (called by center button before competition)
 */
void toggleColorSelection() {
    red = !red;
    displayColorSelection();
}

/**
 * @brief Display the current color selection on brain screen
 */
void displayColorSelection() {
    pros::lcd::clear_line(0);
    pros::lcd::print(0, "Color Sort: %s", red ? "RED" : "BLUE");
    pros::lcd::clear_line(1);
    pros::lcd::print(1, "Press Center to Change");
}

/**
 * @brief Check if a ball is detected by the optical sensor
 * @return true if ball is detected, false otherwise
 */
bool isBallDetected() {
    // Check if there's enough brightness/proximity to indicate a ball
    double brightness = colorSens.get_brightness();
    double proximity = colorSens.get_proximity();
    
    // Ball is detected if brightness is above threshold or proximity is high
    return (brightness > MIN_BRIGHTNESS || proximity > 50);
}

/**
 * @brief Get the color of the detected ball
 * @return BallColor enum value (RED, BLUE, or NONE)
 */
BallColor getBallColor() {
    if (!isBallDetected()) {
        return BallColor::NONE;
    }
    
    // Get hue from optical sensor
    double hue = colorSens.get_hue();
    double saturation = colorSens.get_saturation();
    double brightness = colorSens.get_brightness();
    
    // Normalize hue to 0-360 range
    while (hue < 0) hue += 360;
    while (hue >= 360) hue -= 360;
    
    // Check if saturation and brightness are sufficient
    if (saturation < MIN_SATURATION || brightness < MIN_BRIGHTNESS) {
        return BallColor::NONE;
    }
    
    // Check for red (hue wraps around, so check both ranges)
    if ((hue >= RED_HUE_MIN && hue <= RED_HUE_MAX) || 
        (hue >= 330 && hue <= 360)) {
        return BallColor::RED;
    }
    
    // Check for blue
    if (hue >= BLUE_HUE_MIN && hue <= BLUE_HUE_MAX) {
        return BallColor::BLUE;
    }
    
    // Unknown color
    return BallColor::NONE;
}

/**
 * @brief Run color sorting - reverses intake when wrong color detected
 * This should be called continuously in opcontrol
 * Uses non-blocking approach so driver control isn't interrupted
 */
void runColorSort() {
    BallColor detectedColor = getBallColor();
    uint32_t currentTime = pros::millis();
    
    // Handle ongoing reversal
    if (isReversing) {
        // Check if reversal time has elapsed
        if (currentTime - reverseStartTime >= REVERSE_TIME_MS) {
            // Stop reversing
            intake.brake();
            isReversing = false;
        } else {
            // Continue reversing
            intake.move(REVERSE_SPEED);
            return; // Don't check for new balls while reversing
        }
    }
    
    // If no ball detected, don't do anything
    if (detectedColor == BallColor::NONE) {
        lastBallDetected = false;
        return;
    }
    
    // Only trigger on new ball detection (edge detection)
    if (lastBallDetected) {
        return; // Already processing this ball
    }
    
    lastBallDetected = true;
    
    // Check if detected color matches selected color
    bool isDetectedRed = (detectedColor == BallColor::RED);
    bool shouldKeep = (isDetectedRed == red);
    
    // If wrong color detected, start reversing intake
    if (!shouldKeep) {
        isReversing = true;
        reverseStartTime = currentTime;
        intake.move(REVERSE_SPEED);
        
        // Display feedback on brain screen
        pros::lcd::clear_line(3);
        pros::lcd::print(3, "Rejected: %s", isDetectedRed ? "RED" : "BLUE");
    } else {
        // Correct color - allow normal intake operation
        // Note: Intake speed should be controlled by driver, this just doesn't interfere
        pros::lcd::clear_line(3);
        pros::lcd::print(3, "Accepted: %s", isDetectedRed ? "RED" : "BLUE");
    }
}

