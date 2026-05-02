#ifndef SYSTEM_CONFIG_H_
#define SYSTEM_CONFIG_H_

#include <stdint.h>
#include <stdbool.h>

// TivaWare Includes
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/adc.h"
#include "driverlib/eeprom.h"
#include "driverlib/interrupt.h"

// ==========================================
// ⚠️ SYSTEM NOTE FOR THE TEAM:
// Ensure SysCtlPeripheralEnable() is called 
// for each peripheral before use!
// ==========================================

// ==========================================
// 0. System Clock Configuration
// ==========================================
#define SYSTEM_CLOCK_HZ               16000000U // Default 16 MHz (Update if using PLL)

// ==========================================
// 1. UART0 & PC Terminal (Leader)
// ==========================================
#define TERMINAL_UART_BASE            UART0_BASE
#define TERMINAL_UART_PERIPH          SYSCTL_PERIPH_UART0
#define TERMINAL_GPIO_PERIPH          SYSCTL_PERIPH_GPIOA
#define TERMINAL_GPIO_PORT_BASE       GPIO_PORTA_BASE
#define TERMINAL_RX_PIN               GPIO_PIN_0
#define TERMINAL_TX_PIN               GPIO_PIN_1
#define TERMINAL_RX_CONFIG            GPIO_PA0_U0RX
#define TERMINAL_TX_CONFIG            GPIO_PA1_U0TX

// ==========================================
// 2. EEPROM (Leader)
// ==========================================
#define EEPROM_PERIPH                 SYSCTL_PERIPH_EEPROM0

// ==========================================
// 3. LCD with I2C0 (Hazem)
// NOTE: SDA must be configured as open-drain in GPIOPinTypeI2C()
// ==========================================
#define LCD_I2C_PERIPH                SYSCTL_PERIPH_I2C0
#define LCD_I2C_GPIO_PERIPH           SYSCTL_PERIPH_GPIOB
#define LCD_I2C_BASE                  I2C0_BASE
#define LCD_I2C_GPIO_PORT_BASE        GPIO_PORTB_BASE
#define LCD_I2C_SCL_PIN               GPIO_PIN_2
#define LCD_I2C_SDA_PIN               GPIO_PIN_3
#define LCD_I2C_SCL_CONFIG            GPIO_PB2_I2C0SCL
#define LCD_I2C_SDA_CONFIG            GPIO_PB3_I2C0SDA

// ==========================================
// 4. Engine Temperature - LM35 (Khaled)
// Using AIN0 on PE3
// ==========================================
#define TEMP_SENSOR_GPIO_PERIPH       SYSCTL_PERIPH_GPIOE
#define TEMP_SENSOR_GPIO_PORT_BASE    GPIO_PORTE_BASE
#define TEMP_SENSOR_PIN               GPIO_PIN_3
#define TEMP_SENSOR_ADC_PERIPH        SYSCTL_PERIPH_ADC0
#define TEMP_SENSOR_ADC_BASE          ADC0_BASE
#define TEMP_SENSOR_ADC_SEQ           3
#define TEMP_SENSOR_ADC_STEP          0
#define TEMP_SENSOR_ADC_TRIGGER       ADC_TRIGGER_PROCESSOR
#define TEMP_SENSOR_ADC_CHANNEL       ADC_CTL_CH0 

// ==========================================
// 5. Ultrasonic Sensor - HCSR04 (Salman)
// NOTE: PC0-PC3 are reserved for JTAG. Using PC4-PC5 is safe.
// ==========================================
#define ULTRASONIC_GPIO_PERIPH        SYSCTL_PERIPH_GPIOC
#define ULTRASONIC_GPIO_PORT_BASE     GPIO_PORTC_BASE
#define ULTRASONIC_ECHO_PIN           GPIO_PIN_4
#define ULTRASONIC_TRIG_PIN           GPIO_PIN_5
#define ULTRASONIC_INT                INT_GPIOC
#define ULTRASONIC_TRIG_DIR           GPIO_DIR_MODE_OUT
#define ULTRASONIC_ECHO_DIR           GPIO_DIR_MODE_IN
// NOTE FOR SALMAN: ISR must check if pin is HIGH (start timer) or LOW (stop timer)
#define ULTRASONIC_ECHO_EDGE          GPIO_BOTH_EDGES

// ==========================================
// 6. Window DC Motors & Buttons (Arwa)
// ==========================================
#define MOTORS_GPIO_PERIPH            SYSCTL_PERIPH_GPIOB
#define MOTORS_GPIO_PORT_BASE         GPIO_PORTB_BASE
#define MOTOR1_IN1                    GPIO_PIN_4
#define MOTOR1_IN2                    GPIO_PIN_5
#define MOTOR2_IN3                    GPIO_PIN_6
#define MOTOR2_IN4                    GPIO_PIN_7

#define BUTTONS_GPIO_PERIPH           SYSCTL_PERIPH_GPIOE
#define BUTTONS_GPIO_PORT_BASE        GPIO_PORTE_BASE
#define BTN_WIN1_UP                   GPIO_PIN_0
#define BTN_WIN1_DOWN                 GPIO_PIN_1
#define BTN_WIN2_UP                   GPIO_PIN_4
#define BTN_WIN2_DOWN                 GPIO_PIN_5
#define BUTTONS_INT                   INT_GPIOE

// ==========================================
// 7. System Thresholds & Constants
// ==========================================
#define TEMP_MAX_THRESHOLD            90 // Celsius
#define MIN_SAFE_DISTANCE_CM          10 // Distance < 10cm causes accident error
#define LCD_WARN_DISTANCE_CM          20 // Distance < 20cm shows on LCD

// ==========================================
// 8. System Enums (DTC, States & Buttons)
// ==========================================
typedef enum {
    DTC_NONE = 0,
    DTC_ACCIDENT_MIGHT_HAPPEN = 0x001,  // P001 
    DTC_ENGINE_HIGH_TEMP      = 0x002   // P002 
} DTC_Code_t;

typedef enum {
    SYSTEM_OFF = 0,
    SYSTEM_ON
} SystemState_t;

// Assuming Internal Pull-Up Resistors (0 = Pressed, 1 = Released)
typedef enum {
    BUTTON_PRESSED  = 0,
    BUTTON_RELEASED = 1
} ButtonState_t;

#endif /* SYSTEM_CONFIG_H_ */