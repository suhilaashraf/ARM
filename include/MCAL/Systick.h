#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "Error.h"
#include "Mask.h"
#include "std_types.h"

#define CLOCK_FREQUENCY_MHZ  16000000

typedef void (* SystickCbf_t)(void);

/***********************APIs Prototypes**************************************/

Error_enumStatus_t STK_SetTimer_ms(uint32_t time_ms);
Error_enumStatus_t STK_SetCallBackfun(SystickCbf_t Cbf);
Error_enumStatus_t STK_SettimerCFG (void);
Error_enumStatus_t STK_StatrTimer (void);
Error_enumStatus_t STK_StopTimer (void);

#endif /*SYSTICK_H_*/