#ifndef APP_FAULT_MANAGER_H_
#define APP_FAULT_MANAGER_H_

#include "../Utils/std_types.h"
#include "../System_Config.h"

/* Functions Prototypes */
void FaultManager_Init(void);
void FaultManager_LogFault(DTC_Code_t dtc);
void FaultManager_PrintLogs(void);
void FaultManager_ClearLogs(void);

#endif /* APP_FAULT_MANAGER_H_ */