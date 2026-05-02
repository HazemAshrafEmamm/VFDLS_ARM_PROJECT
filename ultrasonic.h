#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "std_types.h"
#include "System_Config.h"

// Function Prototypes
void Ultrasonic_Init(void);
uint32 Ultrasonic_GetDistance(void);

#endif /* ULTRASONIC_H_ */