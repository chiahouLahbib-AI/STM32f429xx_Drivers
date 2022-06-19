

/******************************************************************************************/
/*																	0. Header																							*/
/******************************************************************************************/

#include "stm32f429xx.h"
#include "HAL_RCC.h"
#include "stdint.h"



/******************************************************************************************/
/*																	1. Global Macros	  																	*/
/******************************************************************************************/

#define PLL_M    2
#define PLL_N    180
#define PLL_P    0    /*PLLP = 2*/


/******************************************************************************************/
/*																	2. Prototype LOCAL FUNCTION														*/
/******************************************************************************************/


/*API to change toe frequency*/
static void RCC_SetTo72MZ(void);

/******************************************************************************************/
/*																	3. FUNCTIONS																					*/
/******************************************************************************************/


/******************************************************************************************/
/**		*@brief 	RCC Config																																*/
/**		*@param 	*RCC_Typedef : Rcc Base Address																						*/
/**		*@param		*RCC_Config :	Pointer to the configuration struct send by appli						*/
/**		*@retval	None																																			*/
/******************************************************************************************/


void SysClockConfig(void )
{
 /* Turn on HSE and wait to become ready*/	
	RCC->CR  |= RCC_CR_HSEON;
	while(!(RCC->CR & RCC_CR_HSERDY));
	
	/* Set the power enable clock and voltage regulator*/
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	PWR->CR |= PWR_CR_VOS;
	
	/*Configure the FLASH PREFETCH and the LATENCY related settings*/
	FLASH->ACR |= FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_5WS;
	
	/* Configure the prescaler HCLK, PCLK, PCLK2*/
	/*AHB PSCLR*/
	/*RCC_CFGR_HPRE_DIV1 = 0 (SYSCLK divided by 0x01)*/
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
	
	/*APB1 PSCLR*/
	/*!< HCLK divided by 2  */
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
	
	/*APB2 PSCLR*/
	/*!< HCLK not divided   */
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;
	
	/* Configure the main PLL */
	//RCC->PLLCFGR  |=  (PLL_M << 0) | (PLL_N << 6) | (PLL_P << 16 ) | (RCC_PLLCFGR_PLLSRC_HSE);
	RCC_SetTo72MZ();

	/* Enable PLL ad wait to become stable*/
	RCC->CR |= RCC_CR_PLLON;
	
	while(!(RCC->CR & RCC_CR_PLLRDY));
	
	/*Set clock source and wait it to be set */
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	
	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
	
}



static void RCC_SetTo72MZ(void)
{
	/*RCC PLL configuration register (RCC_PLLCFGR)*/

	/*PLLM*/
	RCC->PLLCFGR &=~(uint32_t)(0x3F<<0);
	RCC->PLLCFGR |=(uint32_t)(1U<<2);

	/*PLLN*/
	RCC->PLLCFGR &=~(uint32_t)(0x1FF<<6);
	RCC->PLLCFGR |=(uint32_t)(1U<<10);
	RCC->PLLCFGR |=(uint32_t)(1U<<13);
	
	/*PLLP*/
	RCC->PLLCFGR &=~(uint32_t)(3U<<16);

	/*PLLSRC*/
	RCC->PLLCFGR |=(uint32_t)(1U<<22);

	

}


