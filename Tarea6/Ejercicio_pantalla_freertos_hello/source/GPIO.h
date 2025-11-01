#ifndef GPIO_H_
#define GPIO_H_

#include "fsl_port.h"
#include "fsl_gpio.h"

typedef enum {
    LED_RED,
    LED_GREEN,
    LED_BLUE
} board_led_t;

void GPIO_config(void);

bool Read_SW2(void);
bool Read_SW3(void);

void LED_On(board_led_t led);
void LED_Off(board_led_t led);
void LED_Toggle(board_led_t led);


#endif /* GPIO_H_ */
