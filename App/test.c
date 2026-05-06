#include "test.h"
#include "../HAL/lcd_i2c.h"
#include "../HAL/ultrasonic.h"
#include "../Utils/delay.h"
#include "../MCAL/systick.h"
#include "../MCAL/interrupts.h"
#include "../HAL/temp_sensor.h"
#include "../HAL/windows_ctrl.h"
#include "../MCAL/uart.h"
#include "../App/fault_manager.h" 
void Test_LCD(void)
{
    SysTick_Init();
    LCD_Init();
    LCD_ClearScreen();
    
    LCD_MoveCursor(0, 0);
    LCD_DisplayString("Line 1: LCD Test");
    LCD_MoveCursor(1, 0);
    LCD_DisplayString("Line 2: Working!");
    LCD_MoveCursor(2, 0);
    LCD_DisplayString("Line 3: 4x16 OK");
    LCD_MoveCursor(3, 0);
    LCD_DisplayString("Line 4: Perfect!");
    
    while(1) { }
}

void Test_Ultrasonic(void)
{
    uint16 distance = 0;

    SysTick_Init();
    LCD_Init();
    Enable_Exceptions();
    Ultrasonic_Init();
    
    LCD_ClearScreen();
    LCD_MoveCursor(0, 0);
    LCD_DisplayString("Ultrasonic Test");
    
    while(1)
    {
        distance = Ultrasonic_GetDistance();
        
        LCD_MoveCursor(1, 0);
        LCD_DisplayString("Dist: ");
        
        /* لو المسافة أكبر من 100 أو حصل تايم أوت */
        if (distance > 100 || distance == 0) 
        {
            /* المسافات هنا بتمسح أي رقم كبير كان مكتوب قبل كدة */
            LCD_DisplayString("0 cm            "); 
        }
        else 
        {
            LCD_DisplayInteger(distance);
            LCD_DisplayString(" cm            "); 
        }
        
        Delay_ms(200);
    }
    
}
void Test_Temperature(void)
{
    uint8 temp = 0;

    /* 1. تهيئة النظام */
    SysTick_Init();
    LCD_Init();
    TempSensor_Init(); /* تهيئة الـ ADC الداخلي */
    
    LCD_ClearScreen();
    LCD_MoveCursor(0, 0);
    LCD_DisplayString("Temp Sensor Test");
    
    while(1)
    {
        /* 2. قراءة درجة الحرارة */
        temp = TempSensor_Read();
        
        /* 3. العرض على السطر التالت (Row 2) */
        LCD_MoveCursor(2, 0);
        LCD_DisplayString("Temp: ");
        LCD_DisplayInteger(temp);
        LCD_DisplayString(" C   "); /* مسافات للتنظيف زي ما اتعلمنا */
        
        Delay_ms(500); /* تحديث كل نص ثانية كفاية جداً للحرارة */
    }
    
}

void Test_Windows(void)
{
    SysTick_Init();
    LCD_Init();
    WindowsCtrl_Init(); 
    
    LCD_ClearScreen();
    LCD_MoveCursor(0, 0);
    LCD_DisplayString("Windows Test");
    
    while(1)
    {
        /* 1. تحديث حالة المواتير والزراير */
        WindowsCtrl_Update(); 
        
        /* 2. عرض حالة شباك 1 */
        LCD_MoveCursor(2, 0);
        LCD_DisplayString("W1: ");
        if(WindowsCtrl_GetState(1) == WINDOW_OPEN)
            LCD_DisplayString("OPEN  ");
        else
            LCD_DisplayString("CLOSED");

        /* 3. عرض حالة شباك 2 */
        LCD_MoveCursor(3, 0);
        LCD_DisplayString("W2: ");
        if(WindowsCtrl_GetState(2) == WINDOW_OPEN)
            LCD_DisplayString("OPEN  ");
        else
            LCD_DisplayString("CLOSED");
        
        /* التأخير ده مهم جداً عشان حسابات الـ 3 ثواني للشبابيك تطلع مظبوطة (15 * 200ms = 3000ms) */
        Delay_ms(200); 
    }
}


void Test_UART0(void)
{
    uint8 command = 0;

    SysTick_Init();
    UART0_Init();
    FaultManager_Init(); 

    UART0_SendString("\r\n========================================\r\n");
    UART0_SendString("      Vehicle System Interface\r\n");
    UART0_SendString("      Developed by: Hazem Ashraf\r\n"); 
    UART0_SendString("========================================\r\n");
    UART0_SendString(" Commands Menu:\r\n");
    UART0_SendString(" [1] Start Operation\r\n");
    UART0_SendString(" [2] Retrieve Logged Errors (EEPROM)\r\n");
    UART0_SendString(" [3] Close System\r\n");
    UART0_SendString(" [4] Clear All Logs (Erase EEPROM)\r\n"); 
    UART0_SendString("----------------------------------------\r\n");
    UART0_SendString(" Enter command: ");

    while(1)
    {
        command = UART0_ReceiveByte(); 
        UART0_SendByte(command);       
        UART0_SendString("\r\n");

        if(command == '1')
        {
            UART0_SendString(" >> Action: System Started. Subsystems monitoring active...\r\n");
            FaultManager_LogFault(DTC_ACCIDENT_MIGHT_HAPPEN); 
            FaultManager_LogFault(DTC_ENGINE_HIGH_TEMP);
        }
        else if(command == '2')
        {
            FaultManager_PrintLogs(); 
        }
        else if(command == '3')
        {
            UART0_SendString(" >> Action: System Closed. Goodbye!\r\n");
        }
        else if(command == '4') 
        {
            FaultManager_ClearLogs();
            UART0_SendString(" >> Action: All faults have been cleared from EEPROM successfully!\r\n");
        }
        else
        {
            UART0_SendString(" >> Invalid Command! Please press 1, 2, 3, or 4.\r\n");
        }
        
        UART0_SendString("\r\n Enter command: ");
    }
}