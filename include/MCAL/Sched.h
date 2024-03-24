#ifndef SCHED_H_
#define SCHED_H_

#include "std_types.h"
#include "Error.h"
#include "Systick.h"

#define RUNNABLES_NUM 2
#define SCH_TICKS_MS 2

typedef void (*Runnable_Cb_t)(void);

typedef struct
{
    char * name;
    uint32_t periodicity_ms;
    uint32_t priority;
    Runnable_Cb_t cbf ;
} Runnable_t;

extern const Runnable_t Runnables_info [RUNNABLES_NUM];

void Sched_init(void);
void Sched_Start(void);

#endif