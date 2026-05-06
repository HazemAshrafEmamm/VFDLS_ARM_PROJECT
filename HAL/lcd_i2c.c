#include "lcd_i2c.h"
#include "../MCAL/i2c0.h"   
#include "../Utils/delay.h"

/* ================================================================ */
/*                     LCD Low Level Functions                      */
/* ================================================================ */

static void LCD_WriteNibble(uint8 nibble, uint8 rs)
{
    /* 0x08 مسؤولة عن تشغيل إضاءة الشاشة (Backlight) */
    uint8 data = (nibble & 0xF0) | rs | 0x08; 
    
    /* إرسال الداتا مع تفعيل نبضة الشاشة (EN = 1) */
    I2C0_WriteByteToSlave(LCD_I2C_ADDRESS, data | 0x04);
    Delay_ms(1); /* استقرار النبضة */
    
    /* إرسال الداتا مع إغلاق نبضة الشاشة (EN = 0) */
    I2C0_WriteByteToSlave(LCD_I2C_ADDRESS, data & ~0x04);
    Delay_ms(1); /* استقرار الشاشة قبل الأمر اللي بعده */
}

void LCD_SendCommand(uint8 command)
{
    /* إرسال النص العالي من الأمر أولاً، ثم النص المنخفض */
    LCD_WriteNibble(command & 0xF0, 0);        
    LCD_WriteNibble((command << 4) & 0xF0, 0); 
    Delay_ms(2);
}

void LCD_DisplayCharacter(uint8 data)
{
    /* نفس فكرة الأمر، بس الـ RS = 1 عشان الشاشة تفهم إنه حرف هيتطبع */
    LCD_WriteNibble(data & 0xF0, 0x01);        
    LCD_WriteNibble((data << 4) & 0xF0, 0x01); 
    Delay_ms(1); 
}

/* ================================================================ */
/*                     LCD Initialization & Control                 */
/* ================================================================ */

void LCD_Init(void)
{
    /* 1. تهيئة الـ I2C */
    I2C0_Init(); 
    Delay_ms(50); 
    
    /* 2. خطوات التهيئة الإجبارية للـ 4-bit mode */
    LCD_WriteNibble(0x30, 0);
    Delay_ms(5);
    LCD_WriteNibble(0x30, 0);
    Delay_ms(1);
    LCD_WriteNibble(0x30, 0);
    Delay_ms(1);
    LCD_WriteNibble(0x20, 0); /* تفعيل الـ 4-bit mode */
    Delay_ms(1);

    /* 3. إعدادات الشاشة الأساسية */
    LCD_SendCommand(0x28); /* 4-bit mode, 2/4 lines, 5x8 font */
    LCD_SendCommand(0x08); /* Display off */
    LCD_SendCommand(0x01); /* Clear display */
    Delay_ms(5);           
    LCD_SendCommand(0x06); /* Entry mode set: Increment cursor */
    LCD_SendCommand(0x0C); /* Display on, Cursor off */
}

void LCD_ClearScreen(void)
{
    LCD_SendCommand(0x01); 
    Delay_ms(5);
}

void LCD_DisplayString(const uint8 *Str)
{
    uint8 i = 0;
    while(Str[i] != '\0')
    {
        LCD_DisplayCharacter(Str[i]);
        i++;
    }
}

/* ================================================================ */
/*                     LCD Cursor Movement (4x16 Fix)               */
/* ================================================================ */

void LCD_MoveCursor(uint8 row, uint8 col)
{
    uint8 lcd_memory_address;

    /* رجعنا العناوين الاستاندرد 0x10 و 0x50 عشان نلغي الترحيل الـ 4 مسافات */
    switch(row)
    {
        case 0: lcd_memory_address = col; break;
        case 1: lcd_memory_address = col + 0x40; break;
        case 2: lcd_memory_address = col + 0x10; break; 
        case 3: lcd_memory_address = col + 0x50; break; 
        default: lcd_memory_address = col; break;
    }
    
    LCD_SendCommand(lcd_memory_address | 0x80);
}

void LCD_DisplayInteger(uint32 num)
{
    uint8 buff[16];
    uint8 i = 0;
    if(num == 0) { LCD_DisplayCharacter('0'); return; }
    while(num > 0) { buff[i++] = (num % 10) + '0'; num /= 10; }
    while(i > 0) { LCD_DisplayCharacter(buff[--i]); }
}