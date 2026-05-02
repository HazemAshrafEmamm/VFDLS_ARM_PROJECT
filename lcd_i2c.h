#ifndef LCD_I2C_H_
#define LCD_I2C_H_

#include "std_types.h"
#include "System_Config.h"

// Function Prototypes
void LCD_Init(void);
void LCD_SendCommand(uint8 command);
void LCD_SendData(uint8 data);
void LCD_DisplayString(const uint8 *str);
void LCD_SetCursor(uint8 row, uint8 col);
void LCD_Clear(void);

#endif /* LCD_I2C_H_ */