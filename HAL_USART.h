
#ifndef HAL_USART
#define HAL_USART

/* MC specific header file for stm32f429ZITx based Discovery board  */

#include "stm32f429xx.h"
#include <stdint.h>

/*Define Macros*/
/***************************************************************/
/*									1. Global Macros									 				 */
/***************************************************************/
/**@Brief : Macros for USART RCC Enable.
 */

#define _HAL_RCC_USART1_CLK_ENABLE()							(RCC->APB2ENR |= (1UL << 4))
#define _HAL_RCC_USART2_CLK_ENABLE()							(RCC->APB1ENR |= (1UL << 17))
#define _HAL_RCC_USART3_CLK_ENABLE()							(RCC->APB1ENR |= (1UL << 18))
#define _HAL_RCC_UART4_CLK_ENABLE()								(RCC->APB1ENR |= (1UL << 19))
#define _HAL_RCC_UART5_CLK_ENABLE()								(RCC->APB1ENR |= (1UL << 20))
#define _HAL_RCC_USART6_CLK_ENABLE()							(RCC->APB2ENR |= (1UL << 5))
#define _HAL_RCC_UART7_CLK_ENABLE()								(RCC->APB1ENR |= (1UL << 30))
#define _HAL_RCC_UART8_CLK_ENABLE()								(RCC->APB1ENR |= (1UL << 31))

/**@Brief : Macros for USART SR.
 */
#define SR_PARITY_ERROR()													(USART->SR |=(1UL << 0))
#define SR_FRAMING_ERROR()												(USART->SR |=(1UL << 1))
#define SR_NOISE_DETECTED_FLAG()									(USART->SR |=(1UL << 2))
#define SR_OVERRUN_ERROR()												(USART->SR |=(1UL << 3))
#define SR_RXNE																		(USART->SR |=(1UL << 4))
#define SR_TRANSMISSION_COMPLETE()								(USART->SR |=(1UL << 5))
#define SR_TX()																		(USART->SR |=(1UL << 6))
#define SR_LIN_BREAK_DETECTED()										(USART->SR |=(1UL << 7))
#define SR_CTS_CHANGED()													(USART->SR |=(1UL << 8))
#define SR_IDLE_LINE_DETECTED()										(USART->SR |=(1UL << 9))


/**@Brief : Macros for USART CR1.
 */
#define CR1_SEND_BREAK														((uint32_t)0x01)
#define CR1_SEND_NO_BREAK													((uint32_t)0x00)

#define CR1_RECEIVER_WAKEUP_MUTE_MODE							((uint32_t)0x01)
#define CR1_RECEIVER_WAKEUP_ACTIVE_MODE           ((uint32_t)0x00)

#define CR1_RECEIVER_ENABLED				              ((uint32_t)0x01)
#define CR1_RECEIVER_DISABLED					            ((uint32_t)0x00)

#define CR1_TRANSMITTER_ENABLED									  ((uint32_t)0x01)
#define CR1_TRANSMITTER_DISABLED								  ((uint32_t)0x00)

#define CR1_IDLE_INTERRUPT_ENABLED                ((uint32_t)0x01)
#define CR1_IDLE_INTERRUPT_INHIBITED              ((uint32_t)0x00)

#define CR1_RXNE_INTERRUPT_ENABLED	 						  ((uint32_t)0x01)
#define CR1_RXNE_INTERRUPT_INHIBITED						  ((uint32_t)0x00)

#define CR1_TCIE_ENABLED				 							    ((uint32_t)0x01)
#define CR1_TCIE_INHIBITED			 								  ((uint32_t)0x00)

#define CR1_TXEIE_ENABLED		   									  ((uint32_t)0x01)
#define CR1_TXEIE_INHIBITED			 								  ((uint32_t)0x00)

#define CR1_PEIE_ENABLED    										  ((uint32_t)0x01)
#define CR1_PEIE_INHIBITED			 								  ((uint32_t)0x00)

#define CR1_ODD_PARITY_SELECTION	                ((uint32_t)0x01)
#define CR1_EVEN_PARITY_SELECTION								  ((uint32_t)0x00)

#define CR1_PARITY_CONTROL_ENABLED		  				  ((uint32_t)0x01)
#define CR1_PARITY_CONTROL_DISABLED		  				  ((uint32_t)0x00)

#define CR1_WAKEUP_METHOD_ADDRESS_MARK            ((uint32_t)0x01)
#define CR1_WAKEUP_METHOD_IDLE_LINE		            ((uint32_t)0x00)

#define CR1_WORD_LENGTH_9BITS								      ((uint32_t)0x01)
#define CR1_WORD_LENGTH_8BITS								      ((uint32_t)0x00)

#define CR1_USART_ENABLED										      ((uint32_t)0x01)
#define CR1_USART_DISABLED									      ((uint32_t)0x00)

#define CR1_OVERSAMPLING_BY_8                     ((uint32_t)0x01)
#define CR1_OVERSAMPLING_BY_16                    ((uint32_t)0x00)


/**@Brief : Struct for Timer Paramters
 */
typedef struct
	{
		
		uint16_t Data_u16;
		uint16_t BaudRate_u16;
		uint8_t Send_break_u8;															
		uint8_t Receiver_wakeup_u8 ;
		uint8_t Receiver_state_u8	;			  
		uint8_t Transmitter_state_u8 ;				
		uint8_t Idle_interrupt_state_u8 ;
		uint8_t Rxne_interrupt_state_u8 ;
		uint8_t Tcie_state_u8 ;				 			
		uint8_t Txeie_state_u8	;	   				
		uint8_t Peie_state_u8    ;					
		uint8_t Parity_selection_u8	;
		uint8_t Parity_control_u8 ;		
		uint8_t Wakeup_method_u8 ;
		uint8_t Word_length_u8 ;
		uint8_t Usart_status_u8 ;						
		uint8_t Oversampling_u8 ;
		
	}Usart_Cfg_t;

/***************************************************************/
/*									2. Global functions								 				 */
/***************************************************************/
void USART_Cfg(USART_TypeDef *Usart, Usart_Cfg_t *Usart_Cfg);
void USART_Text_Write( USART_TypeDef *Usart,char *text);
char USART2_Write(char texts);
char USART_Write (USART_TypeDef *Usart,char ch);
void Enable_USARTIT(USART_TypeDef *Usart);	
#endif /*HAL_USART*/