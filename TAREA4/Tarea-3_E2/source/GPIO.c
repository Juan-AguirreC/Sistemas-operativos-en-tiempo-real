#include "GPIO.h"

void GPIO_config(void)
{
	gpio_pin_config_t input_pin = {
			kGPIO_DigitalInput,
			0,
	};

	/* Define the init structure for the output LED pin */
	gpio_pin_config_t output_pin = {
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


	PORT_SetPinConfig(PORTA, 4U, &porta4_pin38_config);
	GPIO_PinInit(GPIOA, 4U, &input_pin);

	/* Configurar interrupción por flanco de bajada en PTA4 */
	PORT_SetPinInterruptConfig(PORTA, 4U, kPORT_InterruptFallingEdge);

	/* Limpiar cualquier bandera previa */
	PORT_ClearPinsInterruptFlags(PORTA, (1U << 4U));

	/* Habilitar la interrupción del puerto A en el NVIC */
	EnableIRQ(PORTA_IRQn);

	PORT_SetPinConfig(PORTC, 6U, &porta4_pin38_config);
	GPIO_PinInit(GPIOC, 6U, &input_pin);

	/* Configurar interrupción por flanco de bajada en PTA4 */
	PORT_SetPinInterruptConfig(PORTC, 6U, kPORT_InterruptFallingEdge);

	/* Limpiar cualquier bandera previa */
	PORT_ClearPinsInterruptFlags(PORTC, (1U << 6U));

	/* Habilitar la interrupción del puerto A en el NVIC */
	EnableIRQ(PORTC_IRQn);

	/* Init output LED GPIO. */
	//Red Led
	PORT_SetPinMux(PORTB, 22U, kPORT_MuxAsGpio);
	GPIO_PinInit(GPIOB, 22U, &output_pin);
	//Blue Led
	PORT_SetPinMux(PORTB, 21U, kPORT_MuxAsGpio);
	GPIO_PinInit(GPIOB, 21U, &output_pin);
	//Green Led
	PORT_SetPinMux(PORTE, 26U, kPORT_MuxAsGpio);
	GPIO_PinInit(GPIOE, 26U, &output_pin);

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
