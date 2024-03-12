#ifndef NVIC_H_
#define NVIC_H_

#include "std_types.h"
#include "Error.h"
#include "Mask.h"
#include "Interrupts.h"
 
/***********************Priority Levels **************************************/
#define PRI0                        0
#define PRI1                        1
#define PRI2                        2  
#define PRI3                        3
#define PRI4                        4
#define PRI5                        5
#define PRI6                        6
#define PRI7                        7
#define PRI8                        8
#define PRI9                        9   
#define PRI10                       10    
#define PRI11                       11
#define PRI12                       12
#define PRI13                       13
#define PRI14                       14
#define PRI15                       15
#define MAXpriority                 15

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
Error_enumStatus_t NVIC_GetPriority(uint32_t *IRQn);
Error_enumStatus_t NVIC_TriggerSoftwareINT(uint32_t IRQn);
Error_enumStatus_t NVIC_SystemReset(void);


#endif /*NVIC_H_*/
