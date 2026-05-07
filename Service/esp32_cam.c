#include "esp32_cam.h"
#include "../MCAL/uart.h"
#include "../System_Config.h"
#include "../HAL/windows_ctrl.h" 

void ESP32_CAM_Init(void)
{
    /* Initialize UART1 (Make sure it is configured for 9600 baud in uart.c) */
    UART1_Init();
}

void ESP32_CAM_TriggerCapture(void)
{
    UART1_SendString((const uint8 *)ESP_ALERT_MSG_P001);
}

/* دالة مساعدة لتحويل الرقم لنص وإرساله عبر UART1 */
static void UART1_SendInteger(uint32 num) 
{
    uint8 buffer[10];
    uint8 i = 0; /* 🚨 تم التعديل هنا لـ uint8 بدل int8 عشان الـ Error يختفي */
    
    if (num == 0) {
        UART1_SendByte('0');
        return;
    }
    while (num > 0) {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }
    while (i > 0) {
        UART1_SendByte(buffer[--i]);
    }
}

/* إرسال الداتا الحية لصفحة الويب */
void ESP32_CAM_SendLiveData(uint8 temp, uint16 dist, uint8 w1_state, uint8 w2_state)
{
    /* الحرارة */
    UART1_SendString("T:");
    UART1_SendInteger(temp);
    UART1_SendString("\n");

    /* المسافة */
    if(dist < LCD_WARN_DISTANCE_CM && dist > 0) {
        UART1_SendString("D:");
        UART1_SendInteger(dist);
        UART1_SendString("\n");
    } else {
        UART1_SendString("S:\n"); /* آمنة */
    }

    /* شباك 1 */
    UART1_SendString("W1:");
    if(w1_state == WINDOW_OPEN) UART1_SendString("OPEN\n");
    else UART1_SendString("CLOSED\n");

    /* شباك 2 */
    UART1_SendString("W2:");
    if(w2_state == WINDOW_OPEN) UART1_SendString("OPEN\n");
    else UART1_SendString("CLOSED\n");
}
/* سطر فاضي هنا عشان الـ Warning يختفي */