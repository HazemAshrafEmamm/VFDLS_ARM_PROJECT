#ifndef MCAL_SYSTICK_H_
#define MCAL_SYSTICK_H_

#include "../Utils/std_types.h"
#include "../System_Config.h"

void SysTick_Init(void);
void SysTick_Wait_ms(uint32 ms);
void SysTick_Wait_us(uint32 us);

#endif /* MCAL_SYSTICK_H_ */