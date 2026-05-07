#include "fault_manager.h"
#include "../MCAL/eeprom.h"
#include "../MCAL/uart.h"
#include "../Service/esp32_cam.h"
#include "../Utils/delay.h"

/* Static variable to keep track of EEPROM address */
static uint16 current_eeprom_offset = 0;

void FaultManager_Init(void)
{
    EEPROM_Init();
}

void FaultManager_LogFault(DTC_Code_t dtc)
{
    if (dtc == DTC_NONE)
    {
        return;
    }

    /* 1. Log Fault Code to Internal EEPROM (Block 0) */
    EEPROM_WriteWord(0, current_eeprom_offset, (uint32)dtc);
    
    /* Increment offset for the next log (Simple Ring Buffer 0-15) */
    current_eeprom_offset++;
    if(current_eeprom_offset > 15)
    {
        current_eeprom_offset = 0;
    }

    /* 2. Notify PC Terminal via UART0 and take Service Actions */
    if (dtc == DTC_ACCIDENT_MIGHT_HAPPEN)
    {
        UART0_SendString("\r\n[SYSTEM ALERT]: P001 - Collision Warning!\r\n");
        
        /* Trigger ESP32-CAM to take a photo */
        ESP32_CAM_TriggerCapture();
    }
    else if (dtc == DTC_ENGINE_HIGH_TEMP)
    {
        UART0_SendString("\r\n[SYSTEM ALERT]: P002 - Engine High Temperature!\r\n");
    }
}

void FaultManager_PrintLogs(void)
{
    uint16 i;
    uint32 log_value;
    uint8 logs_found = 0;

    UART0_SendString("\r\n=== Retrieved Fault Logs ===\r\n");
    
    /* Read the first 16 blocks (our ring buffer size) */
    for(i = 0; i < 16; i++)
    {
        log_value = EEPROM_ReadWord(0, i);
        
        if(log_value == (uint32)DTC_ACCIDENT_MIGHT_HAPPEN)
        {
            UART0_SendString("- P001: Accident Might Happen (Dist < 10cm)\r\n");
            logs_found = 1;
        }
        else if(log_value == (uint32)DTC_ENGINE_HIGH_TEMP)
        {
            UART0_SendString("- P002: Engine High Temperature (Temp > 90C)\r\n");
            logs_found = 1;
        }
    }

    if(logs_found == 0)
    {
        UART0_SendString("- No faults logged yet.\r\n");
    }
    UART0_SendString("============================\r\n");
}

void FaultManager_ClearLogs(void)
{
    uint16 i;
    
    /* المرور على الـ 16 مكان ومسحهم (كتابة 0) */
    for(i = 0; i < 16; i++)
    {
        EEPROM_WriteWord(0, i, 0); 
    }
    
    /* تصفير العداد عشان نبدأ تسجيل من الأول */
    current_eeprom_offset = 0; 
}