
#include "ADC.h"

/*!
 * @brief  Configuration structures for ADC.
 */
adc16_config_t adc16ConfigStruct;
adc16_channel_config_t adc16ChannelConfigStruct;

/*!
 * @brief  Configures and initialises ADC in single ended input mode
 */
void ADC_Start(void){
    ADC16_GetDefaultConfig(&adc16ConfigStruct);

#ifdef BOARD_ADC_USE_ALT_VREF
    adc16ConfigStruct.referenceVoltageSource = kADC16_ReferenceVoltageSourceValt;
#endif

    ADC16_Init(ADC16_BASE, &adc16ConfigStruct);
    ADC16_EnableHardwareTrigger(ADC16_BASE, false); /* Make sure the software trigger is used. */

#if defined(FSL_FEATURE_ADC16_HAS_CALIBRATION) && FSL_FEATURE_ADC16_HAS_CALIBRATION
    ADC16_DoAutoCalibration(ADC16_BASE);
#endif /* FSL_FEATURE_ADC16_HAS_CALIBRATION */

    adc16ChannelConfigStruct.channelNumber                        = ADC16_USER_CHANNEL;
    adc16ChannelConfigStruct.enableInterruptOnConversionCompleted = false;

#if defined(FSL_FEATURE_ADC16_HAS_DIFF_MODE) && FSL_FEATURE_ADC16_HAS_DIFF_MODE
    adc16ChannelConfigStruct.enableDifferentialConversion = false;
#endif /* FSL_FEATURE_ADC16_HAS_DIFF_MODE */
}

/*!
 * @brief  Gets the current value in ADC0 A0 pin
 *
 * @return                				    ADC value.
 * @retval ADC16_GetChannelConversionValue  Value from 0 to 4095.
 */
uint16_t ADC_GetValue(void){
    ADC16_SetChannelConfig(ADC16_BASE, ADC16_CHANNEL_GROUP, &adc16ChannelConfigStruct);

    /* Wait for conversion to be completed */
	while (0U == (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(ADC16_BASE, ADC16_CHANNEL_GROUP)));

	return ADC16_GetChannelConversionValue(ADC16_BASE, ADC16_CHANNEL_GROUP);
}
