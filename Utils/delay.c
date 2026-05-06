#include "delay.h"
#include "../MCAL/systick.h" /* Dependency on MCAL SysTick Driver */

/*
 * Description : 
 * Delay execution for a specific number of milliseconds.
 */
void Delay_ms(uint32 milliseconds)
{
    /* Call the MCAL SysTick function to handle the hardware waiting */
    SysTick_Wait_ms(milliseconds);
}

/*
 * Description : 
 * Delay execution for a specific number of microseconds.
 */
void Delay_us(uint32 microseconds)
{
    /* Call the MCAL SysTick function to handle the hardware waiting */
    SysTick_Wait_us(microseconds);
}