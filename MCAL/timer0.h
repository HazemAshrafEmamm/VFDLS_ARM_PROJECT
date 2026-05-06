#ifndef MCAL_TIMER0_H_
#define MCAL_TIMER0_H_

#include "../Utils/std_types.h"
#include "../System_Config.h"

void Timer0_Init(void);
void Timer0_Start(void);
void Timer0_Stop(void);
uint32 Timer0_GetMicros(void);

#endif /* MCAL_TIMER0_H_ */