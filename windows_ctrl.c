#include "windows_ctrl.h"

void Windows_Init(void) 
{
    // TODO: Enable GPIOB for Motors and GPIOE for Buttons
    // TODO: Configure PB4-PB7 as Output pins for L298N Motor Driver
    // TODO: Configure PE0, PE1, PE4, PE5 as Input pins for Buttons (Enable Internal Pull-up)
    // TODO: Ensure all motors are OFF initially
}

void Windows_Update(void) 
{
    // TODO: Read the state of each button
    // TODO: If Window 1 UP button is pressed -> Rotate Motor 1 Clockwise (Close)
    // TODO: If Window 1 DOWN button is pressed -> Rotate Motor 1 Counter-Clockwise (Open)
    // TODO: Apply the same logic for Window 2
    // TODO: Stop the motor if no button is pressed
}

uint8 Windows_GetState(uint8 window_num) 
{
    // TODO: Return the current state of the requested window (Open or Closed)
    // This will be used by the Leader to display the status on the LCD
    return 0;
}