#include "UART_driver.h"

void UART_init(){
	uart_config_t config;

	/*
	 * config.baudRate_Bps = 115200U;
	 * config.parityMode = kUART_ParityDisabled;
	 * config.stopBitCount = kUART_OneStopBit;
	 * config.txFifoWatermark = 0;
	 * config.rxFifoWatermark = 1;
	 * config.enableTx = false;
	 * config.enableRx = false;
	 */
	UART_GetDefaultConfig(&config);
	config.baudRate_Bps = BOARD_DEBUG_UART_BAUDRATE;
	config.enableTx     = true;
	config.enableRx     = true;

	UART_Init(DEMO_UART, &config, DEMO_UART_CLK_FREQ);
	/* Enable RX interrupt. */
	UART_EnableInterrupts(DEMO_UART, kUART_RxDataRegFullInterruptEnable | kUART_RxOverrunInterruptEnable);
	EnableIRQ(DEMO_UART_IRQn);
	uint8_t clear_cmd[] = "\033[2J\033[H";
	UART_WriteBlocking(UART0, clear_cmd, sizeof(clear_cmd) - 1);
}

void UART_TX(uint8_t txbuff[], int len){
    UART_WriteBlocking(DEMO_UART, txbuff, len);
}
uint8_t UART_RX(){
	uint8_t ch;
    UART_ReadBlocking(DEMO_UART, &ch, 1);

    return ch;
}
