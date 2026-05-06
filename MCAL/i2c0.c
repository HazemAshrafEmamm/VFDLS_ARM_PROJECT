#include "i2c0.h"

void I2C0_Init(void)
{
    /* 1. Enable Clock for I2C0 and Port B */
    SYSCTL_RCGCI2C_R |= I2C0_CLK_EN;
    SYSCTL_RCGCGPIO_R |= GPIO_PORTB_CLK_EN;
    INSERT_DUMMY_DELAY(SYSCTL_RCGCGPIO_R);

    /* 2. Configure Pins (PB2 SCL, PB3 SDA) */
    GPIO_PORTB_AFSEL_R |= (LCD_I2C_SCL_PIN_MASK | LCD_I2C_SDA_PIN_MASK);
    GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & ~0xFF00) | (I2C0_PCTL_PB2_I2C0SCL | I2C0_PCTL_PB3_I2C0SDA);
    GPIO_PORTB_DEN_R |= (LCD_I2C_SCL_PIN_MASK | LCD_I2C_SDA_PIN_MASK);
    GPIO_PORTB_ODR_R |= LCD_I2C_SDA_PIN_MASK; /* SDA MUST be Open Drain */

    /* 3. Initialize I2C Master */
    I2C0_MCR_R = 0x00000010; /* Initialize I2C Master function */
    
    /* Set Clock speed to 100KHz (Standard Mode) */
    I2C0_MTPR_R = 0x07;
}

/* الدالة دي بتعمل START وتبعت الداتا وتعمل STOP في عملية واحدة سليمة */
void I2C0_WriteByteToSlave(uint8 slave_addr, uint8 data)
{
    /* 1. Set Slave Address and Write bit */
    I2C0_MSA_R = (slave_addr << 1) & 0xFE;
    
    /* 2. Put data in data register */
    I2C0_MDR_R = data;
    
    /* 3. Send START, RUN, and STOP in one go (0x07) */
    I2C0_MCS_R = 0x07;
    
    /* 4. Wait for it to complete */
    while(I2C0_MCS_R & 0x00000001);
}