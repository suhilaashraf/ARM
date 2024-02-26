#ifndef RCC_H
#define RCC_H

#include "Mask.h"
#include "std_types.h"


/*********BUSES PRESCALER****************/
#define PrescalerAHB_2 0x00000080
#define PrescalerAHB_4 0x00000090
#define PrescalerAHB_8 0x000000A0
#define PrescalerAHB_16 0x000000B0
#define PrescalerAHB_64 0x000000C0
#define PrescalerAHB_128 0x000000D0
#define PrescalerAHB_256 0x000000E0
#define PrescalerAHB_512 0x000000F0 // acts as a mask

#define PrescalerAPB1_2 0x00001000
#define PrescalerAPB1_4 0x00001400
#define PrescalerAPB1_8 0x00001800
#define PrescalerAPB1_16 0x00001C00 //acts as a mask

#define PrescalerAPB2_2 0x00008000
#define PrescalerAPB2_4 0x0000A000
#define PrescalerAPB2_8 0x0000C000
#define PrescalerAPB2_16 0x0000E000 //acts as a mask




//***************PERIPHERALS****************//
#define GPIOA BIT_0_MASK
#define GPIOB BIT_1_MASK
#define GPIOC BIT_2_MASK
#define GPIOD BIT_3_MASK
#define GPIOE BIT_4_MASK
#define GPIOH BIT_7_MASK
#define CRC BIT_12_MASK
#define DMA1 BIT_21_MASK
#define DMA2 BIT_22_MASK
#define USB BIT_7_MASK
#define TIM2 BIT_0_MASK
#define TIM3 BIT_1_MASK
#define TIM4 BIT_2_MASK
#define TIM5 BIT_3_MASK
#define WWDG BIT_11_MASK
#define SPI2 BIT_14_MASK
#define SPI3 BIT_15_MASK
#define USART2 BIT_17_MASK
#define I2C1 BIT_21_MASK
#define I2C2 BIT_22_MASK
#define I2C3 BIT_23_MASK
#define PWR BIT_28_MASK
#define TIM1 BIT_0_MASK
#define USART1 BIT_4_MASK
#define USART6 BIT_5_MASK
#define ADC1 BIT_8_MASK
#define SDIO BIT_11_MASK
#define SPI1 BIT_12_MASK
#define SPI4 BIT_13_MASK
#define SYSCFG BIT_14_MASK
#define TIM9 BIT_16_MASK
#define TIM10 BIT_17_MASK
#define TIM11 BIT_18_MASK




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
/*
typedef enum
{
	CLKPRE_2=0x,
	CLKPRE_4=4,
	CLKPRE_8=8,
	CLKPRE_16=16,
	CLKPRE_64=64,
	CLKPRE_128=128,
	CLKPRE_256=256,
	CLKPRE_512=512,
}RCCBUSES_PRE_enu;*/

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
