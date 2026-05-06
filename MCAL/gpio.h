#ifndef MCAL_GPIO_H_
#define MCAL_GPIO_H_

#include "../Utils/std_types.h"
#include "../Utils/common_macros.h"
#include "../System_Config.h" // Includes tm4c123gh6pm.h and masks

/* GPIO Ports IDs */
typedef enum {
    PORTA_ID = 0, PORTB_ID, PORTC_ID, PORTD_ID, PORTE_ID, PORTF_ID
} GPIO_PortType;

/* GPIO Pins IDs */
typedef enum {
    PIN0_ID = 0, PIN1_ID, PIN2_ID, PIN3_ID, PIN4_ID, PIN5_ID, PIN6_ID, PIN7_ID
} GPIO_PinType;

/* GPIO Pin Direction */
typedef enum {
    PIN_INPUT = 0, PIN_OUTPUT
} GPIO_PinDirectionType;

/* Functions Prototypes */
void GPIO_SetPinDirection(GPIO_PortType port_num, GPIO_PinType pin_num, GPIO_PinDirectionType direction);
void GPIO_WritePin(GPIO_PortType port_num, GPIO_PinType pin_num, uint8 value);
uint8 GPIO_ReadPin(GPIO_PortType port_num, GPIO_PinType pin_num);

#endif /* MCAL_GPIO_H_ */