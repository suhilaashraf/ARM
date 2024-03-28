#include <stdio.h>
#include <stdlib.h>
#include "RCC.h"
#include "Nvic.h"
#include "Uart.h"
#include "gpio.h"
#include "sched.h"
#include "Led.h"




int main()
{

	GPIOPIN_t uart;
	uint8_t buf [4] = {1,2,3,4};
	RCCEnablePripheral(RCC_GPIOB, SysbusAHB1);
	RCCEnablePripheral(RCC_USART1,SysbusAPB2);
	uart.gpioPORT= GPIO_PORTB;
	uart.gpioPIN = GPIO_PIN6;
	uart.gpioMODE = GPIO_AF_PP;
	uart.GPIO_AF = GPIO_AF_USART1_2;
	uart.gpioSPEED = GPIO_HIGHSPEED;
	GPIO_InitPin(&uart);   
	NVIC_EnableIRQ(IRQ_USART1);
	Uart_TxBufferAsync(buf,4,UART_1);
	Sched_init();
	Sched_Start();



	while (1)
	{
		
	}
}
