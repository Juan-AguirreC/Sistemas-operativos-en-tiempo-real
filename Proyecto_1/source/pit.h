#ifndef DRIVERS_PIT_PIT_H_
#define DRIVERS_PIT_PIT_H_

#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_pit.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_PIT_BASEADDR PIT
#define DEMO_PIT_CHANNEL  kPIT_Chnl_0
#define PIT_LED_HANDLER   PIT0_IRQHandler
#define PIT_IRQ_ID        PIT0_IRQn

// PIT1 Definitions
#define DEMO_PIT1_CHANNEL  kPIT_Chnl_1
#define PIT1_HANDLER       PIT1_IRQHandler
#define PIT1_IRQ_ID        PIT1_IRQn
#define PIT1_INTERVAL_MS   50  // PIT1 a 50ms

/* Get source clock for PIT driver */
#define PIT_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)

void PIT_init(uint32_t frecuency);
void PIT_init_PIT1(void);
void set_callback_PIT(void *ptr);
void set_callback_PIT1(void *ptr);

#endif
