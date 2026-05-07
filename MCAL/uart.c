#include "uart.h"

void UART0_Init(void)
{
    /* 1. Enable Clock for UART0 and Port A */
    SYSCTL_RCGCUART_R |= UART0_CLK_EN;
    SYSCTL_RCGCGPIO_R |= GPIO_PORTA_CLK_EN;
    INSERT_DUMMY_DELAY(SYSCTL_RCGCGPIO_R);

    /* 2. Configure UART0 Pins (PA0 RX, PA1 TX) */
    GPIO_PORTA_AFSEL_R |= (TERMINAL_RX_PIN_MASK | TERMINAL_TX_PIN_MASK);
    GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & ~0xFF) | (UART0_PCTL_PA0_U0RX | UART0_PCTL_PA1_U0TX);
    GPIO_PORTA_DEN_R |= (TERMINAL_RX_PIN_MASK | TERMINAL_TX_PIN_MASK);

    /* 3. Configure UART0 (9600 Baud Rate, 8-bit, No Parity, 1 Stop bit) */
    UART0_CTL_R = 0;                     /* Disable UART before config */
    UART0_IBRD_R = 104;                  /* IBRD = 16MHz / (16 * 9600) = 104.16667 */
    UART0_FBRD_R = 11;                   /* FBRD = 0.16667 * 64 + 0.5 = 11 */
    UART0_LCRH_R = 0x00000070;           /* 8-bit length, FIFO enable */
    UART0_CTL_R = 0x00000301;            /* Enable UART, TX, RX */
}

void UART0_SendByte(uint8 data)
{
    while((UART0_FR_R & 0x00000020) != 0); /* Wait until TX FIFO is not full */
    UART0_DR_R = data;
}

void UART0_SendString(const uint8 *Str)
{
    uint8 i = 0;
    while(Str[i] != '\0')
    {
        UART0_SendByte(Str[i]);
        i++;
    }
}

/* Checks if there is data available to read from Terminal */
uint8 UART0_Available(void)
{
    return ((UART0_FR_R & 0x00000010) == 0); /* RXFE is 0 means not empty */
}

/* Reads the received byte from Terminal */
uint8 UART0_ReceiveByte(void)
{
    while((UART0_FR_R & 0x00000010) != 0); /* Wait until RX FIFO is not empty */
    return UART0_DR_R;
}


void UART1_Init(void)
{
    /* 1. Enable Clock for UART1 and Port B */
    SYSCTL_RCGCUART_R |= UART1_CLK_EN;
    SYSCTL_RCGCGPIO_R |= GPIO_PORTB_CLK_EN;
    INSERT_DUMMY_DELAY(SYSCTL_RCGCGPIO_R);

    /* 2. Configure UART1 Pins (PB0 RX, PB1 TX) */
    GPIO_PORTB_AFSEL_R |= (CAM_RX_PIN_MASK | CAM_TX_PIN_MASK);
    GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & ~0xFF) | (UART1_PCTL_PB0_U1RX | UART1_PCTL_PB1_U1TX);
    GPIO_PORTB_DEN_R |= (CAM_RX_PIN_MASK | CAM_TX_PIN_MASK);

    /* 3. Configure UART1 (9600 Baud Rate, 8-bit) */
    UART1_CTL_R = 0;
    UART1_IBRD_R = 104;
    UART1_FBRD_R = 11;
    UART1_LCRH_R = 0x00000070;
    UART1_CTL_R = 0x00000301;
}

void UART1_SendByte(uint8 data)
{
    while((UART1_FR_R & 0x00000020) != 0); 
    UART1_DR_R = data;
}

void UART1_SendString(const uint8 *Str)
{
    uint8 i = 0;
    while(Str[i] != '\0')
    {
        UART1_SendByte(Str[i]);
        i++;
    }
}

/* 🚨 إضافة دوال الاستقبال لـ UART1 عشان الويب يقدر يتحكم في السيستم 🚨 */
uint8 UART1_Available(void)
{
    return ((UART1_FR_R & 0x00000010) == 0); 
}

uint8 UART1_ReceiveByte(void)
{
    while((UART1_FR_R & 0x00000010) != 0); 
    return UART1_DR_R;
}
/* سطر فاضي هنا عشان الـ Warning يختفي */