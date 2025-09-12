#include "thread0.h"

static char command_str[11] = {0};
static uint8_t command = 0;
static uint8_t data;
static uint8_t new_data = 0;

void thread0_init(){
	UART_init();
};

void Thd_2ms(){
	if (new_data == 1){
		static uint8_t str_index = 0;

		if (data == '\r'){
			command_str[str_index] = '\0';
			data = '\n';
	        UART_WriteBlocking(DEMO_UART, &data, 1);
			str_index = 10;
			know_command();
		}
		else{
			command_str[str_index] = data;
		}

		str_index++;

		if (str_index >= 11){
			for(uint8_t i = 0; i <= 11; i++){
				command_str[i] = '\0';
			}
			str_index = 0;
		}

		new_data = 0;
	}
};

void set_command(uint8_t comm){
	if (comm >= 6){
		command = 0;
	}
	else {
		command = comm;
	}
};

uint8_t get_command(){
	return command;
};

void know_command(){
	if (strcmp(command_str, COMMAND1) == 0){
		command = 1;
	}
	else if (strcmp(command_str, COMMAND2) == 0){
		command = 2;
	}
	else if (strcmp(command_str, COMMAND3) == 0){
		command = 3;
	}
	else if (strcmp(command_str, COMMAND4) == 0){
		command = 4;
	}
	else if (strcmp(command_str, COMMAND5) == 0){
		command = 5;
	}
};

void DEMO_UART_IRQHandler(void)
{
    /* If new data arrived. */
    if ((kUART_RxDataRegFullFlag | kUART_RxOverrunFlag) & UART_GetStatusFlags(DEMO_UART))
    {
        data = UART_ReadByte(DEMO_UART);
        UART_WriteBlocking(DEMO_UART, &data, sizeof(data) / sizeof(data));

        new_data = 1;

    }
    SDK_ISR_EXIT_BARRIER;
}
