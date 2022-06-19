
#ifndef __HAL_SPI_DRIVER
#define __HAL_SPI_DRIVER

/* MC specific header file for stm32f429ZITx based Discovery board  */

#include "stm32f429xx.h"
#include <stdint.h>

											/* SPIx Enabling Clock */
#define _HAL_RCC_SPI1_CLK_ENABLE() 			(RCC->APB2ENR |= (1<<12) )
#define _HAL_RCC_SPI2_CLK_ENABLE() 			(RCC->APB1ENR |= (1<<14) )
#define _HAL_RCC_SPI3_CLK_ENABLE() 			(RCC->APB1ENR |= (1<<15) )


#define CLOCK_POLARITY_0 								 ((uint32_t)0x00 << 1)
#define CLOCK_POLARITY_1								 ((uint32_t)0x01 << 1)
#define CLOCK_PHASE_0										 ((uint32_t)0x00 << 0)
#define CLOCK_PHASE_1										 ((uint32_t)0x01 << 0)

#define SLAVE_CONFIGURATION 						 ((uint32_t)0x00 << 2)
#define MASTER_CONFIGURATION						 ((uint32_t)0x01 << 2)

#define BAUD_RATE_CONTROL_2							 ((uint32_t)(0x00 << 3))
#define BAUD_RATE_CONTROL_4							 ((uint32_t)(0x01 << 3))
#define BAUD_RATE_CONTROL_8							 ((uint32_t)(0x02 << 3))
#define BAUD_RATE_CONTROL_16						 ((uint32_t)(0x03 << 3))
#define BAUD_RATE_CONTROL_32						 ((uint32_t)(0x04 << 3))
#define BAUD_RATE_CONTROL_64						 ((uint32_t)(0x05 << 3))
#define BAUD_RATE_CONTROL_128						 ((uint32_t)(0x06 << 3))
#define BAUD_RATE_CONTROL_256						 ((uint32_t)(0x07 << 3))

#define SPI_DISABLED										 ((uint32_t) (0x00 << 6))
#define SPI_ENABLE                       ((uint32_t) (0x01 << 6))

#define MSB_TRANSMITTED_FIRST						 ((uint32_t) (0x00 << 7))
#define LSB_TRANSMITTED_FIRST						 ((uint32_t) (0x01 << 7))

#define SW_SLAVE_MANAGEMENT_DISABLED		 ((uint32_t) (0x00 << 9))
#define SW_SLAVE_MANAGEMENT_ENABLED      ((uint32_t) (0x01 << 9))
#define INTERNAL_SLAVE_SELECT							((uint32_t) (0x01 << 8))

#define RO_FULL_DUPLEX_MODE							 ((uint32_t) (0x00 << 10)) /* Receive Only */
#define RO_RECEIVE_ONLY_MODE             ((uint32_t) (0x01 << 10))

#define BI_RECEIVE_ONLY_MODE						 ((uint32_t) (0x00 << 14)) /* Bidirectionnal Only */
#define BI_TTRANSMIT_ONLY_MODE           ((uint32_t) (0x01 << 14))

#define DATA_FRAME_FORMAT_8_BIT					 ((uint32_t) (0x00 << 11))
#define DATA_FRAME_FORMAT_16_BIT				 ((uint32_t) (0x01 << 11))

#define SPI_8BIT_DF_ENABLE							 ((uint32_t) (0x08))

#define CRC_CALCULATION_DISABLED				 ((uint32_t) (0x00 << 13))
#define CRC_CALCULATION_ENABLED					 ((uint32_t) (0x01 << 13))

#define UNIDIRECTIONAL_DATA_MODE				 ((uint32_t) (0x00 << 15))
#define BIDIRECTIONAL_DATA_MODE					 ((uint32_t) (0x01 << 15))
	
	
	/*																		SPI control register 2 (SPI_CR2)													*/
#define TXE_INTERRUPT_MASKED						 ((uint32_t) (0x00 << 7))
#define TXE_NOT_INTERRUPT_MASKED				 ((uint32_t) (0x01 << 7))

#define RXNE_INTERRUPT_MASKED						 ((uint32_t) (0x00 << 6))
#define RXNE_NOT_INTERRUPT_MASKED				 ((uint32_t) (0x01 << 6))

#define ERROR_INTERRUPT_MASKED					 ((uint32_t) (0x00 << 5))
#define ERROR_INTERRUPT_NOT_MASKED			 ((uint32_t) (0x01 << 5))

#define SPI_MOTOROLA_MODE								 ((uint32_t) (0x00 << 4))
#define SPI_TI_MODE											 ((uint32_t) (0x01 << 4))

#define SS_OUTPUT_DISABLE								 ((uint32_t) (0x00 << 2))
#define SS_OUTPUT_ENABLE								 ((uint32_t) (0x01 << 2))

#define TX_BUFFER_DMA_DISABLED					 ((uint32_t) (0x00 << 1))
#define TX_BUFFER_DMA_ENABLED						 ((uint32_t) (0x01 << 1))

#define RX_BUFFER_DMA_DISABLED					 ((uint32_t) (0x00 << 0))
#define RX_BUFFER_DMA_ENABLED						 ((uint32_t) (0x01 << 0))



											/* SPI status register */
#define _FRAME_FORMAT_ERROR_CLEAR()				((uint32_t) (0x01 << 8)) /* SPI->SR &= ~ */
#define _OVERRUN_OCCURRED_CLEAR()					((uint32_t) (0x01 << 6)) /* SPI->SR &= ~ */
#define _MODE_FAULT_OCCURRED_CLEAR()			((uint32_t) (0x01 << 5)) /* SPI->SR &= ~ */
#define _CRC_ERROR_FLAG_CLEAR()						((uint32_t) (0x01 << 4)) /* SPI->SR &= ~ */
#define _UNDERRUN_OCCURRED_CLEAR()				((uint32_t) (0x01 << 3)) /* SPI->SR &= ~ */


										/* SPI data register */



											/* SPI status register */
