

/******************************************************************************************/
/*																	0. Header																							*/
/******************************************************************************************/

#include "stm32f429xx.h"
#include "HAL_USART.h"
#include "stdint.h"



/******************************************************************************************/
/*																	1. Global Macros	  																	*/
/******************************************************************************************/

/******************************************************************************************/
/*																	2. Prototype LOCAL FUNCTION														*/
/******************************************************************************************/




/******************************************************************************************/
/*																	3. FUNCTIONS																					*/
/******************************************************************************************/


/******************************************************************************************/
/**		*@brief 	Usart Config																															*/
/**		*@param 	*USART_Typedef : usart Base Address																				*/
/**		*@param		*Usart_Config :	Pointer to the configuration struct send by appli					*/
/**		*@retval	None																																			*/
/******************************************************************************************/

void USART_Cfg(USART_TypeDef *Usart, Usart_Cfg_t *Usart_Cfg)
{
	/*Usart Config*/
	
	
	/*Clear Usart*/
	Usart->CR1 = 0x00;
	/*Send Break*/
	if(Usart_Cfg->Send_break_u8)
	{
		Usart->CR1 |= (uint32_t)(1UL << 0);
	}else{
		Usart->CR1 &=~(uint32_t)(1UL << 0);
	}	
	
	/*Receive WakeUp*/
	if(Usart_Cfg->Receiver_wakeup_u8)
	{
		Usart->CR1 |= (uint32_t)(1UL << 1);
	}else{
		Usart->CR1 &=~(uint32_t)(1UL << 1);
	}	

	/*Receiver Enable*/
	if(Usart_Cfg->Receiver_state_u8)
	{
		Usart->CR1 |= (uint32_t)(1UL << 2);
	}else{
		Usart->CR1 &=~(uint32_t)(1UL << 2);
	}	
	
	/*Transmitter Enable*/
	if(Usart_Cfg->Transmitter_state_u8)
	{
		Usart->CR1 |= (uint32_t)(1UL << 3);
	}else{
		Usart->CR1 &=~(uint32_t)(1UL << 3);
	}	
	
	/*IDLE Interrupt Enable*/
	if(Usart_Cfg->Idle_interrupt_state_u8)
	{
		Usart->CR1 |= (uint32_t)(1UL << 4);
	}else{
		Usart->CR1 &=~(uint32_t)(1UL << 4);
	}	
	
	/*RXNE interrupt enable*/
	if(Usart_Cfg->Rxne_interrupt_state_u8)
	{
		Usart->CR1 |= (uint32_t)(1UL << 5);
	}else{
		Usart->CR1 &=~(uint32_t)(1UL << 5);
	}	
	
	/*Transmission complete interrupt enable*/
	if(Usart_Cfg->Tcie_state_u8)
	{
		Usart->CR1 |= (uint32_t)(1UL << 6);
	}else{
		Usart->CR1 &=~(uint32_t)(1UL << 6);
	}	
	
	/*TXE interrupt enable*/
	if(Usart_Cfg->Txeie_state_u8)
	{
		Usart->CR1 |= (uint32_t)(1UL << 7);
	}else{
		Usart->CR1 &=~(uint32_t)(1UL << 7);
	}	
	
	/*PE interrupt enable*/
	if(Usart_Cfg->Peie_state_u8)
	{
		Usart->CR1 |= (uint32_t)(1UL << 8);
	}else{
		Usart->CR1 &=~(uint32_t)(1UL << 8);
	}	
	
	/*Parity selection*/
	if(Usart_Cfg)
	{
		Usart->CR1 |= (uint32_t)(1UL << 9);
	}else{
		Usart->CR1 &=~(uint32_t)(1UL << 9);
	}	
	
	/*Parity control enable*/
	if(Usart_Cfg->Parity_control_u8)
	{
		Usart->CR1 |= (uint32_t)(1UL << 10);
	}else{
		Usart->CR1 &=~(uint32_t)(1UL << 10);
	}	
	
	/*Wakeup method*/
	if(Usart_Cfg->Wakeup_method_u8)
	{
		Usart->CR1 |= (uint32_t)(1UL << 11);
	}else{
		Usart->CR1 &=~(uint32_t)(1UL << 11);
	}	
	
	/*Word length*/
	if(Usart_Cfg->Word_length_u8)
	{
		Usart->CR1 |= (uint32_t)(1UL << 12);
	}else{
		Usart->CR1 &=~(uint32_t)(1UL << 12);
	}	
	
	/*Enable USART*/
	if(Usart_Cfg->Usart_status_u8)
	{
		Usart->CR1 |= (uint32_t)(1UL << 13);
	}else{
		Usart->CR1 &=~(uint32_t)(1UL << 13);
	}	

	
	/*Oversampling mode*/
	if(Usart_Cfg->Oversampling_u8)
	{
		Usart->CR1 |= (uint32_t)(1UL << 14);
	}else{
		Usart->CR1 &=~(uint32_t)(1UL << 14);
	}	
	


	Usart->BRR = ((Usart_Cfg->BaudRate_u16)&(0x000F));
	Usart->BRR |= (((Usart_Cfg->BaudRate_u16)&(0xFFF0)))<<4U;
	


}

/******************************************************************************************/
/**		*@brief 	Enable_USARTIT																															*/
/**		*@param 	*USART_Typedef : usart Base Address																				*/
/**		*@param		*UsartIT_Config :	Pointer to the configuration struct send by application					*/
/**		*@retval	None																																			*/
/******************************************************************************************/
void Enable_USARTIT(USART_TypeDef *Usart)
{
	/*Enable TXEIE & TCIE bits*/
	Usart->CR1 |= (uint32_t)(0x3U<<6);

	/*Enable NVIC Interrupt  -- Found in stm32f429xx.h header file*/
	NVIC_EnableIRQ(USART1_IRQn);

}


char USART_Write (USART_TypeDef *Usart,char ch)
{
	while(!(Usart->SR & (1<<7))){}
		Usart-> DR = (ch & 0xFF);
		return ch;
	
}


void USART_Text_Write(USART_TypeDef *Usart,char *text)
{
	while(*text) USART_Write(Usart,*text++);
	
}