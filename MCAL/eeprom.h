#ifndef MCAL_EEPROM_H_
#define MCAL_EEPROM_H_

#include "../Utils/std_types.h"
#include "../Utils/common_macros.h"
#include "../System_Config.h"

void EEPROM_Init(void);
void EEPROM_WriteWord(uint16 block, uint16 offset, uint32 data);
uint32 EEPROM_ReadWord(uint16 block, uint16 offset);

#endif /* MCAL_EEPROM_H_ */