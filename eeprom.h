#ifndef EEPROM_H_
#define EEPROM_H_

#include "std_types.h"
#include "System_Config.h"

// Function Prototypes
void EEPROM_Init(void);
void EEPROM_LogFault(DTC_Code_t dtc_code);
void EEPROM_RetrieveAllFaults(void); 

#endif /* EEPROM_H_ */