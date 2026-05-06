#ifndef TEMP_SENSOR_H_
#define TEMP_SENSOR_H_

#include "std_types.h"
#include "System_Config.h"

// Function Prototypes
void TempSensor_Init(void);
float32 TempSensor_Read(void);

#endif /* TEMP_SENSOR_H_ */