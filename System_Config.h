#ifndef SYSTEM_CONFIG_H_
#define SYSTEM_CONFIG_H_

#include <stdint.h>
#include <stdbool.h>

// ==========================================
// ⚠️ BARE METAL ARCHITECTURE NOTE:
// No TivaWare (driverlib) allowed. 
// Access memory-mapped registers directly using this standard header:
// ==========================================
#include "tm4c123gh6pm.h"

// ==========================================
// Bit Mask Definitions for Register Manipulation
// ==========================================
#define BIT0                          (1U << 0)
#define BIT1                          (1U << 1)
#define BIT2                          (1U << 2)
#define BIT3                          (1U << 3)
#define BIT4                          (1U << 4)
#define BIT5                          (1U << 5)
#define BIT6                          (1U << 6)
#define BIT7                          (1U << 7)

// ==========================================
// GENERAL PINS CONFIGURATION RULES:
// - Set AFSEL for UART/I2C pins
// - Set DEN for all digital pins (UART, I2C, Ultrasonic, Motors, Buttons)
// - Clear DEN and set AMSEL for ADC pins (LM35)
// ==========================================

// ==========================================
// 0. System Clock & Peripheral Enables (Unified)
// ==========================================
#define SYSTEM_CLOCK_HZ               16000000U // Default 16 MHz 

// GPIO Ports Clock Enables (SYSCTL_RCGCGPIO_R)
#define GPIO_PORTA_CLK_EN             BIT0
#define GPIO_PORTB_CLK_EN             BIT1
#define GPIO_PORTC_CLK_EN             BIT2
#define GPIO_PORTE_CLK_EN             BIT4

// Peripherals Clock Enables
#define UART0_CLK_EN                  BIT0    // SYSCTL_RCGCUART_R
#define UART1_CLK_EN                  BIT1    // SYSCTL_RCGCUART_R
#define I2C0_CLK_EN                   BIT0    // SYSCTL_RCGCI2C_R
#define EEPROM_CLK_EN                 BIT0    // SYSCTL_RCGCEEPROM_R
#define ADC0_CLK_EN                   BIT0    // SYSCTL_RCGCADC_R

// ⚠️ CRITICAL TM4C123G REQUIREMENT:
// Insert a 3-cycle dummy read delay after enabling any peripheral clock.
// Usage in C file: SYSCTL_RCGCGPIO_R |= GPIO_PORTA_CLK_EN; INSERT_DUMMY_DELAY(SYSCTL_RCGCGPIO_R);
#define INSERT_DUMMY_DELAY(REG)       do { volatile uint32_t delay = (REG); (void)delay; } while(0)

// ==========================================
// 1. UART0 & PC Terminal 
// ==========================================
// Using Port A
#define TERMINAL_RX_PIN_MASK          BIT0    // PA0
#define TERMINAL_TX_PIN_MASK          BIT1    // PA1
// PCTL Values for UART0 (Clear mask: 0xFF)
#define UART0_PCTL_PA0_U0RX           0x00000001
#define UART0_PCTL_PA1_U0TX           0x00000010

// ==========================================
// 2. UART1 & ESP32-CAM (Bonus Feature)
// ==========================================
// Using Port B
#define CAM_RX_PIN_MASK               BIT0    // PB0
#define CAM_TX_PIN_MASK               BIT1    // PB1
// PCTL Values for UART1 (Clear mask: 0xFF)
#define UART1_PCTL_PB0_U1RX           0x00000001
#define UART1_PCTL_PB1_U1TX           0x00000010
// Protocol Alert Format
#define ESP_ALERT_MSG_P001            "ALERT:P001\n"

// ==========================================
// 3. LCD with I2C0 
// ==========================================
// Using Port B
#define LCD_I2C_SCL_PIN_MASK          BIT2    // PB2
#define LCD_I2C_SDA_PIN_MASK          BIT3    // PB3 (Must set Open Drain ODR)
// PCTL Values for I2C0 (Clear mask: 0xFF00)
#define I2C0_PCTL_PB2_I2C0SCL         0x00000300
#define I2C0_PCTL_PB3_I2C0SDA         0x00003000

// ==========================================
// 4. Engine Temperature - LM35 
// ==========================================
// Using Port E (AIN0 on PE3)
#define TEMP_SENSOR_PIN_MASK          BIT3    // PE3

// ==========================================
// 5. Ultrasonic Sensor - HCSR04 
// ==========================================
// Using Port C (PC4, PC5)
#define ULTRASONIC_ECHO_PIN_MASK      BIT4    // PC4 (Input)
#define ULTRASONIC_TRIG_PIN_MASK      BIT5    // PC5 (Output)
// Interrupt Configuration (NVIC)
#define NVIC_EN0_PORTC_IRQ            2       // IRQ Number for Port C
// NOTE: For Echo Pin Interrupt, configure GPIOIS, GPIOIBE, GPIOIEV for edge detection.

// ==========================================
// 6. Window DC Motors & Buttons 
// ==========================================
// Motors: Using Port B
#define MOTOR1_IN1_MASK               BIT4    // PB4 (Output)
#define MOTOR1_IN2_MASK               BIT5    // PB5 (Output)
#define MOTOR2_IN3_MASK               BIT6    // PB6 (Output)
#define MOTOR2_IN4_MASK               BIT7    // PB7 (Output)

// Buttons: Using Port E
#define BTN_WIN1_UP_MASK              BIT0    // PE0 (Input + Pull-up)
#define BTN_WIN1_DOWN_MASK            BIT1    // PE1 (Input + Pull-up)
#define BTN_WIN2_UP_MASK              BIT4    // PE4 (Input + Pull-up)
#define BTN_WIN2_DOWN_MASK            BIT5    // PE5 (Input + Pull-up)
// Interrupt Configuration (NVIC)
#define NVIC_EN0_PORTE_IRQ            4       // IRQ Number for Port E

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