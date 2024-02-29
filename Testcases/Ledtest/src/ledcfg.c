#include "led.h"




LedCfg_str Ledcfg [_LEDNUM]=
{
		[Led_one]={
				.ledPORT=LED_PORTA,
				.ledPIN=LED_PIN0 ,
				.ledconnection=LED_ACTIVE_HIGH,
		},
		[Led_two]={
				.ledPORT=LED_PORTA,
				.ledPIN=LED_PIN1,
				.ledconnection=LED_ACTIVE_HIGH,
		}
};



