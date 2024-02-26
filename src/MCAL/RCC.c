#include "RCC.h"


/***********RCC REGISTERS****************/

#define RCC_CR *((volatile uint32_t*)0x40023800)
#define RCC_PLLCFGR *((volatile uint32_t*)0x40023804)
#define RCC_CFGR *((volatile uint32_t*)0x40023808)
#define RCC_CIR *((volatile uint32_t*)0x4002380C)
#define RCC_AHB1ENR *((volatile uint32_t*)0x40023830)
#define RCC_AHB2ENR *((volatile uint32_t*)0x40023834)
#define RCC_APB1ENR *((volatile uint32_t*)0x40023840)
#define RCC_APB2ENR *((volatile uint32_t*)0x40023844)
#define RCC_AHB1LPENR *((volatile uint32_t*)0x40023850)
#define RCC_AHB2LPENR *((volatile uint32_t*)0x40023854)
#define RCC_APB1LPENR *((volatile uint32_t*)0x40023860)
#define RCC_APB2LPENR *((volatile uint32_t*)0x40023864)


/*********Registers bits************/
#define SWS_MASK 0x0000000C
#define SW_MASK 0x00000003
#define PLLSRC_MASK 0x00400000 //For HSE Selected
#define SW_HSI 0
#define SW_HSE 1
#define SW_PLL 2
#define HSEBYP BIT_18_MASK

#define SWS_HSI 0
#define SWS_HSE 0x00000004
#define SWS_PLL 0x00000008

#define HSIRDY 0x00000001
#define HSERDY 0x00020000
#define PLLRDY 0x02000000

#define PLLCFGR_MASK 0x0F037FC0

/***********************IMPLEMENTATIONS*****************************/
RCCERRORCHECK_enu RCCControlCLK(RCCSYSCLK_enu Sysclk,RCCState_enu SysclkSTATE)
{
	RCCERRORCHECK_enu ReturnErrorStatus_enu = RCC_enuNOK;
	switch (Sysclk)
	{
	case Sysclk_HSI:
		if (SysclkSTATE == SysclkEnable) //CLK ENABLE
		{
			if (RCC_CR &Sysclk_HSI)
			{
				ReturnErrorStatus_enu = RCC_enuOK;
			}
			else//should i wait until its ready?
			{
				RCC_CR |= Sysclk_HSI ;
				ReturnErrorStatus_enu = RCC_enuOK;
			}
		}
		else
		{
			if ( (RCC_CFGR&SWS_MASK)== SWS_HSI )
			{
				ReturnErrorStatus_enu= RCC_enuDisabledDenied;
			}
			else if ( ((RCC_CFGR&SWS_MASK)==(SWS_PLL)) && (!(RCC_PLLCFGR&PLLSRC_MASK)))
			{
				ReturnErrorStatus_enu= RCC_enuDisabledDenied;
			}
			else
			{
				RCC_CR &= ~ Sysclk_HSI ;
				ReturnErrorStatus_enu = RCC_enuOK;
			}
		}
		break;

	case Sysclk_HSE :
		if (SysclkSTATE == SysclkEnable) //CLK ENABLE
		{
			if (RCC_CR &Sysclk_HSE)
			{
				ReturnErrorStatus_enu = RCC_enuOK;
			}
			else
			{
				RCC_CR &= ~ HSEBYP;
				RCC_CR |=Sysclk_HSE ;
				ReturnErrorStatus_enu = RCC_enuOK;
			}

		}
		else
		{
			if ( (RCC_CFGR&SWS_MASK)==SWS_HSE)
			{
				ReturnErrorStatus_enu= RCC_enuDisabledDenied;
			}
			else if (((RCC_CFGR&SWS_MASK)==(SWS_PLL)) && (RCC_PLLCFGR&PLLSRC_MASK))
			{
				ReturnErrorStatus_enu= RCC_enuDisabledDenied;
			}
			else
			{
				RCC_CR &= ~Sysclk_HSE ;
				ReturnErrorStatus_enu = RCC_enuOK;
			}
		}
		break;

	case Sysclk_PLL:
		if (SysclkSTATE == SysclkEnable) //CLK ENABLE
		{
			if (RCC_CR &Sysclk_PLL)
			{
				ReturnErrorStatus_enu = RCC_enuOK;
			}
			else
			{
				RCC_CR |= Sysclk_PLL ;
				ReturnErrorStatus_enu = RCC_enuOK;
			}
		}
		else
		{
			if ( (RCC_CFGR&SWS_MASK) == (SWS_PLL) )
			{
				ReturnErrorStatus_enu= RCC_enuDisabledDenied;
			}
			else
			{
				RCC_CR &= ~Sysclk_HSE ;
				ReturnErrorStatus_enu = RCC_enuOK;
			}
		}
		break;

	default:
		ReturnErrorStatus_enu= RCC_enuInvalidCLK;
		break;
	}

	return ReturnErrorStatus_enu;
}



