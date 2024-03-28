#include "Led.h"
#include "Sched.h"

#define periodicity 2 //2 sec

void Traffic_init(void)
{
    LED_init();
}
/*
void Traffic_Runnable(void)
{
    static uint8_t State= GREEN;
    static uint8_t timecounter_sec;
    timecounter_sec += periodicity;

    switch (State)
    {
    case GREEN:// 6 sec
        Led_SetStatus(GREEN,LED_ON);
        Led_SetStatus(YELLOW,LED_OFF);
        Led_SetStatus(RED,LED_OFF);
        if (timecounter_sec == 6)
        {
            State = YELLOW;
        }
        break;
    
    case YELLOW://2 sec
        Led_SetStatus(GREEN,LED_OFF);
        Led_SetStatus(YELLOW,LED_ON);
        Led_SetStatus(RED,LED_OFF);
        if (timecounter_sec == 8)
        {
            State = RED;
        }
        else if (timecounter_sec == 16)
        {
            State = GREEN;
            timecounter_sec=0;
        }
        break;

    
    case RED:// 6 sec
        Led_SetStatus(GREEN,LED_OFF);
        Led_SetStatus(YELLOW,LED_OFF);
        Led_SetStatus(RED,LED_ON);
        if (timecounter_sec == 14)
        {
            State = YELLOW;
        }
        break;

    default:
        break;
    }   

}
*/