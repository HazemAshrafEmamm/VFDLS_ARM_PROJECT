#ifndef HAL_TEMP_SENSOR_H_
#define HAL_TEMP_SENSOR_H_

#include "../Utils/std_types.h"

void TempSensor_Init(void);
uint8 TempSensor_Read(void);

#endif /* HAL_TEMP_SENSOR_H_ */