#define NO_FRAME_FORMAT_ERROR						((uint32_t) (0x01 << 8))  /* SPI->SR &= ~ */
#define SPI_ NOT_BUSY										((uint32_t) (0x01 << 7))  /* SPI->SR &= ~ */
#define TX_BUFFER_NOT_EMPTY							((uint32_t) (0x01 << 1))  /* SPI->SR &= ~ */
#define RX_BUFFER_NOT_EMPTY							((uint32_t) (0x01 << 0))  /* SPI->SR |=	  */

typedef enum
{
	HAL_SPI_STATE_RESET   		=	0x00,
	
	HAL_SPI_STATE_READY   		=	0x01,
	
	HAL_SPI_STATE_BUSY   			=	0x02,
	
	HAL_SPI_STATE_BUSY_TX   	=	0x12,
	
	HAL_SPI_STATE_BUSY_RX   	=	0x22,
	
	HAL_SPI_STATE_BUSY_TX_RX 	= 0x32,
	
	HAL_SPI_STATE_ERROR   		=	0x03
	
}HAL_SPI_State_t;




/* Configuration SPI pin */

/**
	* @breif SPI SR struct definition
	*/
typedef struct
{
	
	uint32_t Slave_Master_Config;			/*Slave configuration  1: Master configuration */
																		/*specifie operating mode salve or master*/
	
	uint32_t Uni_Bi_Directional;			/* 2-line unidirectional or 1-line bidirectional*/
				
	uint32_t DataSize;								/* 8-bit or 16-bit data */
				
	uint32_t Frame_Format;						/* MSB or LSB transmitted first  */
	
	uint32_t SW_Slave_Management;			/* Software OR Hardawre slave management  */
				
	uint32_t SPI_Enable;							/* Peripheral enabled or disabled  */
				
	uint32_t Baud_rate_Presc;					/* Baud rate control */
	
	uint32_t Clk_POL;									/* Clock polarity */
	
	uint32_t Clk_PHASE ;							/* Clock phase */			
	
}SPI_Config_t;


/**
	* @breif SPI Handle struct definition
	*/

typedef struct
{

	
	SPI_TypeDef *Instance;						/* SPI1 , SPI2 or SPI3*/
	
	SPI_Config_t Init;							/* SPI parametres communication*/
	
	uint8_t *pTXBuffer;								/* pointer to SPI TX buffer*/
	
	uint16_t TXBufferSize;							/* SPI TX transfer size*/
	
	uint16_t TXxBufferCount;					/* SPI TX transfer counter */
	
	uint8_t *pRXBuffer;								/* pointer to SPI RX buffer*/
	
	uint16_t RXBufferSize;							/* SPI RX transfer size*/
	
	uint16_t RXxBufferCount;					/* SPI RX transfer counter */
		
	HAL_SPI_State_t SPI_state;
			
	
}SPI_Handle_t;






/*****************************************************************************************/



extern SPI_Handle_t spi_handle;

/******************************************************************************************/
/*																																												*/
/*																	HAL SPI API																				*/
/*																																												*/
/******************************************************************************************/
/******************************************************************************************/
/**	@brief 	API used to do initialize the given SPI device																											
	*	@param 	*SPIx 	: Base adress of the SPIx																						
	*	@param	*buffer : Pointer to the pin configuration struct send by appli	
	*	@param	len 		: length of Rx Data		
	*	@retval None
	*/
void HAL_SPI_Init(SPI_Handle_t *SPI_Handle);



/******************************************************************************************/
/**	@brief 	API used to do master data transmission																											
	*	@param 	*SPIx 	: Base adress of the SPIx
	*	@param	*buffer : Pointer to Tx buffer
	*	@param	len : length of tx Data		
	*	@retval None
	*/
void HAL_SPI_Master_Tx(SPI_Handle_t *SPI_Handle , uint8_t *TxbufferM , uint16_t len);




/******************************************************************************************/
/**	@brief 	API used to do master data Reception																											
	*	@param 	*SPIx 	: Base adress of the SPIx
	*	@param	*buffer : Pointer to Rx buffer
	*	@param	len : length of tx Data		
	*	@retval None
	*/

void HAL_SPI_Master_Rx(SPI_Handle_t *SPI_Handle , uint8_t *RxbufferM , uint16_t len);



/**	@brief 	API used to do Slave data transmission																											
	*	@param 	*SPIx 	: Base adress of the SPIx
	*	@param	*buffer : Pointer to Tx buffer
	*	@param	len : length of tx Data		
	*	@retval None
	*/

void HAL_SPI_Slave_Tx(SPI_Handle_t *SPI_Handle , uint8_t *TxbufferS , uint16_t len);


/******************************************************************************************/
/**	@brief 	API used to do Slave data Reception																											
	*	@param 	*SPIx 	: Base adress of the SPIx
	*	@param	*buffer : Pointer to Rx buffer
	*	@param	len : length of tx Data		
	*	@retval None
	*/

void HAL_SPI_Slave_Rx(SPI_Handle_t *SPI_Handle , uint8_t *RxbufferS , uint16_t len);






/******************************************************************************************/
/**	@brief 	This function handle SPI interrupt																									
	*	@param 	Hspi 	: pointer to a spi _handle_t struct that
	*									contains the config information for spi module 
	*	@retval None
	*/

void HAL_I2C_SPI_IRQN_Interrupt(SPI_Handle_t *Hspi);



#endif __HAL_SPI_DRIVER




