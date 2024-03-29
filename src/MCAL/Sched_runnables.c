#include "Sched.h"

/******************** System Runnables Prototypes********************/
//void LCD_TASK(void);
//void LCD_TEST (void);
void Uart_TxBuffer(void);
void Uart_Rxbuffer(void);


const Runnable_t Runnables_info [RUNNABLES_NUM]=
{
    [0] =
    {
        .name = "Uart_TxBuffer",
        .periodicity_ms = 1,
        .priority = 0,
        .cbf = Uart_TxBuffer,
    },    
    [1]=
    {
        .name = "Uart_RxBuffer",
        .periodicity_ms = 1,
        .priority = 1,
        .cbf = Uart_Rxbuffer,
    }, 
};


   
   /* [0]=
    {
        .name = "Traffic",
        .periodicity_ms = 1000,
        .priority = 0,
        .cbf = Traffic_Runnable,
    },
    
    
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
    }  */
    
