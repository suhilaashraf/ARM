#include "Switch.h"


SWITCHCFG_str Switches [_SWITCH_NUM ]=
{
		[Switch_one]=
		{
				.SwitchPORT = SWITCH_PORTA,
				.SwitchPINnumber = SWITCH_PIN0,
				.SwitchConnection = SWITCH_PULLUP,
		},
		[Switch_two]=
		{
				.SwitchPORT = SWITCH_PORTB,
				.SwitchPINnumber = SWITCH_PIN0,
				.SwitchConnection = SWITCH_PULLDOWN,
		}
};
