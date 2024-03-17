#ifndef SCHED_H_
#define SCHED_H_

#include "std_types.h"
#include "Error.h"
#include "Systick.h"

#define RUNNABLES_NUM 1
#define SCH_TICKS_MS 1000

typedef void (*Runnable_Cb_t)(void);

typedef struct
{
    char * name;
    uint32_t periodicity_ms;
    uint32_t priority;
    Runnable_Cb_t cbf ;
} Runnable_t;

Error_enumStatus_t Sched_RegisterRunnable( Runnable_t *r);
void Sched_init(void);
void Sched_Start(void);

#endif