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
#define hello_task_PRIORITY (configMAX_PRIORITIES - 1)
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

TaskHandle_t xThread1Handle = NULL;
TaskHandle_t xThread2Handle = NULL;
TaskHandle_t xThread3Handle = NULL;

static void vThread1(void *pvParameters);
static void vThread2(void *pvParameters);
static void vThread3(void *pvParameters);


/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Application entry point.
 */
int main(void)
{
    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();

    xTaskCreate(vThread1, "Thread1", 128, NULL, 1, NULL);
    xTaskCreate(vThread2, "Thread2", 128, NULL, 2, NULL);
	xTaskCreate(vThread3, "Thread3", 128, NULL, 3, NULL);

    vTaskStartScheduler();
    for (;;)
        ;
}

/*!
 * @brief Task responsible for printing of "Hello world." message.
 */
static void vThread1(void *pvParameters)
{
    for (;;)
    {
        PRINTF("Hello world in Thread 1.\r\n");
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
static void vThread2(void *pvParameters)
{
    for (;;)
    {
        PRINTF("Hello world in Thread 2.\r\n");
        vTaskDelay(pdMS_TO_TICKS(100));

    }
}
static void vThread3(void *pvParameters)
{
    for (;;)
    {
        PRINTF("Hello world in Thread 3.\r\n");
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
