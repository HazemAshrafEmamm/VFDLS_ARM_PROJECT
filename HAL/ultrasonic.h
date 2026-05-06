#ifndef HAL_ULTRASONIC_H_
#define HAL_ULTRASONIC_H_

#include "../Utils/std_types.h"

void Ultrasonic_Init(void);
uint16 Ultrasonic_GetDistance(void);

#endif /* HAL_ULTRASONIC_H_ */