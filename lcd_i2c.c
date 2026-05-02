#include "lcd_i2c.h"
#include "delay.h" // هنستخدمه بس في دالة الـ Init عشان الشاشة بتاخد وقت لغاية ما تشتغل

void LCD_Init(void) 
{
    // TODO: Initialize I2C0 peripheral on PB2/PB3
    // TODO: Send initialization sequence to the PCF8574 I2C module (4-bit mode)
    // NOTE: Use Delay_ms() only during this initialization phase
}

void LCD_SendCommand(uint8 command) 
{
    // TODO: Format the byte (Upper nibble + Lower nibble + RS=0 + EN pulse) and send via I2C
}

void LCD_SendData(uint8 data) 
{
    // TODO: Format the byte (Upper nibble + Lower nibble + RS=1 + EN pulse) and send via I2C
}

void LCD_DisplayString(const uint8 *str) 
{
    // TODO: Loop through the characters and call LCD_SendData for each
}

void LCD_SetCursor(uint8 row, uint8 col) 
{
    // TODO: Calculate the DDRAM address based on row and col, then send as command
}

void LCD_Clear(void) 
{
    // TODO: Send the clear display command (0x01)
}