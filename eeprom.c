#include "eeprom.h"
#include "uart.h" // هنحتاجه عشان لما نسترجع الأخطاء نطبعها على الـ Terminal

void EEPROM_Init(void) 
{
    // TODO: Enable EEPROM peripheral and perform EEPROMInit() recovery check
}

void EEPROM_LogFault(DTC_Code_t dtc_code) 
{
    // TODO: Check the next available address in EEPROM and write the dtc_code there
}

void EEPROM_RetrieveAllFaults(void) 
{
    // TODO: Read all stored faults from EEPROM blocks and send them via UART_SendString
}