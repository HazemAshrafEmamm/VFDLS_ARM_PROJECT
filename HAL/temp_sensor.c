#include "temp_sensor.h"
#include "../MCAL/adc0.h"

void TempSensor_Init(void)
{
    ADC0_Init(); /* Initialize MCAL ADC */
}

uint8 TempSensor_Read(void)
{
    uint16 adc_value = 0;
    uint8 temp_value = 0;

    /* Read the analog value from the MCAL driver */
    adc_value = ADC0_ReadChannel();

    /* Calculate the temperature 
     * Tiva C ADC is 12-bit (0-4095) with 3.3V reference.
     * LM35 gives 10mV per degree Celsius.
     * Temp = (ADC_Value * 3.3 * 100) / 4096 = (ADC_Value * 330) / 4096 
     */
    temp_value = (uint8)(((uint32)adc_value * 330) / 4096);

    return temp_value;
}