#include "windows_ctrl.h"
#include "../MCAL/gpio.h"
#include "../System_Config.h"

/* 15 ticks * 200ms = 3000ms (3 ثواني للفتح أو القفل الكامل) */
#define WINDOW_FULL_TRAVEL_TICKS  15 

static WindowState_t win1_state = WINDOW_CLOSED;
static WindowState_t win2_state = WINDOW_CLOSED;

static uint8 win1_open_ticks = 0;
static uint8 win1_close_ticks = WINDOW_FULL_TRAVEL_TICKS;
static uint8 win2_open_ticks = 0;
static uint8 win2_close_ticks = WINDOW_FULL_TRAVEL_TICKS;

/* تعريف ريجستر تشغيل الكلوك للبورتات */
#ifndef SYSCTL_RCGCGPIO_R
#define SYSCTL_RCGCGPIO_R       (*((volatile uint32 *)0x400FE608))
#endif

void WindowsCtrl_Init(void)
{
    volatile uint32 delay;

    /* 1. تفعيل الكلوك لـ Port B و Port E */
    SYSCTL_RCGCGPIO_R |= GPIO_PORTB_CLK_EN | GPIO_PORTE_CLK_EN;
    delay = SYSCTL_RCGCGPIO_R; 

    /* ========================================================== */
    /* 🚨 السر هنا: تفعيل الـ Digital Enable للبِنّات المستخدمة 🚨 */
    /* ========================================================== */
    /* Port B: PB4, PB5, PB6, PB7 (المواتير) -> 0xF0 بالباينري 11110000 */
    GPIO_PORTB_DEN_R |= 0xF0; 
    
    /* Port E: PE0, PE1, PE4, PE5 (الزراير) -> 0x33 بالباينري 00110011 */
    GPIO_PORTE_DEN_R |= 0x33; 
    /* ========================================================== */

    /* 2. تهيئة بِنّات المواتير (Output) */
    GPIO_SetPinDirection(PORTB_ID, PIN4_ID, PIN_OUTPUT); 
    GPIO_SetPinDirection(PORTB_ID, PIN5_ID, PIN_OUTPUT); 
    GPIO_SetPinDirection(PORTB_ID, PIN6_ID, PIN_OUTPUT); 
    GPIO_SetPinDirection(PORTB_ID, PIN7_ID, PIN_OUTPUT); 

    /* إيقاف المواتير كحالة ابتدائية */
    GPIO_WritePin(PORTB_ID, PIN4_ID, LOGIC_LOW);
    GPIO_WritePin(PORTB_ID, PIN5_ID, LOGIC_LOW);
    GPIO_WritePin(PORTB_ID, PIN6_ID, LOGIC_LOW);
    GPIO_WritePin(PORTB_ID, PIN7_ID, LOGIC_LOW);

    /* 3. تهيئة بِنّات الزراير (Input) */
    GPIO_SetPinDirection(PORTE_ID, PIN0_ID, PIN_INPUT);
    GPIO_SetPinDirection(PORTE_ID, PIN1_ID, PIN_INPUT);
    GPIO_SetPinDirection(PORTE_ID, PIN4_ID, PIN_INPUT);
    GPIO_SetPinDirection(PORTE_ID, PIN5_ID, PIN_INPUT);
}

