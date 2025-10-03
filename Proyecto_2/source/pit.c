#include "pit.h"



void (*ptr_func)(void) = NULL;
void (*ptr_func_PIT1)(void) = NULL;

void set_callback_PIT(void *ptr){
	ptr_func = ptr;
}

void set_callback_PIT1(void *ptr){
	ptr_func_PIT1 = ptr;
}

void PIT_LED_HANDLER(void)
{
    /* Clear interrupt flag */
    PIT_ClearStatusFlags(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL, kPIT_TimerFlag);
    if (ptr_func != NULL)
    	ptr_func();
    __DSB();
}

void PIT1_IRQHandler(void)
{
    PIT_ClearStatusFlags(PIT, kPIT_Chnl_1, kPIT_TimerFlag);
    //WDT_Refresh();  // Refresca el Watchdog cada 50ms
}

void PIT_init(uint32_t frecuency){
	 /* Structure of initialize PIT */
	    pit_config_t pitConfig;
	    PIT_GetDefaultConfig(&pitConfig);

	    /* Init PIT module */
	    PIT_Init(DEMO_PIT_BASEADDR, &pitConfig);

	    uint32_t ticks = PIT_SOURCE_CLOCK / frecuency;

	    /* Set timer period for PIT0 */
	    PIT_SetTimerPeriod(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL, ticks - 1);
	    PIT_EnableInterrupts(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL, kPIT_TimerInterruptEnable);
	    EnableIRQ(PIT_IRQ_ID);
	    PIT_StartTimer(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL);

}

void PIT_init_PIT1(void){
    /* Calcular ticks para 50ms */
    uint32_t ticks = (PIT_SOURCE_CLOCK / 1000) * PIT1_INTERVAL_MS;

    /* Configurar PIT1 */
    PIT_SetTimerPeriod(DEMO_PIT_BASEADDR, DEMO_PIT1_CHANNEL, ticks - 1);
    PIT_EnableInterrupts(DEMO_PIT_BASEADDR, DEMO_PIT1_CHANNEL, kPIT_TimerInterruptEnable);
    EnableIRQ(PIT1_IRQ_ID);
    PIT_StartTimer(DEMO_PIT_BASEADDR, DEMO_PIT1_CHANNEL);
}
