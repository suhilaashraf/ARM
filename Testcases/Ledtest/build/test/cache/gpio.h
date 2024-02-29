#include "src/Error.h"
#include "src/Mask.h"










typedef struct

{

 void * gpioPORT;

 uint32_t gpioPIN;

 uint32_t gpioMODE;

 uint32_t gpioSPEED;

}GPIOPIN_t;





Error_enumStatus_t GPIO_InitPin(GPIOPIN_t* gpiopin);



Error_enumStatus_t GPIO_SetPinValue(void* PORT , uint32_t gpio_pinNumber , uint32_t gpiopinStatus);



Error_enumStatus_t GPIO_GetPinValue(void* PORT , uint32_t gpio_pinNumber , uint32_t* gpiopinStatus);
