
#include "stm32f429xx.h"
#include <stdint.h>
#include "HAL_GPIO_Driver.h"
#include "HAL_TIM.h"
#include "HAL_USART.h"
#include "HAL_RCC.h"




volatile uint32_t myTicks ;
void delay_ms(uint16_t ms);
void Push_Button_Cfg(void);
void Leds_Cfg(void);
void Rcc_Cfg(void);
void Timer_Cfg(void);
void Usart1_Cfg(void);
void Usart2_Cfg(void);





	/* Globat Macros*/
	Tim_Cfg_t Tim4;
	GPIO_Pin_Config_t GpioA;
	Usart_Cfg_t Usart1;
	Usart_Cfg_t Usart2;
	/*End Global Macros*/
	char completed[] = " TC is complet\r\n";
	
int main(void)
{
	volatile int i = 0;
	
	
	SysClockConfig();
	
	
	/* Enable RCC */
	Rcc_Cfg();
	/* End RCC Config*/
	
	/* GPIO Pin Config : RED and GREEN LEDs on Pin PG13 and PG14  */
	Leds_Cfg();
	
	
	#if 1
	Usart2_Cfg();
	#endif
	Usart1_Cfg();


	/* Timer Configuration*/
	Timer_Cfg();
	
	/*Enable Interrupts*/
	NVIC_EnableIRQ(TIM4_IRQn);
	Enable_USARTIT(USART1);
	/*End Interrupts Configuration*/
	
	
	/* GPIOA Configuration  : Push Button when its clicked then we move to ISR Routine*/
	Push_Button_Cfg();
	char temp[] = "Welcome to Microcontrollers Lab\r\n";
	char temp2[] = "Send from terminal\r\n";
	
	
	/*infinte Loop*/
	while(1)
	{
	/* End User Code */

		
		USART_Text_Write(USART1,temp);
		delay_ms(100);
		HAL_GPIO_TogglePin(GPIOG,13);
		USART_Text_Write(USART1,temp);
		delay_ms(100);
		HAL_GPIO_TogglePin(GPIOG,13);
		USART_Text_Write(USART1,temp);
		delay_ms(500);
		
		



				
	}

}


void Rcc_Cfg(void)
{
	_HAL_RCC_GPIOA_CLK_ENABLE();
	_HAL_RCC_GPIOG_CLK_ENABLE();
	_HAL_RCC_TIM4_CLK_ENABLE();
	_HAL_RCC_USART1_CLK_ENABLE(); 
	_HAL_RCC_USART2_CLK_ENABLE(); 
}

void Timer_Cfg(void)
{
	
	Tim4.Prescaler_u8 = 0U;
	Tim4.Auto_Reload_Reg_u8 = 72U;
	Tim_Cfg(TIM4,&Tim4);

}

void Leds_Cfg(void)
{
	
	GPIO_Pin_Config_t LED;
	
	LED.Pin = 13;
	LED.Mode = GPIO_OUTPUT_MODE;
	LED.OSpeed = GPIO_VERY_HIGH_SPPED;
	LED.OType = GPIO_PUSH_PULL_OUTPUT;
	LED.Pull = GPIO_NO_PULL;
	HAL_GPIO_Config(GPIOG,&LED);
	LED.Pin = 14;
	HAL_GPIO_Config(GPIOG,&LED);
	LED.Pin = 9;
	HAL_GPIO_Config(GPIOG,&LED);
}

void Push_Button_Cfg(void)
{
	GPIO_Pin_Config_t PushButton;
	
	PushButton.Pin = 0;
	PushButton.Mode = GPIO_INPUT_MODE;
	PushButton.OSpeed = GPIO_HIGH_SPPED;
	PushButton.Pull = GPIO_NO_PULL;
	PushButton.OType = GPIO_PUSH_PULL_OUTPUT;
	HAL_GPIO_Config(GPIOA , &PushButton);
}


