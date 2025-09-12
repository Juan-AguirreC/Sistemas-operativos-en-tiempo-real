
#ifndef ADC_H_
#define ADC_H_

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_adc16.h"

#define ADC16_BASE          ADC0
#define ADC16_CHANNEL_GROUP 0U
#define ADC16_USER_CHANNEL  12U		// ADC_SE12 PTB2 (A0)

/*!
 * @brief  Configures and initialises ADC in single ended input mode
 */
void ADC_Start(void);

/*!
 * @brief  Gets the current value in ADC0 A0 pin
 *
 * @return                				    ADC value.
 * @retval ADC16_GetChannelConversionValue  Value from 0 to 4095.
 */
uint16_t ADC_GetValue(void);

#endif /* ADC_H_ */
