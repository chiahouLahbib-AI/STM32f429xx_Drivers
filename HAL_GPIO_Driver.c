 
#include "HAL_GPIO_Driver.h"
#include "stm32f429xx.h"
#include <stdint.h>


/******************************************************************************************/
/*												1. Prototype LOCAL FUNCTION																			*/
/******************************************************************************************/
static void HAL_Config_Pin_Mode(GPIO_TypeDef *GPIOx, uint8_t GPIO_Pin , uint32_t Mode);
static void HAL_Config_Pin_OType(GPIO_TypeDef *GPIOx, uint8_t GPIO_Pin , uint32_t Output_Type);
static void HAL_Config_Pin_OSpeed(GPIO_TypeDef *GPIOx, uint8_t GPIO_Pin , uint32_t Speed);
static void HAL_Config_Pin_Pull(GPIO_TypeDef *GPIOx, uint8_t GPIO_Pin , uint32_t Pull);
static void HAL_Config_Pin_AlterFun(GPIO_TypeDef *GPIOx, uint8_t GPIO_Pin , uint32_t Pull); 









/******************************************************************************************/
/**		*@brief 	Initialize GPIO Pins 																											*/
/**		*@param 	*GPIOx : GPIO Port adress base																						*/
/**		*@param		*GPIO_Pin_Config : Pointer to the pin configuration struct send by appli	*/
/**		*@retval	None																																			*/
/******************************************************************************************/
void HAL_GPIO_Config(GPIO_TypeDef *GPIOx , GPIO_Pin_Config_t *GPIO_Pin_Config)
{
	/* 	1. Helper function to configure pin mode */
	HAL_Config_Pin_Mode(GPIOx,GPIO_Pin_Config->Pin ,GPIO_Pin_Config->Mode);
	/* 	2. Helper function to configure pin output type */
	HAL_Config_Pin_OType(GPIOx, GPIO_Pin_Config->Pin , GPIO_Pin_Config->OType);
	/* 	3. Helper function to configure pin output speed */
	HAL_Config_Pin_OSpeed(GPIOx, GPIO_Pin_Config->Pin , GPIO_Pin_Config->OSpeed);
	/* 	4. Helper function to configure pin pull */
	HAL_Config_Pin_Pull(GPIOx, GPIO_Pin_Config->Pin , GPIO_Pin_Config->Pull);
	/*	5. Helper function to configure AFR	*/
	HAL_Config_Pin_AlterFun(GPIOx, GPIO_Pin_Config->Pin , GPIO_Pin_Config->AFR);    
} 
  
 




/******************************************************************************************/
/*																	3. GLOBAL FUNCTION																			*/
/******************************************************************************************/



/******************************************************************************************/
/**		*@brief 	GPIO Read value from pin 					  																			*/
/**		*@param 	*GPIOx : GPIO Port adress base																						*/
/**		*@param		GPIO_Pin : number of GPIOx Pin																						*/
/**		*@retval	None																																			*/
/******************************************************************************************/
void HAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx , uint8_t GPIO_Pin)
{
	
}


/******************************************************************************************/
/**		*@brief 	GPIO Write value to a pin 				  																			*/
/**		*@param 	*GPIOx : GPIO Port adress base																						*/
/**		*@param		GPIO_Pin : number of GPIOx Pin																						*/
/**		*@param		GValue : value between 0 and 1 																						*/
/**		*@retval	None																																			*/
/******************************************************************************************/
void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx , uint32_t GPIO_Pin , uint8_t Value)
{
	if(Value)
	{
		GPIOx->ODR |= (1<<GPIO_Pin);
	}
	else
	{
		GPIOx->ODR &= ~(1<<GPIO_Pin);
	}
}


/******************************************************************************************/
/**		*@brief 	GPIO Toggle value to a pin 				  																			*/
/**		*@param 	*GPIOx : GPIO Port adress base																						*/
/**		*@param		GPIO_Pin : number of GPIOx Pin																						*/
/**		*@retval	None																																			*/
/******************************************************************************************/
void HAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx , uint32_t GPIO_Pin)
{
	GPIOx->ODR ^= (1<<GPIO_Pin);
}

/******************************************************************************************/
/*						GPIO pin Interrupt Routine Configuration*/
/******************************************************************************************/
/******************************************************************************************/
/**		*@brief 	GPIO Pin Interrupt Config 				  																			*/
/**		*@param 	GPIO_Pin : GPIO Port adress base																					*/
/**		*@param		TriggerEvent : Falling , Rising orr both																	*/
/**		*@retval	None																																			*/
/******************************************************************************************/
void HAL_GPIO_Interrupt_Config(uint16_t GPIO_Pin_Number , TypeDef_TriggerEvent_t TriggerEvent )
{
	if(TriggerEvent == RISING_EDGE_EXTI)
	{
		EXTI->RTSR |= (RISING_TRIGGER_ENABLED << GPIO_Pin_Number);
	}
	else if(TriggerEvent == FALLING_EDGE_EXTI)
	{
		EXTI->FTSR |= (FALLING_TRIGGER_ENABLED << GPIO_Pin_Number);
	}
	else if(TriggerEvent == RISING_AND_FALLING_EDGE)
	{
		EXTI->FTSR |= (FALLING_TRIGGER_ENABLED << GPIO_Pin_Number);
		EXTI->RTSR |= (RISING_TRIGGER_ENABLED << GPIO_Pin_Number);
	}
}


