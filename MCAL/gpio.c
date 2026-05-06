#include "gpio.h"

void GPIO_SetPinDirection(GPIO_PortType port_num, GPIO_PinType pin_num, GPIO_PinDirectionType direction) 
{
    switch(port_num) 
    {
        case PORTA_ID:
            if(direction == PIN_OUTPUT)      SET_BIT(GPIO_PORTA_DIR_R, pin_num);
            else                             CLEAR_BIT(GPIO_PORTA_DIR_R, pin_num);
            break;
        case PORTB_ID:
            if(direction == PIN_OUTPUT)      SET_BIT(GPIO_PORTB_DIR_R, pin_num);
            else                             CLEAR_BIT(GPIO_PORTB_DIR_R, pin_num);
            break;
        case PORTC_ID:
            if(direction == PIN_OUTPUT)      SET_BIT(GPIO_PORTC_DIR_R, pin_num);
            else                             CLEAR_BIT(GPIO_PORTC_DIR_R, pin_num);
            break;
        case PORTE_ID:
            if(direction == PIN_OUTPUT)      SET_BIT(GPIO_PORTE_DIR_R, pin_num);
            else                             CLEAR_BIT(GPIO_PORTE_DIR_R, pin_num);
            break;
        /* Port D and F can be added here if needed in the future */
    }
}

void GPIO_WritePin(GPIO_PortType port_num, GPIO_PinType pin_num, uint8 value) 
{
    switch(port_num) 
    {
        case PORTA_ID:
            if(value == LOGIC_HIGH)          SET_BIT(GPIO_PORTA_DATA_R, pin_num);
            else                             CLEAR_BIT(GPIO_PORTA_DATA_R, pin_num);
            break;
        case PORTB_ID:
            if(value == LOGIC_HIGH)          SET_BIT(GPIO_PORTB_DATA_R, pin_num);
            else                             CLEAR_BIT(GPIO_PORTB_DATA_R, pin_num);
            break;
        case PORTC_ID:
            if(value == LOGIC_HIGH)          SET_BIT(GPIO_PORTC_DATA_R, pin_num);
            else                             CLEAR_BIT(GPIO_PORTC_DATA_R, pin_num);
            break;
        case PORTE_ID:
            if(value == LOGIC_HIGH)          SET_BIT(GPIO_PORTE_DATA_R, pin_num);
            else                             CLEAR_BIT(GPIO_PORTE_DATA_R, pin_num);
            break;
    }
}

uint8 GPIO_ReadPin(GPIO_PortType port_num, GPIO_PinType pin_num) 
{
    uint8 bit_value = LOGIC_LOW;
    switch(port_num) 
    {
        case PORTA_ID:
            bit_value = BIT_IS_SET(GPIO_PORTA_DATA_R, pin_num) ? LOGIC_HIGH : LOGIC_LOW;
            break;
        case PORTB_ID:
            bit_value = BIT_IS_SET(GPIO_PORTB_DATA_R, pin_num) ? LOGIC_HIGH : LOGIC_LOW;
            break;
        case PORTC_ID:
            bit_value = BIT_IS_SET(GPIO_PORTC_DATA_R, pin_num) ? LOGIC_HIGH : LOGIC_LOW;
            break;
        case PORTE_ID:
            bit_value = BIT_IS_SET(GPIO_PORTE_DATA_R, pin_num) ? LOGIC_HIGH : LOGIC_LOW;
            break;
    }
    return bit_value;
}