#ifndef __OPTICAL_ALIGN__
#define __OPTICAL_ALIGN__

// Align to long goal using back optical sensor
// Slowly turns to find goal, then backs into it while maintaining alignment
extern void alignToLongGoal();

// Align to long goal on opposite side of field (centered around 180 degrees)
// Same functionality as alignToLongGoal but for the opposite side
extern void alignToLongGoalOpposite();

#endif
