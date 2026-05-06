#include "ultrasonic.h"
#include "../MCAL/gpio.h"
#include "../MCAL/timer0.h"
#include "../Utils/delay.h"
#include "../System_Config.h" 

#ifndef SYSCTL_RCGCGPIO_R
#define SYSCTL_RCGCGPIO_R       (*((volatile uint32 *)0x400FE608))
#endif

/* تعريف ريجستر الـ Digital Enable لـ Port C */
#ifndef GPIO_PORTC_DEN_R
#define GPIO_PORTC_DEN_R        (*((volatile uint32 *)0x4000651C))
#endif

void Ultrasonic_Init(void)
{
    volatile uint32 delay;

    /* 1. تفعيل الـ Clock لـ Port C */
    SYSCTL_RCGCGPIO_R |= 0x04; 
    delay = SYSCTL_RCGCGPIO_R; 

    /* 2. تأمين تشغيل الديجيتال لـ PC4 و PC5 بالإجبار (تحسباً لأي نقص في درايفر الـ GPIO) */
    GPIO_PORTC_DEN_R |= 0x30; /* 0x30 = 00110000 (Pins 4 & 5) */

    /* 3. تهيئة التايمر */
    Timer0_Init();
    Timer0_Start();

    /* 4. إعداد بِنّات الحساس */
    GPIO_SetPinDirection(PORTC_ID, PIN5_ID, PIN_OUTPUT); /* Trig = PC5 */
    GPIO_SetPinDirection(PORTC_ID, PIN4_ID, PIN_INPUT);  /* Echo = PC4 */
}

uint16 Ultrasonic_GetDistance(void)
{
    uint32 start_time = 0;
    uint32 end_time = 0;
    uint32 pulse_duration = 0;
    uint16 distance_cm = 0;
    uint32 timeout = 0; 

    /* 1. إرسال نبضة التشغيل */
    GPIO_WritePin(PORTC_ID, PIN5_ID, LOGIC_HIGH);
    Delay_us(10);
    GPIO_WritePin(PORTC_ID, PIN5_ID, LOGIC_LOW);

    /* 2. انتظار بداية الموجة (زودنا العداد جداً عشان لو البروسيسور سريع) */
    timeout = 900000;
    while(GPIO_ReadPin(PORTC_ID, PIN4_ID) == LOGIC_LOW && timeout > 0)
    {
        timeout--;
    }
    if(timeout == 0) return 0; 
    
    start_time = Timer0_GetMicros();

    /* 3. انتظار نهاية الموجة */
    timeout = 900000;
    while(GPIO_ReadPin(PORTC_ID, PIN4_ID) == LOGIC_HIGH && timeout > 0)
    {
        timeout--;
    }
    if(timeout == 0) return 0; 
    
    end_time = Timer0_GetMicros();

    /* 4. حساب المسافة */
    if(end_time >= start_time) {
        pulse_duration = end_time - start_time;
    } else {
        pulse_duration = (0xFFFFFFFF - start_time) + end_time; 
    }

    distance_cm = (uint16)(pulse_duration / 58);

    return distance_cm;
}