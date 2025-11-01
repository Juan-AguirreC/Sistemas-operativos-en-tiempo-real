#include "GPIO.h"

void GPIO_config(void)
{
	gpio_pin_config_t input_pin = {
			kGPIO_DigitalInput,
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

	PORT_SetPinConfig(PORTA, 4U, &porta4_pin38_config);
	GPIO_PinInit(GPIOA, 4U, &input_pin);

	/* Configurar interrupción por flanco de bajada en PTA4 */
	PORT_SetPinInterruptConfig(PORTA, 4U, kPORT_InterruptFallingEdge);

	/* Limpiar cualquier bandera previa */
	PORT_ClearPinsInterruptFlags(PORTA, (1U << 4U));

	/* Habilitar la interrupción del puerto A en el NVIC */
	EnableIRQ(PORTA_IRQn);
}

bool Read_SW2(void) {
    return (GPIO_PinRead(GPIOC, 6U) == 0);  // true si está presionado
}
