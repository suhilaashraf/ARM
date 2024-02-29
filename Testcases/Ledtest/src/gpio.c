#include "gpio.h"

/********************GPIO MASKS********************/
#define GPIO_GETMODE		0x00000003

/********************GPIO Registers********************/
typedef struct
{
	uint32_t MODER     ;
	uint32_t OTYPER    ;
	uint32_t OSPEEDR   ;
	uint32_t PUPDR     ;
	uint32_t IDR       ;
	uint32_t ODR       ;
	uint32_t BSRR      ;
	uint32_t LCKR      ;
	uint32_t AFRL      ;
	uint32_t AFRH      ;
}GPIO_t;



/********************GPIO APIS Implementations********************/
Error_enumStatus_t GPIO_InitPin(GPIOPIN_t* gpiopin)
{
	Error_enumStatus_t RETURN_ERRORSTATUS=Status_enumNotOk;
	uint16_t* gpioptr =NULL;
	uint16_t localmask;
	gpioptr = (uint16_t*)&gpiopin->gpioMODE;
	if (gpiopin == NULL)
	{
		RETURN_ERRORSTATUS=Status_enumNULLPointer ;
	}
	else if( !((gpiopin->gpioPORT == GPIO_PORTA)||(gpiopin->gpioPORT == GPIO_PORTB)||(gpiopin->gpioPORT == GPIO_PORTC)))
	{
		RETURN_ERRORSTATUS=Status_enumParameterError;
	}
	else if(gpiopin->gpioPIN > 15)
	{
		RETURN_ERRORSTATUS=Status_enumParameterError;
	}
	//check on masks of modes
	else if (*gpioptr > 15)
	{
		RETURN_ERRORSTATUS=Status_enumParameterError;
	}
	else
	{
		gpioptr = (uint16_t*)&gpiopin->gpioSPEED;
	}
	if((*gpioptr < 16)&&(*gpioptr >19))
	{
		RETURN_ERRORSTATUS=Status_enumParameterError;
	}
	else
	{
		RETURN_ERRORSTATUS=Status_enumOk;
		gpioptr++;

		localmask = ((GPIO_t*)gpiopin->gpioPORT)->OSPEEDR;
		localmask &= ~ (GPIO_GETMODE << (gpiopin->gpioPIN *SHIFTMASK ) );
		localmask |= ( (GPIO_GETMODE&(uint32_t)(*gpioptr)) << (gpiopin->gpioPIN *SHIFTMASK ) );
		((GPIO_t*)gpiopin->gpioPORT)->OSPEEDR |= localmask;

		gpioptr = (uint16_t*)&gpiopin->gpioMODE ;
		gpioptr++;
		localmask = ((GPIO_t*)gpiopin->gpioPORT)->MODER;
		localmask &=~ (GPIO_GETMODE << (gpiopin->gpioPIN *SHIFTMASK ) );
		localmask |= ( (GPIO_GETMODE&(uint32_t)(*gpioptr)) << (gpiopin->gpioPIN *SHIFTMASK ) );
		((GPIO_t*)gpiopin->gpioPORT)->MODER |= localmask;

		(*gpioptr)>>=SHIFTMASK;
		localmask = ((GPIO_t*)gpiopin->gpioPORT)->PUPDR;
		localmask &=~ ( GPIO_GETMODE << (gpiopin->gpioPIN *SHIFTMASK ) );
		localmask |= ((GPIO_GETMODE&(uint32_t)(*gpioptr))<<(gpiopin->gpioPIN *SHIFTMASK) );
		((GPIO_t*)gpiopin->gpioPORT)->PUPDR |= localmask;

		(*gpioptr)>>=SHIFTMASK;
		if (BIT_0_MASK&(uint32_t)(*gpioptr))
		{
			((GPIO_t*)gpiopin->gpioPORT)->OTYPER |=( (BIT_0_MASK&(uint32_t)(*gpioptr))<<(gpiopin->gpioPIN ) );
		}
		else
		{
			((GPIO_t*)gpiopin->gpioPORT)->OTYPER &= ~( (BIT_0_MASK&(uint32_t)(*gpioptr))<<(gpiopin->gpioPIN ) );

		}
	}
	return RETURN_ERRORSTATUS;
}


Error_enumStatus_t GPIO_SetPinValue(void* PORT , uint32_t gpio_pinNumber , uint32_t gpiopinStatus)
{
	Error_enumStatus_t RETURN_ERRORSTATUS=Status_enumNotOk;
	if (PORT == NULL)
	{
		RETURN_ERRORSTATUS=Status_enumNULLPointer ;
	}
	else if( !((PORT == GPIO_PORTA)||(PORT == GPIO_PORTB)||(PORT == GPIO_PORTC)))
	{
		RETURN_ERRORSTATUS=Status_enumParameterError;
	}
	else if(gpio_pinNumber > 15)
	{
		RETURN_ERRORSTATUS=Status_enumParameterError;
	}
	else if(gpiopinStatus > LOGIC_HIGH)
	{
		RETURN_ERRORSTATUS=Status_enumParameterError;
	}
	else
	{
		RETURN_ERRORSTATUS=Status_enumOk;
		if (BIT_0_MASK&gpiopinStatus)
		{
			((GPIO_t*)PORT)->BSRR |= (BIT_0_MASK << gpio_pinNumber) ;
		}
		else
		{
			((GPIO_t*)PORT)->BSRR |= (BIT_0_MASK << (gpio_pinNumber+BSRR_SHIFTMASK) ) ;
		}
	}
	return RETURN_ERRORSTATUS;
}

Error_enumStatus_t GPIO_GetPinValue(void* PORT , uint32_t gpio_pinNumber , uint32_t* gpiopinStatus)
{
	Error_enumStatus_t RETURN_ERRORSTATUS=Status_enumNotOk;
	if (PORT == NULL)
	{
		RETURN_ERRORSTATUS=Status_enumNULLPointer ;
	}
	else if( !((PORT == GPIO_PORTA)||(PORT == GPIO_PORTB)||(PORT == GPIO_PORTC)))
	{
		RETURN_ERRORSTATUS=Status_enumParameterError;
	}
	else if(gpio_pinNumber > 15)
	{
		RETURN_ERRORSTATUS=Status_enumParameterError;
	}
	else if(gpiopinStatus == NULL )
	{
		RETURN_ERRORSTATUS=Status_enumParameterError;
	}
	else
	{
		RETURN_ERRORSTATUS=Status_enumOk;
		if ( ( (BIT_0_MASK << (gpio_pinNumber*2) ) & ( ( (GPIO_t*)PORT )->MODER) )&& (!((BIT_1_MASK << (gpio_pinNumber*2) ) & ( ( (GPIO_t*)PORT )->MODER))) ) //check if the pin is configuered input or output
		{
			* gpiopinStatus = (((GPIO_t*)PORT)->ODR& (1<<gpio_pinNumber));
		}
		else
		{
			* gpiopinStatus = (((GPIO_t*)PORT)->IDR& (1<<gpio_pinNumber));
		}
	}
	return RETURN_ERRORSTATUS;
}













