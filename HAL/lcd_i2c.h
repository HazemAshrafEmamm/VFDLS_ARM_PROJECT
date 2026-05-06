#ifndef HAL_LCD_I2C_H_
#define HAL_LCD_I2C_H_

#include "../Utils/std_types.h"

/* LCD I2C Slave Address (Commonly 0x27 or 0x3F) */
#define LCD_I2C_ADDRESS     0x27

/* LCD Commands */
#define LCD_CLEAR_COMMAND              0x01
#define LCD_GO_TO_HOME                 0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE  0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE   0x28
#define LCD_CURSOR_OFF                 0x0C
#define LCD_CURSOR_ON                  0x0E
#define LCD_SET_CURSOR_LOCATION        0x80

/* Functions Prototypes */
void LCD_Init(void);
void LCD_SendCommand(uint8 command);
void LCD_DisplayCharacter(uint8 data);
void LCD_DisplayString(const uint8 *Str);
void LCD_ClearScreen(void);
void LCD_MoveCursor(uint8 row, uint8 col);
void LCD_DisplayInteger(uint32 num);

#endif /* HAL_LCD_I2C_H_ */