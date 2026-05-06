#include "eeprom.h"
#include "../Utils/delay.h"

/* تعريف ريجستر الـ Reset للـ EEPROM تحسباً لو مش موجود في ملف tm4c123gh6pm.h */
#ifndef SYSCTL_SREEPROM_R
#define SYSCTL_SREEPROM_R (*((volatile uint32 *)0x400FE558))
#endif

void EEPROM_Init(void)
{
    /* 1. تفعيل كلوك الـ EEPROM */
    SYSCTL_RCGCEEPROM_R |= EEPROM_CLK_EN;
    
    /* استنى 6 سايكل على الأقل */
    Delay_ms(1); 

    /* ======================================================= */
    /* 🚨 السر هنا: عمل Software Reset إجباري لموديول الـ EEPROM 🚨 */
    /* ======================================================= */
    SYSCTL_SREEPROM_R = 0x01; /* تفعيل الريسيت */
    Delay_ms(1);
    SYSCTL_SREEPROM_R = 0x00; /* إلغاء الريسيت عشان يشتغل */
    Delay_ms(1);
    /* ======================================================= */

    /* 3. دلوقتي نقدر نستنى وإحنا مطمنين إن الـ EEPROM هترد علينا (WORKING bit is 0) */
    while(EEPROM_EEDONE_R & 0x00000001); 

    /* 4. التأكد من عدم وجود أخطاء */
    if((EEPROM_EESUPP_R & 0x00000008) || (EEPROM_EESUPP_R & 0x00000004))
    {
        /* Software error recovery */
    }
}

void EEPROM_WriteWord(uint16 block, uint16 offset, uint32 data)
{
    while(EEPROM_EEDONE_R & 0x00000001);
    EEPROM_EEBLOCK_R = block;
    EEPROM_EEOFFSET_R = offset;
    EEPROM_EERDWR_R = data;
    while(EEPROM_EEDONE_R & 0x00000001);
}

uint32 EEPROM_ReadWord(uint16 block, uint16 offset)
{
    while(EEPROM_EEDONE_R & 0x00000001);
    EEPROM_EEBLOCK_R = block;
    EEPROM_EEOFFSET_R = offset;
    return EEPROM_EERDWR_R;
}