/*
 * Copyright 2016-2025 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file    Proyecto_2.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"
#include "pit.h"
#include "UART_driver.h"
/* TODO: insert other include files here. */

#define STACK_SIZE 512

/* TODO: insert other definitions and declarations here. */
typedef struct
{
	/*Pushed by Software*/
	uint32_t R4;
	uint32_t R5;
	uint32_t R6;
	uint32_t R8;
	uint32_t R9;
	uint32_t R10;
	uint32_t R11;
	/*Pushed by Hardware*/
	uint32_t R0;
	uint32_t R1;
	uint32_t R2;
	uint32_t R3;
	uint32_t R12;
	uint32_t LR;
	uint32_t PC;
	uint32_t PSR;
} stack_frame_struct_t;
/*
 * @brief   Application entry point.
 */

void Pit_Handler(void);

int main(void) {

	//el LR debe de tener una direccion valida para ser guardado por primera vez, PC lleva la funcion a ejecutar "TH0_Handler"

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

    PIT_init(1000);
    set_callback_PIT(Pit_Handler);

    UART_init();

    return 0 ;
}

void thread_a(void){
	while(1){
		PRINTF("Executing Thread A\r\n");
	}
}

void thread_b(void){
	while(1){
		PRINTF("Executing Thread B\r\n");
	}
}

void thread_c(void){
	while(1){
		PRINTF("Executing Thread C\r\n");
	}
}

static void *cmcm_push_context(void) {
	void *psp;
	__asm__("MRS %0, psp\n"
			"STMDB %0!, {r4-r11}\n"
			"MSR psp, %0\n"
			: "=r" (psp));
	return psp;
}

static void cmcm_pop_context(void *psp) {
	__asm__("LDMFD %0!, {r4-r11}\n"
			"MSR psp, %0\n"
			: : "r" (psp));
}

static void wr_main_stack_ptr(uint32_t val)
{
__asm__ ("MSR msp, %0\n\t" : : "r" (val) );
}
