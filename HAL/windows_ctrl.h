#ifndef HAL_WINDOWS_CTRL_H_
#define HAL_WINDOWS_CTRL_H_

#include "../Utils/std_types.h"

/* Enum to track the window state */
typedef enum {
    WINDOW_CLOSED = 0,
    WINDOW_OPEN
} WindowState_t;

void WindowsCtrl_Init(void);
void WindowsCtrl_Update(void);

/* Getter function for the LCD to read window states */
WindowState_t WindowsCtrl_GetState(uint8 window_num);

#endif /* HAL_WINDOWS_CTRL_H_ */