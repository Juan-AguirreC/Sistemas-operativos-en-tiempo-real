#ifndef UART_DRIVER_H
#define UART_DRIVER_H

#include "fsl_uart.h"
#include "board.h"


#define DEMO_UART          UART0
#define DEMO_UART_CLKSRC   UART0_CLK_SRC
#define DEMO_UART_CLK_FREQ CLOCK_GetFreq(UART0_CLK_SRC)
#define DEMO_UART_IRQn     UART0_RX_TX_IRQn

void UART_init();

void UART_TX(uint8_t txbuff[], int len);
uint8_t UART_RX();


#endif /* UART_DRIVER_H */
