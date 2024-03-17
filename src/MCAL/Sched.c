#include "Sched.h"

extern const Runnable_t Runnables_info [RUNNABLES_NUM];
uint32_t Pendingticks;
static void Sched(void);
static void TICK_cb(void);
/*
Error_enumStatus_t Sched_RegisterRunnable( Runnable_t *r)
{
    Error_enumStatus_t ReturnStatus = Status_enumNotOk;
//for loop 3ala runnables num
    if ((r != NULL) && (runnable_info[r->priority].runnable == NULL))
    {
        ReturnStatus = Status_enumOk;
        runnable_info[r->priority].runnable = r;
        runnable_info[r->priority].remainingtime = r->periodicity_ms;
    }
    return ReturnStatus;
}*/

void Sched_init(void)
{
    STK_SetCallBackfun(TICK_cb);
    STK_SetTimer_ms(SCH_TICKS_MS);
}

void Sched_Start(void)
{
    STK_StatrTimer();
    while (1)
    {
        if (Pendingticks)
        {
            Pendingticks--;
            Sched();
        }
    }
}

static void Sched(void)
{
    uint32_t Localindex;
    static uint32_t timestamp = 0;
    for (Localindex = 0; Localindex < RUNNABLES_NUM; Localindex++)
    {
        if ((Runnables_info[Localindex].cbf) && (timestamp % Runnables_info[Localindex].periodicity_ms == 0))
        {
            Runnables_info[Localindex].cbf();
        }
    }
    timestamp += SCH_TICKS_MS;

}

static void TICK_cb(void)
{
    Pendingticks++;
}