
#ifndef __HAL_GPIO_DRIVER
#define __HAL_GPIO_DRIVER

/* MC specific header file for stm32f429ZITx based Discovery board  */

#include "stm32f429xx.h"
#include <stdint.h>

/* Pin State */
#define HIGH				((uint32_t)0x01)						
#define LOW 				((uint32_t)0x00)						


/* GPIO pin number*/
#define GPIO_PORT_A 										GPIOA
#define GPIO_PORT_B 										GPIOB
#define GPIO_PORT_C 										GPIOC
#define GPIO_PORT_D 										GPIOD
#define GPIO_PORT_E 										GPIOE
#define GPIO_PORT_F 										GPIOF
#define GPIO_PORT_G 										GPIOG
#define GPIO_PORT_H 										GPIOH

/***************************************************************/
/* 								Macros for enabling RCC peripherls					 */
/***************************************************************/
											/*GPIOx Enabling Clock */
#define _HAL_RCC_GPIOA_CLK_ENABLE() 		(RCC->AHB1ENR |= (1<<0) )
#define _HAL_RCC_GPIOB_CLK_ENABLE() 		(RCC->AHB1ENR |= (1<<1) )
#define _HAL_RCC_GPIOC_CLK_ENABLE() 		(RCC->AHB1ENR |= (1<<2) )
#define _HAL_RCC_GPIOD_CLK_ENABLE() 		(RCC->AHB1ENR |= (1<<3) )
#define _HAL_RCC_GPIOE_CLK_ENABLE() 		(RCC->AHB1ENR |= (1<<4) )
#define _HAL_RCC_GPIOF_CLK_ENABLE() 		(RCC->AHB1ENR |= (1<<5) )
#define _HAL_RCC_GPIOG_CLK_ENABLE() 		(RCC->AHB1ENR |= (1<<6) )
#define _HAL_RCC_GPIOH_CLK_ENABLE() 		(RCC->AHB1ENR |= (1<<7) )

#define _HAL_RCC_SPI2_CLK_ENABLE()			(RCC->APB1ENR |= (1<<14) )
#define _HAL_RCC_SPI3_CLK_ENABLE()      (RCC->APB1ENR |= (1<<15) )

#define _HAL_RCC_TIM2_CLK_ENABLE()      (RCC->APB1ENR |= (1<<0) )
#define _HAL_RCC_TIM4_CLK_ENABLE()      (RCC->APB1ENR |= (1<<2) )






/* GPIO port mode */
#define GPIO_INPUT_MODE									((uint32_t)0x00)
#define GPIO_OUTPUT_MODE								((uint32_t)0x01)
#define GPIO_ALTERN_MODE								((uint32_t)0x02)
#define GPIO_ANALOG_MODE								((uint32_t)0x03)

/* GPIO port output type */
#define GPIO_PUSH_PULL_OUTPUT						((uint32_t)0x00)
#define GPIO_OPEN_DRAIN_OUTPUT					((uint32_t)0x01)

/* GPIO port speed */
#define GPIO_LOW_SPPED									((uint32_t)0x00)
#define GPIO_MEDIUM_SPPED								((uint32_t)0x01)
#define GPIO_HIGH_SPPED									((uint32_t)0x02)
#define GPIO_VERY_HIGH_SPPED						((uint32_t)0x03)

/* GPIO port pull-up/pull-down register */
#define GPIO_NO_PULL										((uint32_t)0x00)
#define GPIO_PULL_UP										((uint32_t)0x01)
#define GPIO_PULL_DOWN									((uint32_t)0x02)
#define GPIO_RESERVED										((uint32_t)0x03)

