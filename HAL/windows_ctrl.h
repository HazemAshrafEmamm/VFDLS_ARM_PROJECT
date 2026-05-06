#ifndef WINDOWS_CTRL_H_
#define WINDOWS_CTRL_H_

#include "std_types.h"
#include "System_Config.h"

// Function Prototypes
void Windows_Init(void);
void Windows_Update(void);
uint8 Windows_GetState(uint8 window_num); // Function to return state for LCD display

#endif /* WINDOWS_CTRL_H_ */