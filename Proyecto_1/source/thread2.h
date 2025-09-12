#include "board.h"
#include "UART_driver/UART_driver.h"
#include "ADC.h"
#include "thread0.h"

#define COMMAND_OPTIONS "Turn On -> Encender LED.\n\rTurn Off -> Apagar LED.\n\rToggle x -> x será el periodo en segundos.\n\rTemp -> Lectura del promedio de las ultimas 5 conversiones de unpotenciometro simulando temperatura.\n\rHelp -> Despliega los comando soportados.\n\r"

void thread2_init(void);

void Thd_10ms(void);
