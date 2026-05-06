#include "timer0.h"

void Timer0_Init(void) 
{
    SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R0; // Enable Timer0 clock
    INSERT_DUMMY_DELAY(SYSCTL_RCGCTIMER_R);

    TIMER0_CTL_R = 0;            // Disable timer during setup
    TIMER0_CFG_R = 0x00000000;   // 32-bit timer mode
    TIMER0_TAMR_R = 0x00000002;  // Periodic mode, Count down
    TIMER0_TAILR_R = 0xFFFFFFFF; // Max reload value
    TIMER0_ICR_R = 0x00000001;   // Clear timeout flag
}

void Timer0_Start(void) 
{
    TIMER0_TAILR_R = 0xFFFFFFFF; // Reset reload
    TIMER0_CTL_R |= 0x00000001;  // Enable Timer0
}

void Timer0_Stop(void) 
{
    TIMER0_CTL_R &= ~0x00000001; // Disable Timer0
}

uint32 Timer0_GetMicros(void) 
{
    /* Calculate elapsed time in microseconds 
     * (Max value - Current value) / 16 (for 16MHz clock) */
    uint32 elapsed_ticks = 0xFFFFFFFF - TIMER0_TAV_R;
    return (elapsed_ticks / 16);
}