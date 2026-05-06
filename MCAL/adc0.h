#ifndef MCAL_ADC0_H_
#define MCAL_ADC0_H_

#include "../Utils/std_types.h"
#include "../Utils/common_macros.h"
#include "../System_Config.h"

void ADC0_Init(void);
uint16 ADC0_ReadChannel(void);

#endif /* MCAL_ADC0_H_ */