#include "esp32_cam.h"
#include "../MCAL/uart.h"
#include "../System_Config.h" /* For ESP_ALERT_MSG_P001 definition */

/*
 * Description : 
 * Initializes the communication with the ESP32-CAM module.
 */
void ESP32_CAM_Init(void)
{
    /* Initialize UART1 which is dedicated for ESP32 communication */
    UART1_Init();
}

/*
 * Description : 
 * Sends the trigger command to the ESP32-CAM to take a photo 
 * and upload it to the cloud.
 */
void ESP32_CAM_TriggerCapture(void)
{
    /* Send the pre-configured alert message (e.g., "ALERT:P001\n") */
    UART1_SendString((const uint8 *)ESP_ALERT_MSG_P001);
}