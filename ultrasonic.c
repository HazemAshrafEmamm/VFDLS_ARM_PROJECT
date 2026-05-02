#include "ultrasonic.h"

void Ultrasonic_Init(void) 
{
    // TODO: Enable GPIOC peripheral for Ultrasonic pins
    // TODO: Configure PC5 as Output (Trigger) and PC4 as Input (Echo)
    // TODO: Configure Interrupt on PC4 (Both Edges) and register the ISR
    // TODO: Initialize a Timer to count the pulse width time
}

uint32 Ultrasonic_GetDistance(void) 
{
    // TODO: Send a 10us HIGH pulse on Trigger pin (PC5)
    // NOTE: The actual distance calculation will happen inside the ISR
    // Return the calculated distance variable here
    return 0; 
}

// NOTE FOR SALMAN: Don't forget to write the ISR (Interrupt Service Routine) function here!
// The ISR should start the timer on the Rising Edge, and stop it on the Falling Edge.