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
#include "RMS.h"
#include "pit.h"
#include "thread0.h"
#include "thread1.h"
#include "thread2.h"

uint8_t scheduler_event = 0;
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */

void Pit_Handler(void);
void Thread_init(void);
void Iddle(void);

ThdObj ThreadTable[]= {
		{Thd_2ms, STANDBY,	2, 0},
		{Thd_5ms, STANDBY,	5, 0},
		{Thd_10ms, STANDBY, 10, 0}
};


int main(void) {

	BOARD_InitBootPins();
	BOARD_InitBootClocks();

	Thread_init();

	uint8_t tableCounter = 0;

	while(1) {
		if (scheduler_event >= 1){
			for(tableCounter = 0; tableCounter < 3; tableCounter++){
				if(ThreadTable[tableCounter].ThreadState == READY){
					ThreadTable[tableCounter].ThreadState = EXECUTE;
					ThreadTable[tableCounter].ThreadHandler();
					ThreadTable[tableCounter].ThreadState = STANDBY;
				}
			}
			scheduler_event = 0;
		}
		else
			Iddle();
	}
	return 0 ;
}

void Pit_Handler(void){
	static uint8_t tableCounter = 0;
	scheduler_event = 1;

	for(tableCounter = 0; tableCounter<3; tableCounter++){
		ThreadTable[tableCounter].SystemTime++;
		if(ThreadTable[tableCounter].SystemTime >= ThreadTable[tableCounter].ThreadRate){
			ThreadTable[tableCounter].ThreadState = READY;
			ThreadTable[tableCounter].SystemTime = 0;
		}
	}
}

void Thread_init(void){
	PIT_init(1000);
	set_callback_PIT(Pit_Handler);

	thread0_init();
	thread1_init();
	thread2_init();
}

void Iddle(){
	__asm("NOP");
}

