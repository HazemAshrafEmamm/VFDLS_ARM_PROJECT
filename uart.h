#ifndef UART_H_
#define UART_H_

#include "std_types.h"
#include "System_Config.h"

// Function Prototypes
void UART_Init(void);
void UART_SendByte(uint8 data);
void UART_SendString(const uint8 *str);
uint8 UART_ReceiveByte(void);

#endif /* UART_H_ */