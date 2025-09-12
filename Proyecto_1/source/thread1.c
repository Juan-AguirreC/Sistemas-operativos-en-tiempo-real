#include "thread1.h"

uint32_t current_time = 0;
uint32_t toggle_time = 0;

void thread1_init(){
	GPIO_config();
};

void Thd_5ms(){
	uint8_t job = get_command();
	if (job == 1){
		LED_On(LED_RED);
		set_command(0);
	}
	else if (job == 2){
		LED_Off(LED_RED);
		set_command(0);
	}
	else if (job == 3){
		toggle_time = get_time() * 200;
		set_command(0);
	}

	if (Read_SW2()){
		LED_On(LED_GREEN);
	}
	if(Read_SW3()){
		LED_Off(LED_GREEN);
	}

	if (toggle_time != 0){
		if(toggle_time <= current_time){
			LED_Toggle(LED_BLUE);
			current_time = 0;
		}
		current_time++;
	}
};

