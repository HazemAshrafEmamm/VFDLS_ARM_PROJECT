#include "app.h"
#include "../HAL/lcd_i2c.h"
#include "../HAL/ultrasonic.h"
#include "../HAL/temp_sensor.h"
#include "../HAL/windows_ctrl.h"
#include "../MCAL/uart.h"
#include "../MCAL/systick.h"
#include "../MCAL/interrupts.h"
#include "../MCAL/eeprom.h"
#include "../App/fault_manager.h"
#include "../Service/esp32_cam.h" /* 🚨 إضافة مكتبة الكاميرا */
#include "../Utils/delay.h"

static SystemState_t current_sys_state = SYSTEM_OFF;
static bool p001_logged = false;
static bool p002_logged = false;

void App_Init(void)
{
    SysTick_Init();
    LCD_Init();
    Enable_Exceptions(); 
    Ultrasonic_Init();
    TempSensor_Init();
    WindowsCtrl_Init();
    UART0_Init();
    ESP32_CAM_Init(); /* 🚨 تهيئة UART1 للكاميرا */
    FaultManager_Init(); 

    LCD_ClearScreen();
    LCD_MoveCursor(0, 0);
    LCD_DisplayString("System is OFF");
    LCD_MoveCursor(1, 0);
    LCD_DisplayString("Press 1 on PC/Web");

    UART0_SendString("\r\n========================================\r\n");
    UART0_SendString("      Vehicle System Interface\r\n");
    UART0_SendString("========================================\r\n");
    UART0_SendString(" Enter command (1=Start, 2=Logs, 3=Stop, 4=Clear): ");
}

void App_Run(void)
{
    uint16 distance = 0;
    uint8 temp = 0;
    uint8 command = 0;

    static uint8 last_valid_temp = 25; 
    static uint16 last_valid_distance = 100;
    uint32 temp_sum = 0;
    uint8 i = 0;

    while(1)
    {
        command = 0;

        /* 1. استقبال الأوامر من الكمبيوتر (UART0) أو الويب (UART1) */
        if(UART0_Available()) {
            command = UART0_ReceiveByte();
            UART0_SendByte(command); 
            UART0_SendString("\r\n");
        } 
        else if(UART1_Available()) { /* استقبال الأوامر من الـ Dashboard */
            command = UART1_ReceiveByte();
            UART0_SendString("\r\n >> Command received from Web Dashboard!\r\n");
        }

        if (command != 0)
        {
            if(command == '1') {
                current_sys_state = SYSTEM_ON;
                LCD_ClearScreen();
                UART0_SendString(" >> System STARTED.\r\n");
            }
            else if(command == '2') {
                FaultManager_PrintLogs();
            }
            else if(command == '3') {
                current_sys_state = SYSTEM_OFF;
                LCD_ClearScreen();
                LCD_MoveCursor(0, 0);
                LCD_DisplayString("System is OFF");
                UART0_SendString(" >> System CLOSED.\r\n");
            }
            else if(command == '4') {
                FaultManager_ClearLogs();
                UART0_SendString(" >> Logs Cleared.\r\n");
            }
            UART0_SendString(" Enter command: ");
        }

        /* 2. حلقة التشغيل الرئيسية */
        if(current_sys_state == SYSTEM_ON)
        {
            /* قراءة الحرارة (فلتر 16 قراءة) */
            temp_sum = 0;
            for(i = 0; i < 16; i++) { temp_sum += TempSensor_Read(); }
            temp = temp_sum / 16; 
            if(temp == 0 || temp > 120) temp = last_valid_temp; 
            else last_valid_temp = temp;

            /* قراءة المسافة */
            distance = Ultrasonic_GetDistance();
            if(distance == 0 || distance > 400) distance = last_valid_distance; 
            else last_valid_distance = distance; 

            /* تحديث الشبابيك */
            WindowsCtrl_Update();

            /* تحديث الـ LCD */
            LCD_MoveCursor(0, 0);
            LCD_DisplayString("Temp: "); LCD_DisplayInteger(temp); LCD_DisplayString(" C   ");

            LCD_MoveCursor(1, 0);
            LCD_DisplayString("Dist: "); 
            if(distance < LCD_WARN_DISTANCE_CM && distance > 0) {
                LCD_DisplayInteger(distance); LCD_DisplayString(" cm   ");
            } else {
                LCD_DisplayString("SAFE   "); 
            }

            LCD_MoveCursor(2, 0);
            LCD_DisplayString("W1: ");
            if(WindowsCtrl_GetState(1) == WINDOW_OPEN) LCD_DisplayString("OPEN  ");
            else LCD_DisplayString("CLOSED");

            LCD_MoveCursor(3, 0);
            LCD_DisplayString("W2: ");
            if(WindowsCtrl_GetState(2) == WINDOW_OPEN) LCD_DisplayString("OPEN  ");
            else LCD_DisplayString("CLOSED");

            /* 🚨 إرسال القراءات لايف إلى الويب داشبورد 🚨 */
            ESP32_CAM_SendLiveData(temp, distance, WindowsCtrl_GetState(1), WindowsCtrl_GetState(2));

            /* تسجيل الأخطاء */
            if(distance < MIN_SAFE_DISTANCE_CM && distance > 0) {
                if(p001_logged == false) {
                    FaultManager_LogFault(DTC_ACCIDENT_MIGHT_HAPPEN);
                    p001_logged = true;
                }
            } else if (distance > (MIN_SAFE_DISTANCE_CM + 5)) {
                p001_logged = false; 
            }

            if(temp > TEMP_MAX_THRESHOLD) {
                if(p002_logged == false) {
                    FaultManager_LogFault(DTC_ENGINE_HIGH_TEMP);
                    p002_logged = true;
                }
            } else if (temp < (TEMP_MAX_THRESHOLD - 5)) {
                p002_logged = false;
            }
        }

        Delay_ms(100); 
    }
}