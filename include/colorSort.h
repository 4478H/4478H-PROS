#ifndef __COLOR_SORT__
#define __COLOR_SORT__

#include "devices.h"

// Enum for ball colors
enum class BallColor {
    RED,
    BLUE,
    NONE  // No ball detected or unknown color
};

// Get the currently selected color to keep
// Returns true for red, false for blue
extern bool getSelectedColor();

// Set the selected color to keep
// @param isRed true for red, false for blue
extern void setSelectedColor(bool isRed);

// Toggle the selected color (called by center button before competition)
extern void toggleColorSelection();

// Display the current color selection on brain screen
extern void displayColorSelection();

// Run color sorting - reverses intake when wrong color detected
// This should be called continuously in opcontrol
extern void runColorSort();

// Check if a ball is detected by the optical sensor
// @return true if ball is detected, false otherwise
extern bool isBallDetected();

// Get the color of the detected ball
// @return BallColor enum value (RED, BLUE, or NONE)
extern BallColor getBallColor();

#endif

