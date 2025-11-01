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
#include "semphr.h"
#include "event_groups.h"

/* Freescale includes. */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include <stdio.h>
#include "GPIO.h"

#include "LCD_nokia.h"
#include "SPI.h"
#include "nokia_draw.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Task priorities. */
#define ThreadSeconds_PRIORITY	1
#define ThreadMinutes_PRIORITY	1
#define ThreadHours_PRIORITY	1
#define ThreadAlarm_PRIORITY	3
#define ThreadPrint_PRIORITY	2

#define AUTO_RELOAD_TIMER_ID    1

#define BIT_SECONDS_ALARM_EVENT		(1 << 0)
#define BIT_MINUTES_ALARM_EVENT		(1 << 1)
#define BIT_HOURS_ALARM_EVENT 		(1 << 2)
#define BIT_TURN_OFF_ALARM_EVENT 	(1 << 3)


#define SECONS_START	0
#define MINUTES_START	0
#define HOURS_START		0

#define SECONS_ALARM	45
#define MINUTES_ALARM	0
#define HOURS_ALARM		0


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

typedef enum{seconds_typde, minutes_type, hours_type} time_types_t;

typedef struct{
time_types_t time_type;
uint8_t value;
}time_msg_t;

static void ThreadSeconds(void *pvParameters);
static void ThreadMinutes(void *pvParameters);
static void ThreadHours(void *pvParameters);
static void ThreadAlarm(void *pvParameters);
static void ThreadPrint(void *pvParameters);

static void vSecondsTimerCallback(TimerHandle_t xTimer);


TaskHandle_t xThreadSecondsHandle = NULL;
TaskHandle_t xThreadMinutesHandle = NULL;
TaskHandle_t xThreadHoursHandle = NULL;

SemaphoreHandle_t xSecondsSemaphore = NULL;
SemaphoreHandle_t xMinutesSemaphore = NULL;
SemaphoreHandle_t xHoursSemaphore = NULL;
SemaphoreHandle_t xMutex = NULL;

QueueHandle_t time_queue;

EventGroupHandle_t myEventGroup = NULL;

TimerHandle_t AutoReloadSt;

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

    SPI_config();
    LCD_nokia_init();
    LCD_nokia_clear();
    LCD_nokia_write_string_xy_FB(0, 0, "00:00:00", 8);
    LCD_nokia_sent_FrameBuffer();

    GPIO_config();

    if (xTaskCreate(ThreadHours, "ThreadHours", configMINIMAL_STACK_SIZE + 100, NULL, ThreadSeconds_PRIORITY, &xThreadHoursHandle) != pdPASS){
    	PRINTF("Task creation failed!.\r\n");
    	while (1);
    }
    if (xTaskCreate(ThreadMinutes, "ThreadMinutes", configMINIMAL_STACK_SIZE + 100, NULL, ThreadSeconds_PRIORITY, &xThreadMinutesHandle) != pdPASS){
    	PRINTF("Task creation failed!.\r\n");
    	while (1);
    }
    if (xTaskCreate(ThreadSeconds, "ThreadSeconds", configMINIMAL_STACK_SIZE + 100, NULL, ThreadSeconds_PRIORITY, &xThreadSecondsHandle) != pdPASS){
    	PRINTF("Task creation failed!.\r\n");
    	while (1);
    }
    if (xTaskCreate(ThreadAlarm, "ThreadAlarm", configMINIMAL_STACK_SIZE + 100, NULL, ThreadAlarm_PRIORITY, NULL) != pdPASS){
    	PRINTF("Task creation failed!.\r\n");
    	while (1);
    }
    if (xTaskCreate(ThreadPrint, "ThreadPrint", configMINIMAL_STACK_SIZE + 100, NULL, ThreadPrint_PRIORITY, NULL) != pdPASS){
    	PRINTF("Task creation failed!.\r\n");
    	while (1);
    }

    xSecondsSemaphore = xSemaphoreCreateBinary();
    xMinutesSemaphore = xSemaphoreCreateBinary();
    xHoursSemaphore = xSemaphoreCreateBinary();
    xMutex = xSemaphoreCreateMutex();

    time_queue = xQueueCreate(1, sizeof(time_msg_t));

    myEventGroup = xEventGroupCreate();

    AutoReloadSt = xTimerCreate("AutoReload Timer", pdMS_TO_TICKS(1000), pdTRUE, (void*)AUTO_RELOAD_TIMER_ID, vSecondsTimerCallback);
    xTimerStart(AutoReloadSt, 0);

    vTaskStartScheduler();
    for (;;)
        ;
}

/*!
 * @brief Task responsible for printing of "Hello world." message.
 */
static void vSecondsTimerCallback(TimerHandle_t xTimer){
	xSemaphoreGive(xSecondsSemaphore);
}

