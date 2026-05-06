#ifndef MCAL_I2C0_H_
#define MCAL_I2C0_H_

#include "../Utils/std_types.h"
#include "../System_Config.h"

/* Functions Prototypes */
void I2C0_Init(void);

/* دالة واحدة سحرية هتقوم بكل الشغل بأمان تام */
void I2C0_WriteByteToSlave(uint8 slave_addr, uint8 data);

#endif /* MCAL_I2C0_H_ */