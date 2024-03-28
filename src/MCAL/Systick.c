#include "Systick.h"

#define STK_BASE (void *)(0xE000E010)
#define COUNTER_ENABLE 0x00000001
#define TICKINT 0x00000002
#define SEC_TO_MS 1000
#define RELOAD_LOW_BOUNDARY 0x00000001
#define RELOAD_HIGH_BOUNDARY 0x00FFFFFF

typedef struct
{
    uint32_t STK_CTRL;
    uint32_t STK_LOAD;
    uint32_t STK_VAL;
    uint32_t STK_CALIB;
} Systick_t;

static SystickCbf_t APPCallBackFun = NULL;
/***********************APIs Implmenation********************************/

Error_enumStatus_t STK_StatrTimer(void)
{
    Error_enumStatus_t ReturnErrorStatus;
    Systick_t *STK = (Systick_t *)STK_BASE;
    STK->STK_CTRL |= COUNTER_ENABLE;
    STK->STK_CTRL |= TICKINT;
    ReturnErrorStatus = Status_enumOk;
    return ReturnErrorStatus;
}

Error_enumStatus_t STK_StopTimer(void)
{
    Error_enumStatus_t ReturnErrorStatus;
    Systick_t *STK = (Systick_t *)STK_BASE;
    STK->STK_CTRL &= ~(COUNTER_ENABLE);
    ReturnErrorStatus = Status_enumOk;
    return ReturnErrorStatus;
}

Error_enumStatus_t STK_SetTimer_ms(uint32_t time_ms)
{
    Error_enumStatus_t ReturnErrorStatus = Status_enumNotOk;
    uint32_t Localloadvalue;
    Systick_t *STK = (Systick_t *)STK_BASE;

    Localloadvalue =( ((CLOCK_FREQUENCY_MHZ /8)* time_ms) / (SEC_TO_MS)-1) ;

    if ((Localloadvalue >RELOAD_HIGH_BOUNDARY) || (Localloadvalue <RELOAD_LOW_BOUNDARY) )
    {
        ReturnErrorStatus = Status_enumParameterError;
    }
    else
    {
        ReturnErrorStatus = Status_enumOk;
        STK->STK_LOAD = Localloadvalue;
        STK->STK_VAL = 0;
    }
    return ReturnErrorStatus;
}

Error_enumStatus_t STK_SetCallBackfun(SystickCbf_t Cbf)
{
    Error_enumStatus_t ReturnErrorStatus = Status_enumNotOk;

    if (Cbf != NULL)
    {
        APPCallBackFun = Cbf;
        ReturnErrorStatus = Status_enumOk;
    }
    else
    {
        ReturnErrorStatus = Status_enumNULLPointer;
    }

    return ReturnErrorStatus;
}

void SysTick_Handler(void)
{
    if (APPCallBackFun != NULL)
    {
        APPCallBackFun();
    }
}
