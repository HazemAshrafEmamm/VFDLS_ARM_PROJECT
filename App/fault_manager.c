#include "fault_manager.h"
#include "eeprom.h"
#include "uart.h"

void FaultManager_Init(void) 
{
    // TODO: Initialize EEPROM module
    // EEPROM_Init();
}

void FaultManager_LogFault(DTC_Code_t dtc) 
{
    // TODO: Call EEPROM_LogFault(dtc) to store the error
    // TODO: Optional - Send a quick UART message saying "New Fault Logged!"
}

void FaultManager_RetrieveAll(void) 
{
    // TODO: Call EEPROM_RetrieveAllFaults() to fetch and print over UART
}