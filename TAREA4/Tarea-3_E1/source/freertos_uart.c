
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

#include "fsl_uart_freertos.h"
#include "fsl_uart.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* UART instance and clock */
#define DEMO_UART            UART0
#define DEMO_UART_CLKSRC     UART0_CLK_SRC
#define DEMO_UART_CLK_FREQ   CLOCK_GetFreq(UART0_CLK_SRC)
#define DEMO_UART_RX_TX_IRQn UART0_RX_TX_IRQn
/* Task priorities. */
#define uart_task_PRIORITY (configMAX_PRIORITIES - 1)
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void uart_task(void *pvParameters);


/*******************************************************************************
 * Variables
 ******************************************************************************/
char *to_send               = "FreeRTOS UART driver example!\r\n";
char *send_ring_overrun     = "\r\nRing buffer overrun!\r\n";
char *send_hardware_overrun = "\r\nHardware buffer overrun!\r\n";
uint8_t background_buffer[32];
uint8_t recv_buffer[4];

uart_rtos_handle_t handle;
struct _uart_handle t_handle;

uart_rtos_config_t uart_config = {
    .baudrate    = 115200,
    .parity      = kUART_ParityDisabled,
    .stopbits    = kUART_OneStopBit,
    .buffer      = background_buffer,
    .buffer_size = sizeof(background_buffer),
};

SemaphoreHandle_t xUartSemaphore = NULL;
uint8_t data;



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
    NVIC_SetPriority(DEMO_UART_RX_TX_IRQn, 5);
    UART_init();
    xUartSemaphore = xSemaphoreCreateBinary();

    if (xTaskCreate(uart_task, "Uart_task", configMINIMAL_STACK_SIZE + 100, NULL, uart_task_PRIORITY, NULL) != pdPASS)
    {
        PRINTF("Task creation failed!.\r\n");
        while (1)
            ;
    }
    vTaskStartScheduler();
    for (;;)
        ;
}

/*!
 * @brief Task responsible for loopback.
 */
static void uart_task(void *pvParameters)
{
	for (;;)
	{
		if (xSemaphoreTake(xUartSemaphore, portMAX_DELAY) == pdTRUE)
		{
			UART_TX((uint8_t*)&data, 1);
		}
	}
}

void UART0_RX_TX_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if (UART_GetStatusFlags(UART0) & kUART_RxDataRegFullFlag)
    {
        data = UART_ReadByte(UART0);
        // Guarda el dato o mándalo por cola/semaforo
        xSemaphoreGiveFromISR(xUartSemaphore, &xHigherPriorityTaskWoken);
    }

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

