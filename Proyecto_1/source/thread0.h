#include <stdio.h>
#include <string.h>
#include "board.h"
#include "UART_driver/UART_driver.h"


#define DEMO_UART_IRQHandler UART0_RX_TX_IRQHandler
#define COMMAND1 "Turn On"
#define COMMAND2 "Turn Off"
#define COMMAND3 "Toggle "
#define COMMAND4 "Temp"
#define COMMAND5 "Help"

void DEMO_UART_IRQHandler(void);

void thread0_init(void);

void Thd_2ms(void);

void set_command(uint8_t com);

uint8_t get_command(void);

void know_command();
