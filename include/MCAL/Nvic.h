#ifndef NVIC_H_
#define NVIC_H_

#include "std_types.h"
#include "Error.h"
#include "Mask.h"
#include "Interrupts.h"
 
/***********************Group priority bits**************************************/

#define Subpriority_0bits       0
#define Subpriority_1bits       4
#define Subpriority_2bits       5
#define Subpriority_3bits       6
#define Subpriority_4bits       7

#define MAX_SUBpriority         7

#define SubpriorityBits             Subpriority_0bits  


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

/***********************APIs Prototypes**************************************/
Error_enumStatus_t NVIC_EnableIRQ(uint32_t IRQn);
Error_enumStatus_t NVIC_DisableIRQ(uint32_t IRQn);
Error_enumStatus_t NVIC_SetPendingIRQ(uint32_t IRQn);
Error_enumStatus_t NVIC_ClearPendingIRQ(uint32_t IRQn);
Error_enumStatus_t NVIC_GetActive(uint32_t *IRQn);
Error_enumStatus_t NVIC_SetSubPriority(uint32_t SubpriorityBits);
Error_enumStatus_t NVIC_SetPriority(uint32_t IRQn, uint32_t priority , uint32_t Subpriority);
Error_enumStatus_t NVIC_GetPriority(uint32_t *IRQn);
Error_enumStatus_t NVIC_SoftwareReset(uint32_t IRQn);
Error_enumStatus_t NVIC_SystemReset(void);


#endif /*NVIC_H_*/
