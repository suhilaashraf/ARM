#include "Lcdcfg.h"
#include "gpio.h"


LCDCFG_str Lcd_cfg [LCDPINS]=
{
	
	[RS]=
	{
		.Lcdport = GPIO_PORTA,
		.Lcdpin = GPIO_PIN0    
	},
	[RW]=
	{
		.Lcdport = GPIO_PORTA,
		.Lcdpin = GPIO_PIN1
	},
	[EN]=
	{
		.Lcdport = GPIO_PORTA,
		.Lcdpin = GPIO_PIN2
	},		
	[DB0]=
	{
		.Lcdport = GPIO_PORTA,
		.Lcdpin = GPIO_PIN3
	},	
	[DB1]=
	{
		.Lcdport = GPIO_PORTA,
		.Lcdpin =GPIO_PIN4
	},	
	[DB2]=
	{
		.Lcdport = GPIO_PORTA,
		.Lcdpin = GPIO_PIN5
	},
	[DB3]=
	{
		.Lcdport = GPIO_PORTA,
		.Lcdpin = GPIO_PIN6
	},		
	[DB4]=
	{
		.Lcdport = GPIO_PORTA,
		.Lcdpin = GPIO_PIN7
	},	
	[DB5]=
	{
		.Lcdport = GPIO_PORTB,
		.Lcdpin = GPIO_PIN0
	},	
	[DB6]=
	{
		.Lcdport = GPIO_PORTB,
		.Lcdpin = GPIO_PIN1
	},
	[DB7]=
	{
		.Lcdport = GPIO_PORTB,
		.Lcdpin = GPIO_PIN2
	},	    
};