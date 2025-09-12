#include "thread2.h"

static uint8_t comand_option[] = "Turn On -> Encender LED.\n\rTurn Off -> Apagar LED.\n\rToggle x -> x será el periodo en segundos.\n\rTemp -> Lectura del promedio de las ultimas 5 conversiones de unpotenciometro simulando temperatura.\n\rHelp -> Despliega los comando soportados.\n\r";


static float temperature[5] = {0};
static uint8_t temperature_index = 0;


void thread2_init(){
	ADC_Start();
	UART_TX(comand_option, sizeof(comand_option) / sizeof(comand_option[0]));
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
		float averaje_temperature = 0;
		for (uint8_t i = 0; i < 5 ; i++){
			averaje_temperature = averaje_temperature + temperature[i];
		}
		averaje_temperature = averaje_temperature / 5;
		uint8_t temperature_arr[6] = {0};
		ftoa(averaje_temperature, temperature_arr, 2);
		temperature_arr[4] = '\n';
		temperature_arr[5] = '\r';
		UART_TX(temperature_arr, sizeof(temperature_arr) / sizeof(temperature_arr[0]));
		set_command(0);
	}
	else if (job == 5){
		UART_TX(comand_option, sizeof(comand_option) / sizeof(comand_option[0]));
		set_command(0);
	}
};

void ftoa(float n, char* res, int afterpoint){
    // Extract integer part
    int ipart = (int)n;

    // Extract floating part
    float fpart = n - (float)ipart;

    // convert integer part to string
    int i = intToStr(ipart, res, 0);

    // check for display option after point
    if (afterpoint != 0) {
        res[i] = '.'; // add dot

        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter
        // is needed to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);

        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}

int intToStr(int x, char str[], int d){
    int i = 0;
    while (x) {
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }

    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';

    reverse(str, i);
    str[i] = '\0';
    return i;
}

void reverse(char* str, int len)
{
    int i = 0, j = len - 1, temp;
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}
