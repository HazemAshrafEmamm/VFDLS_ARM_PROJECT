#ifndef MCAL_UART_H_
#define MCAL_UART_H_

#include "../Utils/std_types.h"
#include "../Utils/common_macros.h"
#include "../System_Config.h"

/* Functions Prototypes for UART0 (PC Terminal) */
void UART0_Init(void);
void UART0_SendByte(uint8 data);
void UART0_SendString(const uint8 *Str);
uint8 UART0_Available(void);
uint8 UART0_ReceiveByte(void);

/* Functions Prototypes for UART1 (ESP32-CAM) */
void UART1_Init(void);
void UART1_SendByte(uint8 data);
void UART1_SendString(const uint8 *Str);
uint8 UART1_Available(void);     /* 🚨 دالة جديدة */
uint8 UART1_ReceiveByte(void);   /* 🚨 دالة جديدة */

#endif /* MCAL_UART_H_ */
/* سطر فاضي هنا عشان الـ Warning يختفي */