/* alternate function */
#define ALTER_FUNC_SYSTEM										((uint32_t)0x00)
#define ALTER_FUNC_TIM1											((uint32_t)0x01)
#define ALTER_FUNC_TIM2	  									((uint32_t)0x01)
#define ALTER_FUNC_TIM3   									((uint32_t)0x02)
#define ALTER_FUNC_TIM4   									((uint32_t)0x02)
#define ALTER_FUNC_TIM5   									((uint32_t)0x02)
#define ALTER_FUNC_TIM8   									((uint32_t)0x03)
#define ALTER_FUNC_TIM9   									((uint32_t)0x03)
#define ALTER_FUNC_TIM10  									((uint32_t)0x03)
#define ALTER_FUNC_TIM11  									((uint32_t)0x03)
#define ALTER_FUNC_I2C1   									((uint32_t)0x04)
#define ALTER_FUNC_I2C2   									((uint32_t)0x04)
#define ALTER_FUNC_I2C3   									((uint32_t)0x04)
#define ALTER_FUNC_SPI1_AF5   							((uint32_t)0x05)
#define ALTER_FUNC_SPI2_AF5   							((uint32_t)0x05)
#define ALTER_FUNC_SPI3   									((uint32_t)0x05)
#define ALTER_FUNC_SPI4   									((uint32_t)0x05)
#define ALTER_FUNC_SPI5   									((uint32_t)0x05)
#define ALTER_FUNC_SPI6   									((uint32_t)0x05)
#define ALTER_FUNC_SPI2_AF6   							((uint32_t)0x06)
#define ALTER_FUNC_SPI3_AF6  								((uint32_t)0x06)
#define ALTER_FUNC_SAI1	  									((uint32_t)0x06)
#define ALTER_FUNC_USART1 									((uint32_t)0x07)
#define ALTER_FUNC_USART2 									((uint32_t)0x07)
#define ALTER_FUNC_USART3 									((uint32_t)0x07)
#define ALTER_FUNC_USART4 									((uint32_t)0x08)
#define ALTER_FUNC_USART5 									((uint32_t)0x08)
#define ALTER_FUNC_USART6 									((uint32_t)0x08)
#define ALTER_FUNC_USART7 									((uint32_t)0x08)
#define ALTER_FUNC_USART8 									((uint32_t)0x08)
#define ALTER_FUNC_CAN1   									((uint32_t)0x09)
#define ALTER_FUNC_CAN2   									((uint32_t)0x09)
#define ALTER_FUNC_LTDC   									((uint32_t)0x09)
#define ALTER_FUNC_TIM12  									((uint32_t)0x09)
#define ALTER_FUNC_TIM13  									((uint32_t)0x09)
#define ALTER_FUNC_TIM14  									((uint32_t)0x09)
#define ALTER_FUNC_OTG_FS 									((uint32_t)0x0A)
#define ALTER_FUNC_OTG_HS 									((uint32_t)0x0A)
#define ALTER_FUNC_ETH    									((uint32_t)0x0B)
#define ALTER_FUNC_FSMC   									((uint32_t)0x0C)
#define ALTER_FUNC_SDIO   									((uint32_t)0x0C)
#define ALTER_FUNC_DCMI   									((uint32_t)0x0D)
#define ALTER_FUNCT_LTDC   									((uint32_t)0x0E)
#define ALTER_FUNC_EVEN_OUT 								((uint32_t)0x0F)

/* Rising trigger selection */
#define RISING_TRIGGER_DISABLED							((uint32_t)0x00)	
#define RISING_TRIGGER_ENABLED							((uint32_t)0x01)

/* Falling trigger selection */
#define FALLING_TRIGGER_DISABLED						((uint32_t)0x00)	
#define FALLING_TRIGGER_ENABLED							((uint32_t)0x01)



/* External interrupt/event controller */
typedef enum
{
	INTERRUPT_EXTI = 0U,
	EVENT_EXTI
}IRQn_Type_t;

typedef enum
{
	RISING_EDGE_EXTI = 0U,
	FALLING_EDGE_EXTI,
	RISING_AND_FALLING_EDGE
}TypeDef_TriggerEvent_t;


 


