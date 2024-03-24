#include "Nvic.h"
/***********************NVIC REGISTERS********************************/
#define NVIC_ISER       ((volatile uint32_t *)0xE000E100)
#define NVIC_ICER       ((volatile uint32_t *)0xE000E180)
#define NVIC_ISPR       ((volatile uint32_t *)0xE000E200)
#define NVIC_ICPR       ((volatile uint32_t *)0xE000E280)
#define NVIC_IABR       ((volatile uint32_t *)0xE000E300)
#define NVIC_IPR        ((volatile uint32_t *)0xE000E400)
#define NVIC_STIR       ((volatile uint32_t *)0xE000EF00)
#define AIRCR           *((volatile uint32_t *)0xE000ED0C)

#define MAX_IRQn        84
#define VECTKEY_WRITE   0x05FA0000
#define VECTKEY_SHIFT   16
#define VECTKEY_Clear   0xFFFF0000

#define PRIGROUP_SHIFT  8
#define PRIGROUP_CLEAR  0xFFFF0700

#define PRIMASK         0x000000F0

#define BITS_PER_REG    32
#define STIQ_MASK       0x000000FF

#define BITS_PER_PRIREG 4
#define BITS_PER_BYTE   8
/***********************APIs Implmenation********************************/

Error_enumStatus_t NVIC_EnableIRQ(uint32_t IRQn)
{
    Error_enumStatus_t ReturnErrorStatus = Status_enumNotOk;
    uint8_t Localindex;
    if (IRQn > MAX_IRQn)
    {
        ReturnErrorStatus = Status_enumParameterError;
    }
    else
    {
        ReturnErrorStatus = Status_enumOk;
        Localindex = IRQn / BITS_PER_REG;
        NVIC_ISER[Localindex] = (BIT_0_MASK << (IRQn % BITS_PER_REG));
    }
    return ReturnErrorStatus;
}

Error_enumStatus_t NVIC_DisableIRQ(uint32_t IRQn)
{
    Error_enumStatus_t ReturnErrorStatus = Status_enumNotOk;
    uint8_t Localindex;
    if (IRQn > MAX_IRQn)
    {
        ReturnErrorStatus = Status_enumParameterError;
    }
    else
    {
        ReturnErrorStatus = Status_enumOk;
        Localindex = IRQn / BITS_PER_REG;
        NVIC_ICER[Localindex] = (BIT_0_MASK << (IRQn % BITS_PER_REG));
    }
    return ReturnErrorStatus;
}

Error_enumStatus_t NVIC_SetPendingIRQ(uint32_t IRQn)
{
    Error_enumStatus_t ReturnErrorStatus = Status_enumNotOk;
    uint8_t Localindex;
    if (IRQn > MAX_IRQn)
    {
        ReturnErrorStatus = Status_enumParameterError;
    }
    else
    {
        ReturnErrorStatus = Status_enumOk;
        Localindex = IRQn / BITS_PER_REG;
        NVIC_ISPR[Localindex] = (BIT_0_MASK << (IRQn % BITS_PER_REG));
    }
    return ReturnErrorStatus;
}

Error_enumStatus_t NVIC_ClearPendingIRQ(uint32_t IRQn)
{
    Error_enumStatus_t ReturnErrorStatus = Status_enumNotOk;
    uint8_t Localindex;

    if (IRQn > MAX_IRQn)
    {
        ReturnErrorStatus = Status_enumParameterError;
    }
    else
    {
        ReturnErrorStatus = Status_enumOk;
        Localindex = IRQn / BITS_PER_REG;
        NVIC_ICPR[Localindex] = (BIT_0_MASK << (IRQn % BITS_PER_REG));
    }
    return ReturnErrorStatus;
}

Error_enumStatus_t NVIC_GetActive(uint32_t *IRQn)
{
    Error_enumStatus_t ReturnErrorStatus = Status_enumNotOk;
    uint8_t Localindex;
    if (*IRQn > MAX_IRQn)
    {
        ReturnErrorStatus = Status_enumParameterError;
    }
    else
    {
        ReturnErrorStatus = Status_enumOk;
        Localindex = *IRQn / BITS_PER_REG;
        *IRQn = ( (NVIC_ICPR[Localindex] >> (*IRQn % BITS_PER_REG) ) & (BIT_0_MASK ) );
    }
    return ReturnErrorStatus;
}

Error_enumStatus_t NVIC_SetPriorityLevels(uint32_t Priority_bits)
{
    Error_enumStatus_t ReturnErrorStatus = Status_enumNotOk;
    uint8_t* IRQn_ptr =(uint8_t*)&Priority_bits;
    uint32_t localmask;
    if ((*(IRQn_ptr++)) > MAX_PriorityBITS)
    {
        ReturnErrorStatus = Status_enumParameterError;
    }
    else
    {
        ReturnErrorStatus = Status_enumOk;
        localmask = AIRCR;
        localmask &= ~PRIGROUP_CLEAR;
        localmask |= Priority_bits;
        AIRCR = localmask;
    }

    return ReturnErrorStatus;
}

Error_enumStatus_t NVIC_SetPriority (uint32_t IRQn, uint8_t PRI)
{
    Error_enumStatus_t ReturnErrorStatus = Status_enumNotOk;
    uint8_t localindex;
    uint8_t localshift;
    uint32_t localmask;
    if (IRQn > MAX_IRQn)
    {
        ReturnErrorStatus = Status_enumParameterError;
    }
    else if (PRI> MAXpriority)
    {
        ReturnErrorStatus = Status_enumCFGError;
    }
    else
    {
        ReturnErrorStatus = Status_enumOk;
        localindex = IRQn / BITS_PER_PRIREG;
        localshift = (IRQn % BITS_PER_PRIREG)*BITS_PER_BYTE;
        localmask = NVIC_IPR[localindex];
        localmask &= ~ (PRIMASK <<localshift);
        localmask |= (PRI << localshift);
        NVIC_IPR[localindex] = localmask;
    }
    return ReturnErrorStatus;
}

Error_enumStatus_t NVIC_GetPriority(uint32_t IRQn , uint32_t* priority)
{
    Error_enumStatus_t ReturnErrorStatus = Status_enumNotOk;
    uint8_t localindex;
    uint8_t localshift;
    if (IRQn > MAX_IRQn)
    {
        ReturnErrorStatus = Status_enumParameterError;
    }
    else
    {
        ReturnErrorStatus = Status_enumOk;
        localindex = IRQn / BITS_PER_PRIREG;
        localshift = (IRQn % BITS_PER_PRIREG)*BITS_PER_BYTE;
        *priority =(NVIC_IPR[localindex]>> localshift) & (PRIMASK);
    }
    return ReturnErrorStatus;
}


Error_enumStatus_t NVIC_TriggerSoftwareINT(uint32_t IRQn)
{
    Error_enumStatus_t ReturnErrorStatus = Status_enumNotOk;
    uint32_t localmask;
    if (IRQn > MAX_IRQn)
    {
        ReturnErrorStatus = Status_enumParameterError;
    }
    else
    {
        ReturnErrorStatus = Status_enumOk;
        localmask = *NVIC_STIR;
        localmask &= ~ STIQ_MASK;
        localmask |= IRQn;
       *NVIC_STIR = localmask;
    }
    return ReturnErrorStatus;
}