/******************************************************************************************/
/**		*@brief 	GPIO Pin Interrupt enable 				  																			*/
/**		*@param 	GPIO_Pin : GPIO Port adress base																					*/
/**		*@param		Irqn_No : Choose which EXTIx																							*/
/**		*@retval	None																																			*/
/******************************************************************************************/
void HAL_GPIO_Interrupt_Enable(uint16_t GPIO_Pin_Number , IRQn_Type_t IRQnType , uint8_t IRQN_NO )
{
	if(IRQnType == INTERRUPT_EXTI)
	{
		EXTI->IMR |= (1 << GPIO_Pin_Number);
	}
	else if(IRQnType == EVENT_EXTI)
	{
		EXTI->EMR |= (1 << GPIO_Pin_Number);
	}
	
	NVIC_EnableIRQ(IRQN_NO);
}

/******************************************************************************************/
/**		*@brief 	GPIO Pin Interrupt Clear	 				  																			*/
/**		*@param 	GPIO_Pin : GPIO Port adress base																					*/
/**		*@param		Irqn_No : Choose which EXTIx																							*/
/**		*@retval	None																																			*/
/******************************************************************************************/
void HAL_GPIO_Interrupt_Clear(uint16_t GPIO_Pin_Number )
{
	if((EXTI->PR)&(1 << GPIO_Pin_Number ))
	{
		EXTI->PR |= ( 1 << GPIO_Pin_Number);
	}
}





/******************************************************************************************/
/*																	1. LOCAL FUNCTION																			*/
/******************************************************************************************/
/******************************************************************************************/
/**		*@brief 	HAL_Config_Pin_Mode 																											*/
/**		*@param 	*GPIOx : GPIO Port adress base																						*/
/**		*@param		GPIO_Pin : Pin number																											*/
/**		*@param		Mode : Mode of gpio pin																										*/
/**		*@retval	None																																			*/
/******************************************************************************************/
static void HAL_Config_Pin_Mode(GPIO_TypeDef *GPIOx, uint8_t GPIO_Pin , uint32_t Mode)
{
	GPIOx->MODER |= (Mode << ( GPIO_Pin*2 ) );
}

/******************************************************************************************/
/**		*@brief 	HAL_Config_Pin_OType 																											*/
/**		*@param 	*GPIOx : GPIO Port adress base																						*/
/**		*@param		GPIO_Pin : Pin number																											*/
/**		*@param		Mode : Mode of gpio pin																										*/
/**		*@retval	None																																			*/
/******************************************************************************************/
static void HAL_Config_Pin_OType(GPIO_TypeDef *GPIOx, uint8_t GPIO_Pin , uint32_t OType)
{
	GPIOx->OTYPER |= (OType << ( GPIO_Pin ));
}

/******************************************************************************************/
/**		*@brief 	HAL_Config_Pin_OSpeed																											*/
/**		*@param 	*GPIOx : GPIO Port adress base																						*/
/**		*@param		*GPIO_Pin_Config : Pointer to the pin configuration struct send by appli	*/
/**		*@retval	None																																			*/
/******************************************************************************************/
static void HAL_Config_Pin_OSpeed(GPIO_TypeDef *GPIOx, uint8_t GPIO_Pin , uint32_t OSpeed)
{
	GPIOx->OSPEEDR |= (OSpeed << (GPIO_Pin*2) );
}

/******************************************************************************************/
/**		*@brief 	HAL_Config_Pin_Pull																												*/
/**		*@param 	*GPIOx : GPIO Port adress base																						*/
/**		*@param		*GPIO_Pin_Config : Pointer to the pin configuration struct send by appli	*/
/**		*@retval	None																																			*/
/******************************************************************************************/

static void HAL_Config_Pin_Pull(GPIO_TypeDef *GPIOx, uint8_t GPIO_Pin , uint32_t Pull)
{
	GPIOx->PUPDR |= (Pull << (GPIO_Pin*2));
}


/******************************************************************************************/
/**		*@brief 	HAL_Config_Pin_AlterFun																										*/
/**		*@param 	*GPIOx : GPIO Port adress base																						*/
/**		*@param		*GPIO_Pin_Config : Pointer to the pin configuration struct send by appli	*/
/**		*@retval	None																																			*/
/******************************************************************************************/
static void HAL_Config_Pin_AlterFun(GPIO_TypeDef *GPIOx, uint8_t GPIO_Pin , uint32_t AlternateFun	)
{
	if(GPIO_Pin<8)
	{
		GPIOx->AFR[0] |= (AlternateFun << (GPIO_Pin*4));
	}
	else
	{
		GPIOx->AFR[1] |= (AlternateFun << ((GPIO_Pin % 8)*4));
	}
	
}




