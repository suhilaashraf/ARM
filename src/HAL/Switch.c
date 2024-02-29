/*
 * Switch.c
 * Created on: Feb 26, 2024
 * Author: Suhila Ashraf
 */
#include "Switch.h"

extern SWITCHCFG_str Switches [_SWITCH_NUM ];

Error_enumStatus_t SWITCH_INIT (void)
{
	Error_enumStatus_t RETURN_ERRORSTATUS=Status_enumNotOk;
	uint8_t localCounter,Errorcheck=0;
	GPIOPIN_t Switch;
	Switch.gpioSPEED = GPIO_HIGHSPEED;
	for (localCounter =0 ;localCounter< _SWITCH_NUM ;localCounter++)
	{
		Switch.gpioPORT =Switches[localCounter].SwitchPORT;
		Switch.gpioPIN = Switches[localCounter].SwitchPINnumber;
		Switch.gpioMODE = Switches[localCounter].SwitchConnection;
		RETURN_ERRORSTATUS =GPIO_InitPin(&Switch);
		if (RETURN_ERRORSTATUS != Status_enumOk)
		{
			Errorcheck ++;
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

Error_enumStatus_t SWITCH_GETSTATUS(SWITCHES_enu Switchname , uint32_t* SwitchStatus)
{
	Error_enumStatus_t RETURN_ERRORSTATUS=Status_enumNotOk;
	if (Switchname > _SWITCH_NUM)
	{
		RETURN_ERRORSTATUS=Status_enumParameterError;
	}
	else if (SwitchStatus == NULL)
	{
		RETURN_ERRORSTATUS=Status_enumNULLPointer;
	}
	else
	{
		RETURN_ERRORSTATUS=GPIO_GetPinValue(Switches[Switchname].SwitchPORT, Switches[Switchname].SwitchPINnumber,SwitchStatus);
		if (Switches[Switchname].SwitchConnection == SWITCH_PULLUP)
		{
			*SwitchStatus = *SwitchStatus ^1;
		}
	}

	return RETURN_ERRORSTATUS;
}