void Usart1_Cfg(void)
{
	GpioA.Pin = 9;
	GpioA.Mode = GPIO_ALTERN_MODE;
	GpioA.OType = GPIO_PUSH_PULL_OUTPUT;
	GpioA.Pull = GPIO_PULL_UP;
	GpioA.OSpeed = GPIO_VERY_HIGH_SPPED;
	GpioA.AFR = ALTER_FUNC_USART1;
	HAL_GPIO_Config(GPIOA, &GpioA);


	/*Pin 10*/
	GpioA.Pin = 10;
	GpioA.Mode = GPIO_ALTERN_MODE;
	GpioA.OType = GPIO_PUSH_PULL_OUTPUT;
	//GpioA.Pull = GPIO_PULL_UP;
	GpioA.OSpeed = GPIO_VERY_HIGH_SPPED;
	GpioA.AFR = ALTER_FUNC_USART2;
	HAL_GPIO_Config(GPIOA, &GpioA);
	/*
	Usart1.Usart_status_u8 = CR1_USART_ENABLED;
	Usart1.Transmitter_state_u8 = CR1_TRANSMITTER_ENABLED;
	Usart1.Receiver_state_u8 = CR1_RECEIVER_ENABLED;
	*/
	
	/*Enable USART */
	USART1->CR1 = 0x00;
	USART1->CR1 |= (1 << 13);
	/*Define the Word length*/
	USART1->CR1 &= ~(1 << 12);
	/*Bauderate*/
	USART1->BRR |=(uint32_t)(0x3A94)<<0; 

	/*Enable Tx and Rx*/
	USART1->CR1 |= (1 << 2);/*RE=1*/
	USART1->CR1 |= (1 << 3);/*TE=1*/

	
	
	
	
}


void Usart2_Cfg(void)
{
	/*Pin 2*/
	GpioA.Pin = 2;
	GpioA.Mode = GPIO_ALTERN_MODE;
	GpioA.OType = GPIO_PUSH_PULL_OUTPUT;
	GpioA.Pull = GPIO_PULL_UP;
	GpioA.OSpeed = GPIO_VERY_HIGH_SPPED;
	GpioA.AFR = ALTER_FUNC_USART2;
	HAL_GPIO_Config(GPIOA, &GpioA);
	
	
	
	/*Pin 3*/
	GpioA.Pin = 3;
	GpioA.Mode = GPIO_ALTERN_MODE;
	GpioA.OType = GPIO_PUSH_PULL_OUTPUT;
	//GpioA.Pull = GPIO_PULL_UP;
	GpioA.OSpeed = GPIO_VERY_HIGH_SPPED;
	GpioA.AFR = ALTER_FUNC_USART2;
	HAL_GPIO_Config(GPIOA, &GpioA);
	
	/*Enable USART */
	USART2->CR1 = 0x00;
	USART2->CR1 |= (1 << 13);
	/*Define the Word length*/
	USART2->CR1 &= ~(1 << 12);
	
	/*The bauderate*/
	USART2->BRR |=0x1D4C; 
	
	/*Enable Tx and Rx*/
	USART2->CR1 |= (1 << 2);/*RE=1*/
	USART2->CR1 |= (1 << 3);/*TE=1*/
	
	
	
	/*Usart*/
	/*
	Usart2.Usart_status_u8 = CR1_USART_ENABLED;
	Usart2.Transmitter_state_u8 = CR1_TRANSMITTER_ENABLED;
	Usart2.Receiver_state_u8 = CR1_RECEIVER_ENABLED;
	Usart2.BaudRate_u16 = 0x249E;
	USART_Cfg(USART2, &Usart2);
	*/
	
}


void delay_ms(uint16_t ms)
{
	TIM4->CR1 |= (1UL << 0);
	myTicks = 0UL;
	
	while(myTicks < ms * 1000U)
	{
	}
	
	TIM4->CR1 &=~ (1UL << 0);
}

void TIM4_IRQHandler(void)
{
	myTicks++;
	TIM4->SR &=~(1UL << 0);
}


void USART1_IRQHandler(void)
{
	#if 0
	/*Here because of data received*/
	if(USART1->SR & (1UL<<5))
		{
			char Data = USART1->DR;
			
			USART_Text_Write(USART1,&Data);
			HAL_GPIO_TogglePin(GPIOG,13);
			USART_Text_Write(USART1,completed);
			while (!(USART1->SR & USART_SR_TC))
			;
			
			
			/*Clear IT bit*/
			USART1->SR &=~(uint32_t)(3U << 5);
			
			
		}
	/*Send Msg "IT generate at TX complet"*/
	if(!(USART1->SR & USART_SR_TC))
	{
		//USART_Text_Write(USART1,completed);
	}
	
	/*Clear IT bit*/
	USART1->SR &=~(uint32_t)(3U << 5);
	#endif
}




