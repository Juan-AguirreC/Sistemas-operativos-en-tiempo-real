#include "thread2.h"

static float temperature[5] = {0};
static uint8_t temperature_index = 0;


void thread2_init(){
	ADC_Start();
	UART_TX(COMMAND_OPTIONS, sizeof(COMMAND_OPTIONS) / sizeof(COMMAND_OPTIONS[0]));
};

void Thd_10ms(){
	static bool adc = 0;
	if (adc){
		adc = false;
		temperature[temperature_index] = ((float)ADC_GetValue() / 4095.0f) * 40;
		temperature_index++;
		if (temperature_index >= 5){
			temperature_index = 0;
		}
	} else
		adc = true;

	uint8_t job = get_command();

	if (job == 4){
		set_command(0);
	}
	else if (job == 5){
		UART_TX(COMMAND_OPTIONS, sizeof(COMMAND_OPTIONS) / sizeof(COMMAND_OPTIONS[0]));
		set_command(0);
	}
};

