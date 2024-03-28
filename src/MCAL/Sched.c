#include "Sched.h"


uint32_t Pendingticks;
static void Sched(void);
static void TICK_cb(void);

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