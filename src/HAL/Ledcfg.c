#include "Ledcfg.h"
#include "Led.h"

LedCfg_str Ledcfg[_LEDNUM] =
	{
		[GREEN] = {
			.ledPORT = LED_PORTB,
			.ledPIN = LED_PIN2,
			.ledconnection = LED_ACTIVE_HIGH,
		},

		[YELLOW] = {
			.ledPORT = LED_PORTB,
			.ledPIN = LED_PIN0,
			.ledconnection = LED_ACTIVE_HIGH,
		},

		[RED] = {
			.ledPORT = LED_PORTA,
			.ledPIN = LED_PIN0,
			.ledconnection = LED_ACTIVE_HIGH,
		},

};
