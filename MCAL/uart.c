#include "uart.h"

void UART_Init(void) 
{
    // TODO: Initialize UART0 with SYSTEM_CLOCK_HZ, set Baud Rate, and configure PA0/PA1
}

void UART_SendByte(uint8 data) 
{
    // TODO: Wait until TX buffer is not full, then send the byte
}

void UART_SendString(const uint8 *str) 
{
    // TODO: Loop through the string array and send byte by byte until '\0'
}

uint8 UART_ReceiveByte(void) 
{
    // TODO: Wait until RX buffer is not empty, then read and return the byte
    return 0; 
}