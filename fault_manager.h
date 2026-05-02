#ifndef FAULT_MANAGER_H_
#define FAULT_MANAGER_H_

#include "std_types.h"
#include "System_Config.h"

// Function Prototypes
void FaultManager_Init(void);
void FaultManager_LogFault(DTC_Code_t dtc);
void FaultManager_RetrieveAll(void);

#endif /* FAULT_MANAGER_H_ */