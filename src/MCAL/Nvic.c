#include "Nvic.h"
/***********************NVIC REGISTERS********************************/
#define NVIC_ISER ((volatile uint32_t *)0xE000E100)
#define NVIC_ICER ((volatile uint32_t *)0xE000E180)
#define NVIC_ISPR ((volatile uint32_t *)0xE000E200)
#define NVIC_ICPR ((volatile uint32_t *)0xE000E280)
#define NVIC_IABR ((volatile uint32_t *)0xE000E180)
#define NVIC_IPR ((volatile uint32_t *)0xE000E200)
#define NVIC_STIR ((volatile uint32_t *)0xE000E280)
#define AIRCR *((volatile uint32_t *)0xE000E280)

/**
 * Mask :(OFFSETID:0000)(IRQBIT:0000)
 */
#define GET_OFFSETID 0x00000003
#define GET_IRQBIT 0x0000001F
#define SOFTWAREINT 0xFF

#define MAX_IRQn 31
#define VECTKEY_WRITE 0x5FA
#define VECTKEY_SHIFT 15
#define VECTKEY_Clear 0xFFFF0000

#define PRIGROUP_SHIFT              8
#define PRIGROUP_CLEAR              0x00000700

#define PRIMASK                     0xF0

/********************************typedef********************************/

/***********************APIs Implmenation********************************/

Error_enumStatus_t NVIC_EnableIRQ(uint32_t IRQn)
{
    Error_enumStatus_t ReturnErrorStatus = Status_enumNotOk;
    uint8_t *IRQ_ptr = (uint8_t *)&IRQn;
    uint32_t *localReg;
    if (*IRQ_ptr > MAX_IRQn)
    {
        ReturnErrorStatus = Status_enumParameterError;
    }
    else
    {
        ReturnErrorStatus = Status_enumOk;
        localReg = NVIC_ISER + *(IRQ_ptr++);
        *localReg |= (BIT_0_MASK << *IRQ_ptr);
    }
    return ReturnErrorStatus;
}

Error_enumStatus_t NVIC_DisableIRQ(uint32_t IRQn)
{
    Error_enumStatus_t ReturnErrorStatus = Status_enumNotOk;
    uint8_t *IRQ_ptr = (uint8_t *)&IRQn;
    uint32_t *localReg;

    if (*IRQ_ptr > MAX_IRQn)
    {
        ReturnErrorStatus = Status_enumParameterError;
    }
    else
    {
        ReturnErrorStatus = Status_enumOk;
        localReg = NVIC_ICER + *(IRQ_ptr++);
        *localReg |= (BIT_0_MASK << *IRQ_ptr);
    }
    return ReturnErrorStatus;
}

Error_enumStatus_t NVIC_SetPendingIRQ(uint32_t IRQn)
{
    Error_enumStatus_t ReturnErrorStatus = Status_enumNotOk;
    uint8_t *IRQ_ptr = (uint8_t *)&IRQn;
    uint32_t *localReg;
    if (*IRQ_ptr > MAX_IRQn)
    {
        ReturnErrorStatus = Status_enumParameterError;
    }
    else
    {
        ReturnErrorStatus = Status_enumOk;
        localReg = NVIC_ISPR + *(IRQ_ptr++);
        *localReg |= (BIT_0_MASK << *IRQ_ptr);
    }
    return ReturnErrorStatus;
}

Error_enumStatus_t NVIC_ClearPendingIRQ(uint32_t IRQn)
{
    Error_enumStatus_t ReturnErrorStatus = Status_enumNotOk;
    uint8_t *IRQ_ptr = (uint8_t *)&IRQn;
    uint32_t *localReg;
    if (*IRQ_ptr > MAX_IRQn)
    {
        ReturnErrorStatus = Status_enumParameterError;
    }
    else
    {
        ReturnErrorStatus = Status_enumOk;
        localReg = NVIC_ICPR + *(IRQ_ptr++);
        *localReg |= (BIT_0_MASK << *IRQ_ptr);
    }
    return ReturnErrorStatus;
}

