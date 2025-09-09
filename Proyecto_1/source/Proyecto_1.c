/*
 * Copyright 2016-2025 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file    Proyecto_1.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"
#include "fsl_uart.h"
#include "RMS.h"

#define DEMO_UART            UART0
#define DEMO_UART_CLKSRC     UART0_CLK_SRC
#define DEMO_UART_CLK_FREQ   CLOCK_GetFreq(UART0_CLK_SRC)
#define DEMO_UART_IRQn       UART0_RX_TX_IRQn
#define DEMO_UART_IRQHandler UART0_RX_TX_IRQHandler
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */

void DEMO_UART_IRQHandler(void)
{
    uint8_t data;

    /* If new data arrived. */
    if ((kUART_RxDataRegFullFlag | kUART_RxOverrunFlag) & UART_GetStatusFlags(DEMO_UART))
    {
        data = UART_ReadByte(DEMO_UART);
        UART_WriteBlocking(DEMO_UART, &data, sizeof(data) / sizeof(data));

    }
    SDK_ISR_EXIT_BARRIER;
}

void Thd_2ms(void);
void Thd_5ms(void);
void Thd_10ms(void);
void Pit_Handler(void);


ThdObj ThreadTable[]= {
		{Thd_2ms, STANDBY,	2, 0},
		{Thd_5ms, STANDBY,	5, 0},
		{Thd_10ms, STANDBY, 10, 0}
};


int main(void) {


	uart_config_t config;

	BOARD_InitBootPins();
	BOARD_InitBootClocks();

	UART_init();

	uint8_t tableCounter = 0;

	while(1) {
		//for(tableCounter)
	}
	return 0 ;
}

void Thd_2ms(void){};
void Thd_5ms(void){};
void Thd_10ms(void){};

void Pit_Handler(void){
	static uint8_t tableCounter = 0;

	for(tableCounter = 0; tableCounter<3; tableCounter++){
		ThreadTable[tableCounter].SystemTime++;
		if(ThreadTable[tableCounter].SystemTime >= ThreadTable[tableCounter].ThreadRate){
			ThreadTable[tableCounter].ThreadState = READY;
			ThreadTable[tableCounter].SystemTime = 0;
		}
	}
}
