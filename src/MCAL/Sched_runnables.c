#include "Sched.h"

/******************** System Runnables Prototypes********************/
void SWITCH_Runabble(void);
void Traffic_Runnable(void);

const Runnable_t Runnables_info [RUNNABLES_NUM]=
{
    [0]=
    {
        .name = "Traffic",
        .periodicity_ms = 1000,
        .priority = 0,
        .cbf = Traffic_Runnable,
    },
    
    /*
    [0]=
    {
        .name = "Switch",
        .periodicity_ms = 5,
        .priority = 0,
        .cbf = SWITCH_Runabble,
    },
    [1] =
    {
        .name = "APP1",
        .periodicity_ms = 50,
        .priority = 1,
        .cbf = APP1,
    }   */
};