void WindowsCtrl_Update(void)
{
    /* ================= Window 1 Control ================= */
    if(GPIO_ReadPin(PORTE_ID, PIN0_ID) == BUTTON_PRESSED) /* زرار الرفع (UP) */
    {
        win1_open_ticks = 0; /* تصفير عداد الفتح لأننا بنقفل دلوقتي */
        
        /* هل لسه الشباك مقفلش للاخر؟ */
        if(win1_close_ticks < WINDOW_FULL_TRAVEL_TICKS) 
        {
            GPIO_WritePin(PORTB_ID, PIN4_ID, LOGIC_HIGH); /* شغل الموتور للرفع */
            GPIO_WritePin(PORTB_ID, PIN5_ID, LOGIC_LOW);
            win1_close_ticks++;
        } 
        else 
        {
            /* الشباك وصل لآخر المسار (مقفول تماماً) */
            GPIO_WritePin(PORTB_ID, PIN4_ID, LOGIC_LOW);  /* افصل الموتور فوراً */
            GPIO_WritePin(PORTB_ID, PIN5_ID, LOGIC_LOW);
            win1_state = WINDOW_CLOSED; 
        }
    }
    else if(GPIO_ReadPin(PORTE_ID, PIN1_ID) == BUTTON_PRESSED) /* زرار التنزيل (DOWN) */
    {
        win1_close_ticks = 0; /* تصفير عداد القفل لأننا بنفتح دلوقتي */
        
        /* هل لسه الشباك مفتحش للاخر؟ */
        if(win1_open_ticks < WINDOW_FULL_TRAVEL_TICKS) 
        {
            GPIO_WritePin(PORTB_ID, PIN4_ID, LOGIC_LOW);
            GPIO_WritePin(PORTB_ID, PIN5_ID, LOGIC_HIGH); /* شغل الموتور للتنزيل */
            win1_open_ticks++;
        } 
        else 
        {
            /* الشباك وصل لآخر المسار (مفتوح تماماً) */
            GPIO_WritePin(PORTB_ID, PIN4_ID, LOGIC_LOW);  /* افصل الموتور فوراً */
            GPIO_WritePin(PORTB_ID, PIN5_ID, LOGIC_LOW);
            win1_state = WINDOW_OPEN; 
        }
    }
    else /* إيقاف الموتور لو مفيش أي زرار متداس */
    {
        GPIO_WritePin(PORTB_ID, PIN4_ID, LOGIC_LOW);
        GPIO_WritePin(PORTB_ID, PIN5_ID, LOGIC_LOW);
    }

    /* ================= Window 2 Control ================= */
    if(GPIO_ReadPin(PORTE_ID, PIN4_ID) == BUTTON_PRESSED) /* زرار الرفع (UP) */
    {
        win2_open_ticks = 0;
        
        if(win2_close_ticks < WINDOW_FULL_TRAVEL_TICKS) 
        {
            GPIO_WritePin(PORTB_ID, PIN6_ID, LOGIC_HIGH);
            GPIO_WritePin(PORTB_ID, PIN7_ID, LOGIC_LOW);
            win2_close_ticks++;
        } 
        else 
        {
            GPIO_WritePin(PORTB_ID, PIN6_ID, LOGIC_LOW);
            GPIO_WritePin(PORTB_ID, PIN7_ID, LOGIC_LOW);
            win2_state = WINDOW_CLOSED;
        }
    }
    else if(GPIO_ReadPin(PORTE_ID, PIN5_ID) == BUTTON_PRESSED) /* زرار التنزيل (DOWN) */
    {
        win2_close_ticks = 0;
        
        if(win2_open_ticks < WINDOW_FULL_TRAVEL_TICKS) 
        {
            GPIO_WritePin(PORTB_ID, PIN6_ID, LOGIC_LOW);
            GPIO_WritePin(PORTB_ID, PIN7_ID, LOGIC_HIGH);
            win2_open_ticks++;
        } 
        else 
        {
            GPIO_WritePin(PORTB_ID, PIN6_ID, LOGIC_LOW);
            GPIO_WritePin(PORTB_ID, PIN7_ID, LOGIC_LOW);
            win2_state = WINDOW_OPEN;
        }
    }
    else 
    {
        GPIO_WritePin(PORTB_ID, PIN6_ID, LOGIC_LOW);
        GPIO_WritePin(PORTB_ID, PIN7_ID, LOGIC_LOW);
    }
}

WindowState_t WindowsCtrl_GetState(uint8 window_num)
{
    if(window_num == 1) return win1_state;
    else return win2_state;
}