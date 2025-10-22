/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

/* Freescale includes. */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/


/* Task priorities. */
#define Th0_Tx_PRIORITY (configMAX_PRIORITIES - 2)
#define Th1_Tx_PRIORITY (configMAX_PRIORITIES - 2)
#define Th2_Tx_PRIORITY (configMAX_PRIORITIES - 2)
#define Th3_Rx_PRIORITY (configMAX_PRIORITIES - 1)


/*******************************************************************************
 * Prototypes
 ******************************************************************************/
typedef struct{
	uint8_t id;
	uint16_t data;
} Identification_struct;

static void Th0_Tx(void *pvParameters);
static void Th1_Tx(void *pvParameters);
static void Th2_Tx(void *pvParameters);
static void Th3_Rx(void *pvParameters);


QueueHandle_t myque = NULL;
TaskHandle_t TH0_Handle;
TaskHandle_t TH1_Handle;
TaskHandle_t TH2_Handle;


/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Application entry point.
 */
Identification_struct size;



int main(void)
{
    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();

    myque = xQueueCreate(3, sizeof(size));

    xTaskCreate(Th0_Tx, "Th0_Tx", configMINIMAL_STACK_SIZE + 100, NULL, Th0_Tx_PRIORITY, &TH0_Handle) != pdPASS;
    xTaskCreate(Th1_Tx, "Th1_Tx", configMINIMAL_STACK_SIZE + 100, NULL, Th1_Tx_PRIORITY, &TH1_Handle) != pdPASS;
    xTaskCreate(Th2_Tx, "Th2_Tx", configMINIMAL_STACK_SIZE + 100, NULL, Th2_Tx_PRIORITY, &TH2_Handle) != pdPASS;
    xTaskCreate(Th3_Rx, "Th3_Tx", configMINIMAL_STACK_SIZE + 100, NULL, Th3_Rx_PRIORITY, NULL) != pdPASS;

    vTaskStartScheduler();
    for (;;)
        ;
}

/*!
 * @brief Task responsible for printing of "Hello world." message.
 */
static void Th0_Tx(void *pvParameters)
{
	Identification_struct th0 = {0, 0};

	for (;;)
	{
		if (xQueueSend(myque, &th0, portMAX_DELAY) == pdPASS)
		{
			th0.data++;
		}
		vTaskResume(TH1_Handle);
		vTaskSuspend(TH0_Handle);
	}
}

static void Th1_Tx(void *pvParameters){
	Identification_struct th1 = {1, 0};
	bool use_Queue = true;

	for (;;)
	{
		if (use_Queue){
			if (xQueueSend(myque, &th1, portMAX_DELAY) == pdPASS)
			{
				th1.data = th1.data + 2;
				use_Queue = false;
			}
		} else {
			use_Queue = true;
		}
		vTaskResume(TH2_Handle);
		vTaskSuspend(TH1_Handle);
	}

}

static void Th2_Tx(void *pvParameters){
	Identification_struct th2 = {2, 65535 };

	for (;;)
	{
		if (xQueueSend(myque, &th2, portMAX_DELAY) == pdPASS)
		{
			th2.data--;
		}
		vTaskResume(TH0_Handle);
		vTaskSuspend(TH2_Handle);
	}

}

static void Th3_Rx(void *pvParameters){
	Identification_struct receptor;

	for (;;)
	{
		if (xQueueReceive(myque, &receptor, portMAX_DELAY) == pdTRUE)
		{
			// Se recibió un valor correctamente
			PRINTF("Datos recibidos del Th%d = %d\n\r", receptor.id, receptor.data);
		}
	}
}
