#include <stdio.h>
#include <stdlib.h>
#include "RCC.h"
#include "Sched.h"
#include "Lcd.h"


int main()
{   
	RCCEnablePripheral(GPIOA, SysbusAHB1);
	RCCEnablePripheral(GPIOB, SysbusAHB1);
	
	Lcdinit_Asyn();
	Sched_init();
	Sched_Start();
}
