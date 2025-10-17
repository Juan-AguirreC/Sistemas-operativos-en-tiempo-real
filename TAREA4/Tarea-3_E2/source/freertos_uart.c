
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
#include "UART_driver/UART_driver.h"
#include "GPIO.h"

#include "fsl_uart_freertos.h"
#include "fsl_uart.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define Thread0_PRIORITY 3
#define Thread1_PRIORITY 2
#define Thread2_PRIORITY 1

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void Thread0(void *pvParameters);
static void Thread1(void *pvParameters);
static void Thread2(void *pvParameters);

SemaphoreHandle_t xEntranceSemaphore = NULL;
SemaphoreHandle_t xExitSemaphore = NULL;

uint8_t spaces = 10;



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

    GPIO_config();
    NVIC_SetPriority(PORTA_IRQn, 5);
    NVIC_SetPriority(PORTC_IRQn, 5);

    xEntranceSemaphore = xSemaphoreCreateBinary();
    xExitSemaphore = xSemaphoreCreateBinary();

    if (xTaskCreate(Thread0, "Thread0", configMINIMAL_STACK_SIZE + 100, NULL, Thread0_PRIORITY, NULL) == pdPASS)
    {
        if (xTaskCreate(Thread1, "Thread1", configMINIMAL_STACK_SIZE + 100, NULL, Thread1_PRIORITY, NULL) == pdPASS){
        	if (xTaskCreate(Thread2, "Thread2", configMINIMAL_STACK_SIZE + 100, NULL, Thread2_PRIORITY, NULL) != pdPASS){


        		PRINTF("Task creation failed!.\r\n");
        		while (1)
        			;
        	}
        }
    }
    vTaskStartScheduler();
    for (;;)
        ;
}

/*!
 * @brief Task responsible for loopback.
 */
static void Thread0(void *pvParameters)
{
	for (;;)
	{
		if (xSemaphoreTake(xEntranceSemaphore, portMAX_DELAY) == pdTRUE)
		{
			if (spaces > 0){
				spaces--;
			}
		}
	}
}

static void Thread1(void *pvParameters){
	for (;;)
	{
		if (xSemaphoreTake(xExitSemaphore, portMAX_DELAY) == pdTRUE)
		{
			if (spaces < 10){
				spaces++;
			}
		}
	}
}

static void Thread2(void *pvParameters){

	while(1){
		if(spaces >= 7){
			LED_Off(LED_RED);
			LED_Off(LED_BLUE);
			LED_On(LED_GREEN);

		} else if(spaces >= 1){
			LED_Off(LED_BLUE);
			LED_On(LED_GREEN);
			LED_On(LED_RED);

		} else{
			LED_Off(LED_BLUE);
			LED_Off(LED_GREEN);
			LED_On(LED_RED);

		}
	}

}

void PORTA_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    PORT_ClearPinsInterruptFlags(PORTA, (1U << 4U));

    /* Liberar el semáforo para despertar una tarea */
    xSemaphoreGiveFromISR(xEntranceSemaphore, &xHigherPriorityTaskWoken);

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void PORTC_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    PORT_ClearPinsInterruptFlags(PORTC, (1U << 6U));

    /* Liberar el semáforo para despertar una tarea */
    xSemaphoreGiveFromISR(xExitSemaphore, &xHigherPriorityTaskWoken);

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}


