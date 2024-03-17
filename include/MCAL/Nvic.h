#ifndef NVIC_H_
#define NVIC_H_

//#include "std_types.h"
#include "stdint.h"
#include "Error.h"
#include "Mask.h"
#include "Interrupts.h"

/***********************Priority Levels **************************************/
#define PRI0                        0x00000000
#define PRI1                        0x00000010
#define PRI2                        0x00000020
#define PRI3                        0x00000030
#define PRI4                        0x00000040
#define PRI5                        0x00000050
#define PRI6                        0x00000060
#define PRI7                        0x00000070
#define PRI8                        0x00000080
#define PRI9                        0x00000090
#define PRI10                       0x000000A0
#define PRI11                       0x000000B0
#define PRI12                       0x000000C0
#define PRI13                       0x000000D0
#define PRI14                       0x000000E0
#define PRI15                       0x000000F0

#define MAXpriority                 0x000000F0

/***********************Group priority bits**************************************/
#define Priority_FOURbits             0x05FA0000 /*16 priority levels- none sub priority*/
#define Priority_THREEbits            0x05FA0400 /*8  priority levels - two sub priority group*/
#define Priority_TWObits              0x05FA0500 /*4  priority levels- none sub priority group*/
#define Priority_ONEbits              0x05FA0600 /*2  priority levels- none sub priority group*/
#define Priority_none                 0x05FA0700 /*0 priority levels- none sub priority group*/

#define MAX_PriorityBITS               7

#define PriorityBits                Priority_3bits

/***********************APIs Prototypes**************************************/
Error_enumStatus_t NVIC_EnableIRQ(uint32_t IRQn);
Error_enumStatus_t NVIC_DisableIRQ(uint32_t IRQn);
Error_enumStatus_t NVIC_SetPendingIRQ(uint32_t IRQn);
Error_enumStatus_t NVIC_ClearPendingIRQ(uint32_t IRQn);
Error_enumStatus_t NVIC_GetActive(uint32_t *IRQn);
Error_enumStatus_t NVIC_SetPriorityLevels(uint32_t Priority_bits);
Error_enumStatus_t NVIC_SetPriority (uint32_t IRQn, uint8_t PRI);
Error_enumStatus_t NVIC_GetPriority(uint32_t IRQn , uint32_t* priority);
Error_enumStatus_t NVIC_TriggerSoftwareINT(uint32_t IRQn);
Error_enumStatus_t NVIC_SystemReset(void);


#endif /*NVIC_H_*/
