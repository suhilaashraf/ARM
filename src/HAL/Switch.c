/*
 * Switch.c
 * Created on: Feb 26, 2024
 * Author: Suhila Ashraf
 */
#include "Switch.h"

extern SWITCHCFG_str Switches[_SWITCH_NUM];

uint8_t SwitchesStates[_SWITCH_NUM];

Error_enumStatus_t SWITCH_init(void)
{
	Error_enumStatus_t RETURN_ERRORSTATUS = Status_enumNotOk;
	uint8_t localCounter, Errorcheck = 0;
	GPIOPIN_t Switch;
	Switch.gpioSPEED = GPIO_HIGHSPEED;
	for (localCounter = 0; localCounter < _SWITCH_NUM; localCounter++)
	{
		Switch.gpioPORT = Switches[localCounter].SwitchPORT;
		Switch.gpioPIN = Switches[localCounter].SwitchPINnumber;
		Switch.gpioMODE = Switches[localCounter].SwitchConnection;
		RETURN_ERRORSTATUS = GPIO_InitPin(&Switch);
		if (RETURN_ERRORSTATUS != Status_enumOk)
		{
			Errorcheck++;
		}
	}
	if (Errorcheck == 0)
	{
		RETURN_ERRORSTATUS = Status_enumOk;
	}
	else
	{
		RETURN_ERRORSTATUS = Status_enumParameterError;
	}
	return RETURN_ERRORSTATUS;
}

Error_enumStatus_t SWITCH_GETSTATUS(SWITCHES_enu Switchname, uint8_t *SwitchStatus)
{
	Error_enumStatus_t RETURN_ERRORSTATUS = Status_enumNotOk;
	if (Switchname > _SWITCH_NUM)
	{
		RETURN_ERRORSTATUS = Status_enumParameterError;
	}
	else if (SwitchStatus == NULL)
	{
		RETURN_ERRORSTATUS = Status_enumNULLPointer;
	}
	else
	{
		RETURN_ERRORSTATUS = Status_enumOk;
		*SwitchStatus = SwitchesStates[Switchname];
		if (Switches[Switchname].SwitchConnection == SWITCH_PULLUP)
		{
			*SwitchStatus = *SwitchStatus ^ 1;
		}
	}
		return RETURN_ERRORSTATUS;
}

void SWITCH_Runabble(void)
{
	static uint8_t counter[_SWITCH_NUM];
	static uint8_t current;
	static uint8_t pervious[_SWITCH_NUM];
	uint8_t localindex;
	for (localindex = 0; localindex < _SWITCH_NUM; localindex++)
	{
		GPIO_GetPinValue(Switches[localindex].SwitchPORT, Switches[localindex].SwitchPINnumber, &current);
		if (current == pervious[localindex])
		{
			counter[localindex]++;
		}
		else
		{
			counter[localindex] = 0;
		}
		if (counter[localindex] % 5 == 0)
		{
			SwitchesStates[localindex] = current;
		}
		pervious[localindex] = current;
	}
}