static void ThreadSeconds(void *pvParameters)
{
	time_msg_t seconds = {seconds_typde, SECONS_START};

	if (seconds.value == SECONS_ALARM){
		xEventGroupSetBits(myEventGroup, BIT_SECONDS_ALARM_EVENT);
	}

	for (;;)
	{
		if (xSemaphoreTake(xSecondsSemaphore, portMAX_DELAY) == pdTRUE)
		{
			seconds.value++;
			if (seconds.value == 60){
				seconds.value = 0;
				xSemaphoreGive(xMinutesSemaphore);
			}
			if (seconds.value == SECONS_ALARM){
				xEventGroupSetBits(myEventGroup, BIT_SECONDS_ALARM_EVENT);
			}
			xQueueSend(time_queue, &seconds, portMAX_DELAY);
		}
	}
}

static void ThreadMinutes(void *pvParameters){

	time_msg_t minutes = {minutes_type, MINUTES_START};

	if (minutes.value == MINUTES_ALARM){
		xEventGroupSetBits(myEventGroup, BIT_MINUTES_ALARM_EVENT);
	}

	for (;;)
	{
		if (xSemaphoreTake(xMinutesSemaphore, portMAX_DELAY) == pdTRUE)
		{
			minutes.value++;
			if (minutes.value == 60){
				minutes.value = 0;
				xSemaphoreGive(xHoursSemaphore);
			}
			if (minutes.value == MINUTES_ALARM){
				xEventGroupSetBits(myEventGroup, BIT_MINUTES_ALARM_EVENT);
			}
			xQueueSend(time_queue, &minutes, portMAX_DELAY);
		}
	}
}

static void ThreadHours(void *pvParameters){

	time_msg_t hours = {hours_type, HOURS_START};

	if (hours.value == HOURS_ALARM){
		xEventGroupSetBits(myEventGroup, BIT_HOURS_ALARM_EVENT);
	}

	for (;;)
	{
		if (xSemaphoreTake(xHoursSemaphore, portMAX_DELAY) == pdTRUE)
		{
			hours.value++;
			if (hours.value == 24){
				hours.value = 0;
			}
			if (hours.value == HOURS_ALARM){
				xEventGroupSetBits(myEventGroup, BIT_HOURS_ALARM_EVENT);
			}
			xQueueSend(time_queue, &hours, portMAX_DELAY);
		}
	}
}

static void ThreadAlarm(void *pvParameters){
	EventBits_t bits;
	bool hours = false;
	bool minutes = false;
	bool seconds = false;
	while(1){

		bits = xEventGroupWaitBits(myEventGroup,  BIT_SECONDS_ALARM_EVENT| BIT_MINUTES_ALARM_EVENT| BIT_HOURS_ALARM_EVENT , pdTRUE, pdFALSE, portMAX_DELAY);

		if (bits & BIT_HOURS_ALARM_EVENT){
			hours = true;
		}
		if ((bits & BIT_MINUTES_ALARM_EVENT && hours)){
			minutes = true;
		}
		if ((bits & BIT_SECONDS_ALARM_EVENT) && minutes){
			seconds = true;
		}

		if (seconds && minutes && hours){
			hours = false;
			minutes = false;
			hours = false;
			if (xSemaphoreTake(xMutex, portMAX_DELAY) == pdTRUE) {
				LCD_nokia_write_string_xy_FB(0, 2, "ALARMA", 6);
				LCD_nokia_sent_FrameBuffer();
				xSemaphoreGive(xMutex);
			}
		}
	}
}
static void ThreadPrint(void *pvParameters){
	uint8_t seconds = SECONS_START;
	uint8_t minutes = MINUTES_START;
	uint8_t hours = HOURS_START;

	time_msg_t receptor;

	uint8_t buff[8];

	EventBits_t bits;

	while(1){
		if (xQueueReceive(time_queue, &receptor, portMAX_DELAY) == pdTRUE){
			switch (receptor.time_type) {
				case seconds_typde:
					seconds = receptor.value;
					break;
				case minutes_type:
					minutes = receptor.value;
					break;
				case hours_type:
					hours = receptor.value;
					break;
				default:
					break;
			}

			sprintf(buff, "%02d:%02d:%02d", hours, minutes, seconds);
			PRINTF("%s\r\n", buff);
		    LCD_nokia_sent_FrameBuffer();
		    if (xSemaphoreTake(xMutex, portMAX_DELAY) == pdTRUE) {
			    LCD_nokia_write_string_xy_FB(0, 0, buff, 8);
		    	LCD_nokia_sent_FrameBuffer();
		    	xSemaphoreGive(xMutex);
		    }
		}
	}
}

void PORTA_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    PORT_ClearPinsInterruptFlags(PORTA, (1U << 4U));

	LCD_nokia_write_string_xy_FB(0, 2, "      ", 6);

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
