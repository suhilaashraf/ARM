#ifndef RCC_H
#define RCC_H

#include "Mask.h"
#include "std_types.h"


/*********BUSES PRESCALER****************/
#define PrescalerAHB_2 		0x00000080
#define PrescalerAHB_4 		0x00000090
#define PrescalerAHB_8 		0x000000A0
#define PrescalerAHB_16 	0x000000B0
#define PrescalerAHB_64 	0x000000C0
#define PrescalerAHB_128 	0x000000D0
#define PrescalerAHB_256 	0x000000E0
#define PrescalerAHB_512 	0x000000F0 // acts as a mask

#define PrescalerAPB1_2 	0x00001000
#define PrescalerAPB1_4 	0x00001400
#define PrescalerAPB1_8 	0x00001800
#define PrescalerAPB1_16 	0x00001C00 //acts as a mask

#define PrescalerAPB2_2 	0x00008000
#define PrescalerAPB2_4 	0x0000A000
#define PrescalerAPB2_8 	0x0000C000
#define PrescalerAPB2_16 	0x0000E000 //acts as a mask




//***************PERIPHERALS****************//
#define RCC_GPIOA 			BIT_0_MASK
#define RCC_GPIOB 			BIT_1_MASK
#define RCC_GPIOC 			BIT_2_MASK
#define RCC_GPIOD 			BIT_3_MASK
#define RCC_GPIOE 			BIT_4_MASK
#define RCC_GPIOH 			BIT_7_MASK
#define RCC_CRC 			BIT_12_MASK
#define RCC_DMA1 			BIT_21_MASK
#define RCC_DMA2 			BIT_22_MASK

#define RCC_USB 			BIT_7_MASK

#define RCC_TIM2 			BIT_0_MASK
#define RCC_TIM3 			BIT_1_MASK
#define RCC_TIM4 			BIT_2_MASK
#define RCC_TIM5 			BIT_3_MASK
#define RCC_WWDG 			BIT_11_MASK
#define RCC_SPI2 			BIT_14_MASK
#define RCC_SPI3 			BIT_15_MASK
#define RCC_USART2 			BIT_17_MASK
#define RCC_I2C1 			BIT_21_MASK
#define RCC_I2C2 			BIT_22_MASK
#define RCC_I2C3 			BIT_23_MASK
#define RCC_PWR 			BIT_28_MASK

#define RCC_TIM1 			BIT_0_MASK
#define RCC_USART1 			BIT_4_MASK
#define RCC_USART6 			BIT_5_MASK
#define RCC_ADC1 			BIT_8_MASK
#define RCC_SDIO 			BIT_11_MASK
#define RCC_SPI1 			BIT_12_MASK
#define RCC_SPI4 			BIT_13_MASK
#define RCC_SYSCFG 			BIT_14_MASK
#define RCC_TIM9 			BIT_16_MASK
#define RCC_TIM10 			BIT_17_MASK
#define RCC_TIM11 			BIT_18_MASK

/******SYSCLK OPTIONS *************/
typedef enum
{
	Sysclk_HSI=0x00000001,
	Sysclk_HSE=0x00010000,
	Sysclk_PLL=0x01000000,
}RCCSYSCLK_enu;

typedef enum
{
	SysclkDisable,
	SysclkEnable
}RCCState_enu;

/*******RCC ERROR CHECKS *************/
typedef enum
{
	RCC_enuOK,
	RCC_enuNOK,
	RCC_enuInvalidPeripheral,
	RCC_enuInvalidCLK,
	RCC_enuCLKNotRDY,
	RCC_enuCLKNotON,
	RCC_enuDisabledDenied, //disable denied due to direct or indirect disable to the system clock
	RCC_enuInvalidPRE, //invalid prescaler
	RCC_enuInvaildParameter
}RCCERRORCHECK_enu;
/*******BUS options ************/
typedef enum
{
	SysbusAHB1,
	SysbusAHB2,
	SysbusAPB1,
	SysbusAPB2
}RCCBUSES_enu;

/**********APIS*************/

/* ConfigPLL funtion: set PLL parameters (M , N , P , Q )
 * Caution:
 * the max clk freq is 84Mhz make sure not to exceed it
 * make sure not to exceed the parameters range
 * the M  range: [ 2 :63]
 * the N  range: [192 : 432]
 * the Q  range: [2:15]
 * the P  range: [ 2, 4, 6, or 8]
 * */
RCCERRORCHECK_enu ConfigPLL(uint16_t M ,uint16_t N,uint16_t Q,uint16_t P);


/*
 *RCCControlCLK FUNCTION: control CLK ON/OFF
 *Sysclk :(Sysclk_HSI/ Sysclk_HSE/ Sysclk_PLL)
 *caution: make sure when disable the required clk that it's not selected as system clock */
RCCERRORCHECK_enu RCCControlCLK(RCCSYSCLK_enu Sysclk ,RCCState_enu SysclkSTATE );

/*
 *RCCSelectCLK FUNCTION: select CLK from:(Sysclk_HSI/ Sysclk_HSE/ Sysclk_PLL) to be the system clock
 *caution: make sure to enable the clock and wait for it to get ready otherwise
 the clk won't be selected as sysclk  */
RCCERRORCHECK_enu RCCSelectCLK(RCCSYSCLK_enu Sysclk);



/*RCC_SelectPRESCALER Function: select bus prescaler
 * Prescaler options for APB1 ,APB2 :[2,4,8,16]
 * Prescaler options for AHB1 :[2,4,8,16,64,128,256,512]*/
RCCERRORCHECK_enu RCCSelectPRESCALER(RCCBUSES_enu Sysbus,uint16_t Prescaler);

/*RCCEnablePripheral Function: ENABLE
 *
*/

RCCERRORCHECK_enu RCCEnablePripheral(uint32_t Pripheral,RCCBUSES_enu Sysbus);




#endif