/* Configuration GPIO pin */
typedef struct
{
	uint8_t Pin;
	
	uint32_t Mode;
	
	uint32_t OType;
	
	uint32_t OSpeed;
	
	uint32_t Pull;
	
	uint32_t AFR;
	
}GPIO_Pin_Config_t;

/******************************************************************************************/
/*																																												*/
/*																	HAL_GPIO_CONFIG																				*/
/*																																												*/
/******************************************************************************************/
/******************************************************************************************/
/**		*@brief 	Initialize GPIO Pins 																											*/
/**		*@param 	*GPIOx : GPIO Port adress base																						*/
/**		*@param		*GPIO_Pin_Config : Pointer to the pin configuration struct send by appli	*/
/**		*@retval	None																																			*/
/******************************************************************************************/
void HAL_GPIO_Config(GPIO_TypeDef *GPIOx , GPIO_Pin_Config_t *GPIO_Pin_Config);


/******************************************************************************************/
/**		*@brief 	GPIO Read value from pin 					  																			*/
/**		*@param 	*GPIOx : GPIO Port adress base																						*/
/**		*@param		GPIO_Pin : number of GPIOx Pin																						*/
/**		*@retval	None																																			*/
/******************************************************************************************/
void HAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx , uint8_t GPIO_Pin);


/******************************************************************************************/
/**		*@brief 	GPIO Write value to a pin 				  																			*/
/**		*@param 	*GPIOx : GPIO Port adress base																						*/
/**		*@param		GPIO_Pin : number of GPIOx Pin																						*/
/**		*@param		GValue : value between 0 and 1 																						*/
/**		*@retval	None																																			*/
/******************************************************************************************/
void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx , uint32_t GPIO_Pin , uint8_t Value);


/******************************************************************************************/
/**		*@brief 	GPIO Toggle value to a pin 				  																			*/
/**		*@param 	*GPIOx : GPIO Port adress base																						*/
/**		*@param		GPIO_Pin : number of GPIOx Pin																						*/
/**		*@retval	None																																			*/
/******************************************************************************************/
void HAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx , uint32_t GPIO_Pin);


/******************************************************************************************/
/**		*@brief 	GPIO Toggle value to a pin 				  																			*/
/**		*@param 	*GPIOx : GPIO Port adress base																						*/
/**		*@param		GPIO_Pin : number of GPIOx Pin																						*/
/**		*@param		AlterFunValue : alternate function value																	*/
/**		*@retval	None																																			*/
/******************************************************************************************/
void HAL_GPIO_AlterFunc(GPIO_TypeDef *GPIOx , uint8_t GPIO_Pin , uint8_t AlterFunValue);


/******************************************************************************************/
/**		*@brief 	GPIO Pin Interrupt Config 				  																			*/
/**		*@param 	GPIO_Pin : GPIO Port adress base																					*/
/**		*@param		TriggerEvent : Falling , Rising orr both																	*/
/**		*@retval	None																																			*/
/******************************************************************************************/
void HAL_GPIO_Interrupt_Config(uint16_t GPIO_Pin_Number , TypeDef_TriggerEvent_t TriggerEvent );


/******************************************************************************************/
/**		*@brief 	GPIO Pin Interrupt enable 				  																			*/
/**		*@param 	GPIO_Pin : GPIO Port adress base																					*/
/**		*@param		Irqn_No : Choose which EXTIx																							*/
/**		*@retval	None																																			*/
/******************************************************************************************/
void HAL_GPIO_Interrupt_Enable(uint16_t GPIO_Pin_Number , IRQn_Type_t IRQnType , uint8_t IRQN_NO );


/******************************************************************************************/
/**		*@brief 	GPIO Pin Interrupt Clear	 				  																			*/
/**		*@param 	GPIO_Pin : GPIO Port adress base																					*/
/**		*@param		Irqn_No : Choose which EXTIx																							*/
/**		*@retval	None																																			*/
/******************************************************************************************/
void HAL_GPIO_Interrupt_Clear(uint16_t GPIO_Pin_Number );





#endif  /* __HAL GPIO Drivers */