Error_enumStatus_t NVIC_GetActive(uint32_t *IRQn)
{
    Error_enumStatus_t ReturnErrorStatus = Status_enumNotOk;
    uint8_t *IRQ_ptr = (uint8_t *)&IRQn;
    uint32_t *localReg;
    if (*IRQ_ptr > MAX_IRQn)
    {
        ReturnErrorStatus = Status_enumParameterError;
    }
    else
    {
        ReturnErrorStatus = Status_enumOk;
        localReg = NVIC_IABR + *(IRQ_ptr++);
        *IRQn = (BIT_0_MASK & (*localReg >> *IRQ_ptr));
    }
    return ReturnErrorStatus;
}

Error_enumStatus_t NVIC_SoftwareReset(uint32_t IRQn)
{

    Error_enumStatus_t ReturnErrorStatus = Status_enumNotOk;
    uint8_t *IRQ_ptr = (uint8_t *)&IRQn;
    uint8_t localoffset;
    uint32_t localmask;

    if (*IRQ_ptr > MAX_IRQn)
    {
        ReturnErrorStatus = Status_enumParameterError;
    }
    else
    {
        ReturnErrorStatus = Status_enumOk;
        localoffset = *IRQ_ptr + ((*(IRQ_ptr++)) * 32);
        localmask = NVIC_STIR;
        localmask &= ~SOFTWAREINT;
        localmask |= localoffset;
        NVIC_STIR = localmask;
    }

    return ReturnErrorStatus;
}

Error_enumStatus_t NVIC_SetSubPriority(void)
{
    Error_enumStatus_t ReturnErrorStatus = Status_enumNotOk;
    uint32_t localmask;
    if (SubpriorityBits > MAX_SUBpriority)
    {
        ReturnErrorStatus = Status_enumParameterError;
    }
    else
    {
        ReturnErrorStatus = Status_enumOk;
        localmask = AIRCR;
        localmask &= ~VECTKEY_Clear;
        localmask |= (VECTKEY_WRITE << VECTKEY_SHIFT);
        AIRCR = localmask;

        localmask &= ~PRIGROUP_CLEAR;
        localmask |= (SubpriorityBits << PRIGROUP_SHIFT);
        AIRCR = localmask;
    }

    return ReturnErrorStatus;
}

Error_enumStatus_t NVIC_SetPriority(uint32_t IRQn,uint8_t priority, uint8_t Subpriority)
{
    Error_enumStatus_t ReturnErrorStatus = Status_enumNotOk;
    uint8_t *IRQ_ptr = (uint8_t *)&IRQn;
    uint32_t *localReg;
    uint32_t localmask;
    uint8_t prioritymask,subprioritymask,totalpriority;
    uint8_t PRISHIFT ;
    if (*IRQ_ptr > MAX_IRQn)
    {
        ReturnErrorStatus = Status_enumParameterError;
    }
    else if (SubpriorityBits > MAX_SUBpriority)
    {
        ReturnErrorStatus = Status_enumCFGError;
    }
    else if (priority > MAXpriority)
    {
        ReturnErrorStatus = Status_enumParameterError;
    }
    else if (Subpriority > MAXpriority)
    {
        ReturnErrorStatus = Status_enumParameterError;
    }    
    else
    {
        ReturnErrorStatus = Status_enumOk;
        


        PRISHIFT = (*(IRQ_ptr+2)/4) * 8;
        localReg = NVIC_IPR + *(IRQ_ptr+2);
        localmask &= ~ PRIMASK;
        localmask |=(totalpriority << PRISHIFT);
        *localReg = localmask ;
        
        
        
        
        
        switch (SubpriorityBits)
        {
        case Subpriority_0bits :
            
            break;

        case Subpriority_1bits :
            break;

        case Subpriority_2bits :
            break;

        case Subpriority_3bits :
            break;

        case Subpriority_4bits :
            break;  

        default:
            break;
        }



    }
    return ReturnErrorStatus;
}

Error_enumStatus_t NVIC_GetPriority(uint32_t *IRQn)
{
    Error_enumStatus_t ReturnErrorStatus = Status_enumNotOk;
    uint8_t *IRQ_ptr = (uint8_t *)&IRQn;
    uint32_t *localReg;
    if (*IRQ_ptr > MAX_IRQn)
    {
        ReturnErrorStatus = Status_enumParameterError;
    }
    else
    {
        ReturnErrorStatus = Status_enumOk;
        



    }
    return ReturnErrorStatus;
}
