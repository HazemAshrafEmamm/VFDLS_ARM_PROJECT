#include "systick.h"

void SysTick_Init(void) 
{
    NVIC_ST_CTRL_R = 0;              // Disable SysTick during setup
    NVIC_ST_RELOAD_R = 0x00FFFFFF;   // Maximum reload value
    NVIC_ST_CURRENT_R = 0;           // Clear current value
    NVIC_ST_CTRL_R = 0x00000005;     // Enable SysTick with core clock
}

static void SysTick_Wait(uint32 delay_ticks) 
{
    NVIC_ST_RELOAD_R = delay_ticks - 1; 
    NVIC_ST_CURRENT_R = 0;              
    while((NVIC_ST_CTRL_R & 0x00010000) == 0); // Wait for count flag
}

void SysTick_Wait_ms(uint32 ms) 
{
    uint32 i;
    for(i = 0; i < ms; i++) {
        SysTick_Wait(16000); // 16000 ticks = 1ms (Assuming 16 MHz clock)
    }
}

void SysTick_Wait_us(uint32 us) 
{
    uint32 i;
    for(i = 0; i < us; i++) {
        SysTick_Wait(16); // 16 ticks = 1us (Assuming 16 MHz clock)
    }
}