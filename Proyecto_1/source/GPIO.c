/*
 * GPIO.c
 *
 *  Created on: 16 feb 2022
 *      Author: LUISPIZANO
 */
#include "GPIO.h"

void GPIO_config(void)
{
	gpio_pin_config_t sw_config = {
			kGPIO_DigitalInput,
			0,
	};

	/* Define the init structure for the output LED pin */
	gpio_pin_config_t led_config = {
			kGPIO_DigitalOutput,
			0,
	};

	const port_pin_config_t porta4_pin38_config = {/* Internal pull-up resistor is enabled */
			kPORT_PullUp,
			/* Fast slew rate is configured */
			kPORT_FastSlewRate,
			/* Passive filter is disabled */
			kPORT_PassiveFilterDisable,
			/* Open drain is disabled */
			kPORT_OpenDrainDisable,
			/* High drive strength is configured */
			kPORT_HighDriveStrength,
			/* Pin is configured as PTA4 */
			kPORT_MuxAsGpio,
			/* Pin Control Register fields [15:0] are not locked */
			kPORT_UnlockRegister};

	CLOCK_EnableClock(kCLOCK_PortA);
	CLOCK_EnableClock(kCLOCK_PortB);
	CLOCK_EnableClock(kCLOCK_PortE);
	CLOCK_EnableClock(kCLOCK_PortC);


	PORT_SetPinConfig(PORTA, bit_4, &porta4_pin38_config);
	GPIO_PinInit(GPIOA, bit_4, &sw_config);

	PORT_SetPinConfig(PORTC, bit_6, &porta4_pin38_config);
	GPIO_PinInit(GPIOC, bit_6, &sw_config);

	/* Init output LED GPIO. */
	//Red Led
	PORT_SetPinMux(PORTB, bit_22, kPORT_MuxAsGpio);
	GPIO_PinInit(GPIOB, bit_22, &led_config);
	//Blue Led
	PORT_SetPinMux(PORTB, bit_21, kPORT_MuxAsGpio);
	GPIO_PinInit(GPIOB, bit_21, &led_config);
	//Green Led
	PORT_SetPinMux(PORTE, bit_26, kPORT_MuxAsGpio);
	GPIO_PinInit(GPIOE, bit_26, &led_config);

	LED_Off(LED_RED);
	LED_Off(LED_GREEN);
	LED_Off(LED_BLUE);

}

bool Read_SW2(void) {
    return (GPIO_PinRead(GPIOC, 6U) == 0);  // true si está presionado
}

bool Read_SW3(void) {
    return (GPIO_PinRead(GPIOA, 4U) == 0);  // true si está presionado
}

void LED_On(board_led_t led) {
    switch (led) {
        case LED_RED:
            GPIO_PinWrite(GPIOB, 22U, 0);
            break;
        case LED_GREEN:
            GPIO_PinWrite(GPIOE, 26U, 0);
            break;
        case LED_BLUE:
            GPIO_PinWrite(GPIOB, 21U, 0);
            break;
    }
}

void LED_Off(board_led_t led) {
    switch (led) {
        case LED_RED:
            GPIO_PinWrite(GPIOB, 22U, 1);
            break;
        case LED_GREEN:
            GPIO_PinWrite(GPIOE, 26U, 1);
            break;
        case LED_BLUE:
            GPIO_PinWrite(GPIOB, 21U, 1);
            break;
    }
}

void LED_Toggle(board_led_t led){
    switch (led) {
        case LED_RED:
        {
            uint32_t cur = GPIO_PinRead(GPIOB, 22U);
            GPIO_PinWrite(GPIOB, 22U, cur ? 0U : 1U);
            break;
        }
        case LED_GREEN:
        {
            uint32_t cur = GPIO_PinRead(GPIOE, 26U);
            GPIO_PinWrite(GPIOE, 26U, cur ? 0U : 1U);
            break;
        }
        case LED_BLUE:
        {
            uint32_t cur = GPIO_PinRead(GPIOB, 21U);
            GPIO_PinWrite(GPIOB, 21U, cur ? 0U : 1U);
            break;
        }
    }
}
