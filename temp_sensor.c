#include "temp_sensor.h"

void TempSensor_Init(void) 
{
    // TODO: Enable ADC0 peripheral and GPIOE
    // TODO: Configure PE3 as AIN0 (Analog Input)
    // TODO: Configure ADC0 Sequence 3, Processor Trigger, and enable it
}

float32 TempSensor_Read(void) 
{
    // TODO: Trigger ADC conversion (ADCProcessorTrigger)
    // TODO: Wait for conversion to complete (ADCIntStatus)
    // TODO: Read the ADC value and clear the interrupt flag
    // TODO: Convert the digital value to Temperature in Celsius (LM35 formula)
    return 0.0; 
}