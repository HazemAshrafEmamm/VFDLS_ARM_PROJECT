#include "adc0.h"

void ADC0_Init(void)
{
    /* 1. Enable Clock for ADC0 and Port E */
    SYSCTL_RCGCADC_R |= ADC0_CLK_EN;
    SYSCTL_RCGCGPIO_R |= GPIO_PORTE_CLK_EN;
    INSERT_DUMMY_DELAY(SYSCTL_RCGCGPIO_R);

    /* 2. Configure PE3 (AIN0) as Analog Input */
    GPIO_PORTE_AFSEL_R |= TEMP_SENSOR_PIN_MASK;   /* Enable alternate function */
    GPIO_PORTE_DEN_R &= ~TEMP_SENSOR_PIN_MASK;    /* Disable digital function */
    GPIO_PORTE_AMSEL_R |= TEMP_SENSOR_PIN_MASK;   /* Enable analog function */

    /* 3. Configure ADC0 Sample Sequencer 3 */
    ADC0_ACTSS_R &= ~0x0008;      /* Disable SS3 during configuration */
    ADC0_EMUX_R &= ~0xF000;       /* Software trigger conversion */
    ADC0_SSMUX3_R = 0;            /* Get input from channel 0 (AIN0) */
    ADC0_SSCTL3_R = 0x0006;       /* Take one sample at a time, set flag at 1st sample */
    ADC0_ACTSS_R |= 0x0008;       /* Enable SS3 */
}

uint16 ADC0_ReadChannel(void)
{
    uint16 result;
    ADC0_PSSI_R = 0x0008;                 /* Start conversion on SS3 */
    while((ADC0_RIS_R & 0x08) == 0);      /* Wait for conversion complete flag */
    result = ADC0_SSFIFO3_R & 0xFFF;      /* Read 12-bit result */
    ADC0_ISC_R = 0x0008;                  /* Clear completion flag */
    return result;
}