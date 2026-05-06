#include "interrupts.h"

void NVIC_EnableIRQ(uint8 irq_number) 
{
    if (irq_number <= 31) 
    {
        NVIC_EN0_R = (1U << irq_number);
    } 
    else if (irq_number <= 63) 
    {
        NVIC_EN1_R = (1U << (irq_number - 32));
    }
    else if (irq_number <= 95) 
    {
        NVIC_EN2_R = (1U << (irq_number - 64));
    }
}

void NVIC_DisableIRQ(uint8 irq_number) 
{
    if (irq_number <= 31) 
    {
        NVIC_DIS0_R = (1U << irq_number);
    } 
    else if (irq_number <= 63) 
    {
        NVIC_DIS1_R = (1U << (irq_number - 32));
    }
    else if (irq_number <= 95) 
    {
        NVIC_DIS2_R = (1U << (irq_number - 64));
    }
}