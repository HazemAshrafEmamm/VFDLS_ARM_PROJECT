#ifndef SERVICE_ESP32_CAM_H_
#define SERVICE_ESP32_CAM_H_

#include "../Utils/std_types.h"

/* Functions Prototypes */
void ESP32_CAM_Init(void);
void ESP32_CAM_TriggerCapture(void);
void ESP32_CAM_SendLiveData(uint8 temp, uint16 dist, uint8 w1_state, uint8 w2_state);

#endif /* SERVICE_ESP32_CAM_H_ */