RCCERRORCHECK_enu RCCSelectCLK(RCCSYSCLK_enu Sysclk)
{
	RCCERRORCHECK_enu ReturnErrorStatus_enu = RCC_enuNOK;
	uint8_t localmask;
	switch(Sysclk)
	{
	case Sysclk_HSI:

		if((RCC_CR&Sysclk_HSI)&&(RCC_CR&HSIRDY))
		{
			localmask = RCC_CFGR;
			localmask &= ~SW_MASK ;
			RCC_CFGR = localmask;
			ReturnErrorStatus_enu = RCC_enuOK;
		}
		else
		{
			if(RCC_CR&Sysclk_HSI)
			{
				ReturnErrorStatus_enu = RCC_enuCLKNotRDY;

			}
			else
			{
				ReturnErrorStatus_enu = RCC_enuCLKNotON;
			}
		}
		break;

	case Sysclk_HSE:
		if((RCC_CR&Sysclk_HSE)&&(RCC_CR&HSERDY))
		{
			localmask = RCC_CFGR;
			localmask &= ~SW_MASK ;
			localmask |= SW_HSE ;
			RCC_CFGR = localmask;
			ReturnErrorStatus_enu = RCC_enuOK;
		}
		else
		{
			if(RCC_CR&Sysclk_HSE)
			{
				ReturnErrorStatus_enu = RCC_enuCLKNotRDY;
			}
			else
			{
				ReturnErrorStatus_enu = RCC_enuCLKNotON;
			}
		}

		break;

	case Sysclk_PLL:
		if((RCC_CR&Sysclk_PLL)&&(RCC_CR&PLLRDY))
		{
			localmask = RCC_CFGR;
			localmask &= ~SW_MASK ;
			RCC_CFGR |=SW_PLL;
			RCC_CFGR = localmask;
			ReturnErrorStatus_enu = RCC_enuOK;
		}
		else
		{
			if(RCC_CR&Sysclk_HSI)
			{
				ReturnErrorStatus_enu = RCC_enuCLKNotRDY;
			}
			else
			{
				ReturnErrorStatus_enu = RCC_enuCLKNotON;
			}
		}
		break;

	default :
		ReturnErrorStatus_enu = RCC_enuInvalidCLK;
		break;
	}
	return ReturnErrorStatus_enu;
}
/*
RCCERRORCHECK_enu RCCSelectPRESCALER(RCCBUSES_enu Sysbus,uint16_t Prescaler)
{
	RCCERRORCHECK_enu ReturnErrorStatus_enu = RCC_enuNOK;
	uint8 localmask;
	switch(Sysbus)
	{
	case SysbusAHB1:
		if ((Prescaler<PrescalerAHB_2) &&(Prescaler>PrescalerAHB_512))
		{
			ReturnErrorStatus_enu = RCC_enuInvalidPRE;
		}
		else
		{
			localmask =RCC_CFGR;
			localmask &= ~ PrescalerAHB_512;
			localmask |= Prescaler;
			RCC_CFGR=localmask;
			ReturnErrorStatus_enu = RCC_enuOK;
		}
		break;

	case SysbusAPB1:
		if ((Prescaler<PrescalerAPB1_2) &&(Prescaler>PrescalerAPB1_16))
		{
			ReturnErrorStatus_enu = RCC_enuInvalidPRE;
		}
		else
		{
			localmask =RCC_CFGR;
			localmask &= ~ PrescalerAPB1_16;
			localmask |= Prescaler;
			RCC_CFGR=localmask;
			ReturnErrorStatus_enu = RCC_enuOK;
		}

		break;

	case SysbusAPB2:
		if ((Prescaler<PrescalerAPB2_2) &&(Prescaler>PrescalerAPB2_16))
		{
			ReturnErrorStatus_enu = RCC_enuInvalidPRE;
		}
		else
		{
			localmask =RCC_CFGR;
			localmask &= ~ PrescalerAPB2_16;
			localmask |= Prescaler;
			RCC_CFGR=localmask;
			ReturnErrorStatus_enu = RCC_enuOK;
		}
		break;
	}
	return ReturnErrorStatus_enu;
}*/

RCCERRORCHECK_enu ConfigPLL(uint16_t M ,uint16_t N,uint16_t Q,uint16_t P)
{
	RCCERRORCHECK_enu ReturnErrorStatus_enu = RCC_enuNOK;
	uint16_t localmask;
	switch (P)
	{
	case 2:
		P=0;
		break;
	case 4:
		P=1;
		break;
	case 6:
		P=2;
		break;
	case 8:
		P=3;
		break;
	default:
		ReturnErrorStatus_enu =RCC_enuInvaildParameter;
		break;
	}
	if ((M<2)&&(M>63))
	{
		ReturnErrorStatus_enu =RCC_enuInvaildParameter;
	}
	else if ((N<192)&&(N>432))
	{
		ReturnErrorStatus_enu =RCC_enuInvaildParameter;
	}
	else if ((Q<2)&&(Q>15))
	{
		ReturnErrorStatus_enu =RCC_enuInvaildParameter;
	}
	else
	{
		ReturnErrorStatus_enu = RCC_enuOK;
		localmask = RCC_PLLCFGR;
		localmask &= ~ PLLCFGR_MASK;
		localmask |= M | (N<< 6) | (P<<16) | (Q<<24);
		RCC_PLLCFGR = localmask;
	}
	return ReturnErrorStatus_enu;
}



RCCERRORCHECK_enu RCCEnablePripheral(uint32_t Pripheral,RCCBUSES_enu Sysbus)
{
	RCCERRORCHECK_enu ReturnErrorStatus_enu = RCC_enuNOK;

	switch(Sysbus)
	{
	case SysbusAHB1:
		RCC_AHB1ENR|=Pripheral;
		ReturnErrorStatus_enu = RCC_enuOK;
		break;

	case SysbusAHB2:
		RCC_AHB2ENR|=Pripheral;
		ReturnErrorStatus_enu = RCC_enuOK;
		break;
	case SysbusAPB1:
		RCC_APB1ENR|=Pripheral;
		ReturnErrorStatus_enu = RCC_enuOK;
		break;

	case SysbusAPB2:
		RCC_APB2ENR|=Pripheral;
		ReturnErrorStatus_enu = RCC_enuOK;
		break;

	default:
		ReturnErrorStatus_enu = RCC_enuInvalidPeripheral;
		break;
	}
	return ReturnErrorStatus_enu;
}



