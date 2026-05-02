#include "app.h"
#include "fault_manager.h"
#include "uart.h"
#include "lcd_i2c.h"
#include "temp_sensor.h"
#include "ultrasonic.h"
#include "windows_ctrl.h"

// Global variable to hold the current state of the system
static SystemState_t g_system_state = SYSTEM_OFF;

void App_Init(void) 
{
    // TODO: Call all initialization functions for the modules
    // UART_Init();
    // FaultManager_Init();
    // LCD_Init();
    // TempSensor_Init();
    // Ultrasonic_Init();
    // Windows_Init();
    
    // TODO: Display a welcome message on the LCD and PC Terminal
}

void App_Start(void) 
{
    // TODO: Change g_system_state to SYSTEM_ON
    // TODO: Update LCD to show "System Running"
}

void App_Stop(void) 
{
    // TODO: Change g_system_state to SYSTEM_OFF
    // TODO: Clear LCD and show "System Stopped"
    // TODO: Ensure motors are stopped
}

void App_Update(void) 
{
    // 1. Read UART Commands (Non-Blocking)
    // TODO: Check if a command is received (1, 2, or 3)
    // If '1' -> App_Start()
    // If '2' -> FaultManager_RetrieveAll()
    // If '3' -> App_Stop()

    // 2. Main System Logic (Only if SYSTEM_ON)
    if (g_system_state == SYSTEM_ON) 
    {
        // --- A. Read Sensors ---
        // float32 current_temp = TempSensor_Read();
        // uint32 current_dist = Ultrasonic_GetDistance();
        
        // --- B. Update Actuators & LCD ---
        // Windows_Update();
        // uint8 win1_state = Windows_GetState(1);
        // uint8 win2_state = Windows_GetState(2);
        // TODO: Update LCD with Temp, Distance (if < 20cm), and Window states
        
        // --- C. Fault Detection ---
        // TODO: If current_temp > TEMP_MAX_THRESHOLD -> FaultManager_LogFault(DTC_ENGINE_HIGH_TEMP)
        // TODO: If current_dist < MIN_SAFE_DISTANCE_CM -> FaultManager_LogFault(DTC_ACCIDENT_MIGHT_HAPPEN)
    }
}