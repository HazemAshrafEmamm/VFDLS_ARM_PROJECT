#ifndef MCAL_INTERRUPTS_H_
#define MCAL_INTERRUPTS_H_

#include "../Utils/std_types.h"
#include "../System_Config.h"

/* Enable Interrupts globally */
#define Enable_Exceptions()    __asm(" cpsie i ")
/* Disable Interrupts globally */
#define Disable_Exceptions()   __asm(" cpsid i ")

void NVIC_EnableIRQ(uint8 irq_number);
void NVIC_DisableIRQ(uint8 irq_number);

#endif /* MCAL_INTERRUPTS_H_ */