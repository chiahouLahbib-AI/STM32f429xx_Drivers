
#include<stdint.h>
#include "HAL_SPI_Driver.h"



/******************************************************************************************/
/*												1. Prototype LOCAL FUNCTION																			*/
/******************************************************************************************/


static void HAL_SPI_CPHA_CPOL(SPI_TypeDef *pSPIx , uint32_t CPHASE , uint32_t CPOL);
static void HAL_SPI_Device_Mode(SPI_TypeDef *pSPIx , uint32_t Master);
static void HAL_SPI_Baud_Rate_Presc(SPI_TypeDef *pSPIx , uint32_t baude);
static void HAL_SPI_SPI_Frame_Format(SPI_TypeDef *pSPIx , uint32_t Format);
static void HAL_SPI_Enable_Peripheral(SPI_TypeDef *pSPIx , uint32_t EnablePeripheram);
static void HAL_SPI_SW_Slave_Management(SPI_TypeDef *pSPIx , uint32_t Soft_Slave_Management);
static void HAL_SPI_Data_Size(SPI_TypeDef *pSPIx , uint32_t DataSize);
static void HAL_SPI_Direction_Mode(SPI_TypeDef *pSPIx , uint32_t Unidirec_Bidirec_Mode);

static void HAL_SPI_RXNE_Enable_Interrupt(SPI_TypeDef *SPIx);
static void HAL_SPI_TXE_Enable_Interrupt(SPI_TypeDef *SPIx);
static void HAL_SPI_TXE_Disable_Interrupt(SPI_TypeDef *SPIx); 

void HAL_SPI_Handle_TX_Interrupt(SPI_Handle_t *Hspi);
void HAL_SPI_Handle_RX_Interrupt(SPI_Handle_t *Hspi);
static void HAL_SPI_TX_Close_Interrupt(SPI_Handle_t *Hspi);
static void HAL_SPI_RX_Close_Interrupt(SPI_Handle_t *Hspi);


/******************************************************************************************/
/**	@brief 	API used to do initialize the given SPI device																											
	*	@param 	*SPIx 	: Base adress of the SPIx																						
	*	@param	*buffer : Pointer to the pin configuration struct send by appli	
	*	@param	len 		: length of Rx Data		
	*	@retval None
	*/
void HAL_SPI_Init(SPI_Handle_t *SPI_Handle)
{
	
	/* 	1. Helper function to configure clock polarity and phase */
	HAL_SPI_CPHA_CPOL(SPI_Handle->Instance , SPI_Handle->Init.Clk_PHASE , SPI_Handle->Init.Clk_POL);
		
	/* 	2. Helper function to configure master/ slave selection */
	HAL_SPI_Device_Mode(SPI_Handle->Instance , SPI_Handle->Init.Slave_Master_Config);
		
	/* 	3. Helper function to configure baud rate presclar */
	HAL_SPI_Baud_Rate_Presc(SPI_Handle->Instance, SPI_Handle->Init.Baud_rate_Presc);
		
	
	/* 	4. Helper function to enable SPI peripheral and frame format */
	HAL_SPI_Enable_Peripheral(SPI_Handle->Instance , SPI_Handle->Init.SPI_Enable);
	HAL_SPI_SPI_Frame_Format(SPI_Handle->Instance , SPI_Handle->Init.Frame_Format);
	
	/*	5. Helper function to configure Software slave management	*/
	HAL_SPI_SW_Slave_Management(SPI_Handle->Instance , SPI_Handle->Init.SW_Slave_Management);
		
	/*	6. Helper function to configure data size and direction mode	*/
	HAL_SPI_Data_Size(SPI_Handle->Instance , SPI_Handle->Init.DataSize);
	HAL_SPI_Direction_Mode(SPI_Handle->Instance , SPI_Handle->Init.Uni_Bi_Directional);
		

} 
	
	

/******************************************************************************************/
/**	@brief 	API used to do master data Reception																											
	*	@param 	*SPIx 	: Base adress of the SPIx
	*	@param	*buffer : Pointer to Rx buffer
	*	@param	len : length of tx Data		
	*	@retval None
	*/

void HAL_SPI_Master_Tx(SPI_Handle_t *SPI_Handle , uint8_t *TxbufferM , uint16_t len)
{
	SPI_Handle->pTXBuffer = TxbufferM;
	SPI_Handle->TXBufferSize = len;
	SPI_Handle->TXxBufferCount = len;
	SPI_Handle->SPI_state = HAL_SPI_STATE_BUSY_TX;
	//HAL_SPI_Enable(SPI_Handle->Instance);
	HAL_SPI_TXE_Enable_Interrupt(SPI_Handle->Instance);
}


/******************************************************************************************/
/**	@brief 	API used to do master data Reception																											
	*	@param 	*SPIx 	: Base adress of the SPIx
	*	@param	*buffer : Pointer to Rx buffer
	*	@param	len : length of tx Data		
	*	@retval None
	*/

void HAL_SPI_Master_Rx(SPI_Handle_t *SPI_Handle , uint8_t *RxbufferM , uint16_t len)
{
	uint32_t val;
	val = 0;
	/* this is a dummy tx*/
	SPI_Handle->pTXBuffer = RxbufferM;
	SPI_Handle->TXBufferSize = len;
	SPI_Handle->TXxBufferCount = len;
	
	/* data will be rxed to rx buffer */
	SPI_Handle->pRXBuffer = RxbufferM;
	SPI_Handle->RXBufferSize = len;
	SPI_Handle->RXxBufferCount = len;
	
	/* Driver is busy in RX */
	SPI_Handle->SPI_state = HAL_SPI_STATE_BUSY_RX;
	//HAL_SPI_Enable(SPI_Handle->Instance);
		/* read data once before enabling
		 * the RXNE interrupt to make sure DR is empty	
		 */
	val = SPI_Handle->Instance->DR;
	/* now enabling both txe rxne interrupt*/	
	HAL_SPI_RXNE_Enable_Interrupt(SPI_Handle->Instance);
	HAL_SPI_TXE_Enable_Interrupt(SPI_Handle->Instance);
	
}


/**	@brief 	API used to do Slave data transmission																											
	*	@param 	*SPIx 	: Base adress of the SPIx
	*	@param	*buffer : Pointer to Tx buffer
	*	@param	len : length of tx Data		
	*	@retval None
	*/

void HAL_SPI_Slave_Tx(SPI_Handle_t *SPI_Handle , uint8_t *TxbufferS , uint16_t len)
{

	/* populate data to be transmitted */
	SPI_Handle->pTXBuffer = TxbufferS;
	SPI_Handle->TXBufferSize = len;
	SPI_Handle->TXxBufferCount = len;

	/* Dummy rx*/
	SPI_Handle->pRXBuffer = TxbufferS;
	SPI_Handle->RXBufferSize = len;
	SPI_Handle->RXxBufferCount = len;
	
	/* state */
	SPI_Handle->SPI_state = HAL_SPI_STATE_BUSY_TX;
	
	/*enable spi*/
	//HAL_SPI_Enable(SPI_Handle->Instance);
	
		/* now enabling both txe rxne interrupt*/	
	HAL_SPI_RXNE_Enable_Interrupt(SPI_Handle->Instance);
	HAL_SPI_TXE_Enable_Interrupt(SPI_Handle->Instance);
	
}

/******************************************************************************************/
/**	@brief 	API used to do Slave data Reception																											
	*	@param 	*SPIx 	: Base adress of the SPIx
	*	@param	*buffer : Pointer to Rx buffer
	*	@param	len : length of tx Data		
	*	@retval None
	*/

void HAL_SPI_Slave_Rx(SPI_Handle_t *SPI_Handle , uint8_t *RxbufferS , uint16_t len)
{
	SPI_Handle->pRXBuffer = RxbufferS;
	SPI_Handle->RXBufferSize = len;
	SPI_Handle->RXxBufferCount = len;
	/* status of spi */
	SPI_Handle->SPI_state = HAL_SPI_STATE_BUSY_RX;
	
	/*enable spi*/
	//HAL_SPI_Enable(SPI_Handle->Instance);
	
	/* salve need to rcv data so enable rxne */
	HAL_SPI_RXNE_Enable_Interrupt(SPI_Handle->Instance);
}




/******************************************************************************************/
/**	@brief 	API used to do Slave data Reception																											
	*	@param 	*SPIx 	: Base adress of the SPIx
	*	@param	*buffer : Pointer to Rx buffer
	*	@param	len : length of tx Data		
	*	@retval None
	*/

static void HAL_SPI_Slave_NSS(SPI_Handle_t *SPI_Handle , uint8_t *RxbufferS , uint16_t len)
{
	
}



/******************************************************************************************/
/**	@brief 	API used to do Slave data Reception																											
	*	@param 	*SPIx 	: Base adress of the SPIx
	*	@param	*buffer : Pointer to Rx buffer
	*	@param	len : length of tx Data		
	*	@retval None
	*/

static void HAL_SPI_Master_NSS(SPI_Handle_t *SPI_Handle , uint8_t *RxbufferS , uint16_t len)
{
	
}


/******************************************************************************************/
/**	@brief 	This function handle SPI interrupt request																							
	*	@param 	Hspi 	: pointer to a spi _handle_t struct that
	*									contains the config information for spi module 
	*	@retval None
	*/

 void HAL_I2C_SPI_IRQN_Interrupt(SPI_Handle_t *Hspi)
{
	uint32_t tmp1 = 0;
	uint32_t tmp2 = 0; 
	/* check to see RXNE is set in the status register */
	tmp1 = (Hspi->Instance->SR & RX_BUFFER_NOT_EMPTY);
	/* check to see RXNEIE bit is enabled in the control register */
	tmp2 = (Hspi->Instance->CR2 & RXNE_NOT_INTERRUPT_MASKED);
	
	if((tmp1 != 0) && (tmp2 != 0))
	{
 /*RXNE flas is set
	*handle the RX of data bytes
	*/	
		HAL_SPI_Handle_RX_Interrupt(Hspi);
	}
	
	/* check to see TXE is set in the status register*/
	tmp1 = (Hspi->Instance->SR & TX_BUFFER_NOT_EMPTY);
	/* check to see RXNEIE bit is enabled in the control register */
	tmp2 = (Hspi->Instance->CR2 & TXE_NOT_INTERRUPT_MASKED);
	
	if((tmp1 != 0) && (tmp2 != 0))
	{
 /*TXE flas is set
	*handle the TX of data bytes
	*/	
		HAL_SPI_Handle_TX_Interrupt(Hspi);
	}	
}



/******************************************************************************************/
/**	@brief 																									
	*	@param 	 	 
	*	@retval None
	*/

static void HAL_SPI_TXE_Enable_Interrupt(SPI_TypeDef *SPIx)
{
	SPIx->CR2 |= (1 << 7);
}


/******************************************************************************************/
/**	@brief 																									
	*	@param 	 	 
	*	@retval None
	*/

static void HAL_SPI_TXE_Disable_Interrupt(SPI_TypeDef *SPIx)
{
	SPIx->CR2 &= ~(1 << 7);
}


/******************************************************************************************/
/**	@brief 																									
	*	@param 	 	 
	*	@retval None
	*/

static void HAL_SPI_RXNE_Enable_Interrupt(SPI_TypeDef *SPIx)
{
	SPIx->CR2 |= (1 << 6);
}


/******************************************************************************************/
/**	@brief 																									
	*	@param 	 	 
	*	@retval None
	*/

static void HAL_SPI_RXNE_Disable_Interrupt(SPI_TypeDef *SPIx)
{
	SPIx->CR2 &= ~(unsigned )(1 << 6);
}


/******************************************************************************************/
/*																	1. LOCAL FUNCTION																			*/
/******************************************************************************************/
/******************************************************************************************/
/**	@brief 	
	*	@param 	
	*									
	*	@retval None
	*/
static void HAL_SPI_CPHA_CPOL(SPI_TypeDef *pSPIx , uint32_t CPHASE , uint32_t CPOL)
{
	if(CPHASE)
	{
		pSPIx->CR1 |= CLOCK_PHASE_1 ;
	}
	else 
	{
		pSPIx->CR1 &= ~CLOCK_PHASE_1 ;
	}
	
		if(CPOL)
	{
		pSPIx->CR1 |= CLOCK_POLARITY_1 ;
	}
	else 
	{
		pSPIx->CR1 &= ~CLOCK_POLARITY_1 ;
	}
	 
}

/******************************************************************************************/
/**	@brief 	
	*	@param 	
	*									
	*	@retval None
	*/
static void HAL_SPI_Device_Mode(SPI_TypeDef *pSPIx , uint32_t Master)
{
	if(Master)
	{
		pSPIx->CR1 |= MASTER_CONFIGURATION ;
	}
	else 
	{
		pSPIx->CR1 &= ~MASTER_CONFIGURATION ;
	}
}


/******************************************************************************************/
/**	@brief 	
	*	@param 	
	*									
	*	@retval None
	*/
static void HAL_SPI_Baud_Rate_Presc(SPI_TypeDef *pSPIx , uint32_t baude)
{
	pSPIx->CR1 |= baude;
}

/******************************************************************************************/
/**	@brief 	
	*	@param 	
	*									
	*	@retval None
	*/
static void HAL_SPI_SPI_Frame_Format(SPI_TypeDef *pSPIx , uint32_t Format)
{
	if(Format)
	{
		pSPIx->CR1 |= LSB_TRANSMITTED_FIRST ; 
	}
	else
	{
		pSPIx->CR1 &= ~LSB_TRANSMITTED_FIRST ; 
	}
}


/******************************************************************************************/
/**	@brief 	
	*	@param 	
	*									
	*	@retval None
	*/
static void HAL_SPI_Enable_Peripheral(SPI_TypeDef *pSPIx , uint32_t EnablePeripheram)
{
	if(EnablePeripheram)
	{
		pSPIx->CR1 |= SPI_ENABLE ; 
	}
	else
	{
		pSPIx->CR1 &= ~SPI_ENABLE ; 
	}
}

/******************************************************************************************/
/**	@brief 	
	*	@param 	
	*									
	*	@retval None
	*/

static void HAL_SPI_NSS_Master(SPI_TypeDef *pSPIx , uint32_t NSSManagement)
{
	if(NSSManagement)
	{
		pSPIx->CR1 |= SW_SLAVE_MANAGEMENT_ENABLED ; 
		pSPIx->CR1 |= INTERNAL_SLAVE_SELECT;
	}
	else
	{
		pSPIx->CR1 &= ~SW_SLAVE_MANAGEMENT_ENABLED ; 
	}
}


/******************************************************************************************/
/**	@brief 	
	*	@param 	
	*									
	*	@retval None
	*/

static void HAL_SPI_SW_Slave_Management(SPI_TypeDef *pSPIx , uint32_t Soft_Slave_Management)
{
	if(Soft_Slave_Management)
	{
		pSPIx->CR1 |= SW_SLAVE_MANAGEMENT_ENABLED ; 
	}
	else
	{
		pSPIx->CR1 &= ~SW_SLAVE_MANAGEMENT_ENABLED ; 
	}
}


/******************************************************************************************/
/**	@brief 	
	*	@param 	
	*									
	*	@retval None
	*/
static void HAL_SPI_Data_Size(SPI_TypeDef *pSPIx , uint32_t DataSize)
{
	if(DataSize)
	{
		pSPIx->CR1 |= DATA_FRAME_FORMAT_16_BIT ; 
	}
	else
	{
		pSPIx->CR1 &= ~DATA_FRAME_FORMAT_16_BIT ; 
	}
}

/******************************************************************************************/
/**	@brief 	
	*	@param 	
	*									
	*	@retval None
	*/

static void HAL_SPI_Direction_Mode(SPI_TypeDef *pSPIx , uint32_t Unidirec_Bidirec_Mode)
{
	if(Unidirec_Bidirec_Mode)
	{
		pSPIx->CR1 |= BI_TTRANSMIT_ONLY_MODE ; 
	}
	else
	{
		pSPIx->CR1 &= ~BI_TTRANSMIT_ONLY_MODE ; 
	}
}
	

/**	@brief handles TEX interrupt	
	*	@param 	hspi : pointer to a spi_handle_t struct that contains
	*					the configurations information for spi module.
	*									
	*	@retval None
	*/
void HAL_SPI_Handle_TX_Interrupt(SPI_Handle_t *Hspi)
{
	/* Transmit data in 8 bit mode */
	if(Hspi->Init.DataSize == DATA_FRAME_FORMAT_8_BIT)
	{
		Hspi->Instance->DR = (*Hspi->pTXBuffer++);
		Hspi->TXxBufferCount--;
	}
	/*transmit data in 16 bit Mode*/
	else
	{
		Hspi->Instance->DR = *((uint16_t*)Hspi->pTXBuffer);
		Hspi->pTXBuffer+=2;
		Hspi->TXxBufferCount-=2;
	}
	if(Hspi->TXxBufferCount == 0)
	{
		HAL_SPI_TX_Close_Interrupt(Hspi);
	}
}

/**	@brief handles RXNE interrupt	
	*	@param 	hspi : pointer to a spi_handle_t struct that contains
	*					the configurations information for spi module.
	*									
	*	@retval None
	*/
void HAL_SPI_Handle_RX_Interrupt(SPI_Handle_t *Hspi)
{
	/*Receive  data in 8 bit mode*/
	if(Hspi->Init.DataSize == DATA_FRAME_FORMAT_8_BIT)
	{
		/*Null check*/
		if(Hspi->pRXBuffer++)
		{
			(*Hspi->pRXBuffer++) = (uint8_t)Hspi->Instance->DR;
			Hspi->RXxBufferCount--;
		}
	}
	/* Receive 16 bit mode*/
	else
		{
				*((uint16_t*)Hspi->pRXBuffer) = (uint16_t)Hspi->Instance->DR;
				Hspi->pRXBuffer+=2;
				Hspi->RXxBufferCount-=2;
		}
		if(Hspi->RXxBufferCount == 0)
		{
			HAL_SPI_RX_Close_Interrupt(Hspi);
		}
}
/* @brief  : close Tx transfer
 * @param  : 
 * @retval : void
 */
static void HAL_SPI_TX_Close_Interrupt(SPI_Handle_t *Hspi)
{
	/* Disable TXE interrupt */
	HAL_SPI_TXE_Disable_Interrupt(Hspi->Instance);
	
	/* if master and if driver state is not HAL_SPI_STATE_BUSY_RX then make state */
	if(Hspi->Init.Slave_Master_Config && (Hspi->SPI_state != HAL_SPI_STATE_BUSY_RX)) /* Check this mode */
	{
		Hspi->SPI_state = HAL_SPI_STATE_READY;	
	}
}

/* @brief  : close Rx transfer
 * @param  : 
 * @retval : void
 */
static void HAL_SPI_RX_Close_Interrupt(SPI_Handle_t *Hspi)
{
	/* Disable TXE interrupt */
	HAL_SPI_TXE_Disable_Interrupt(Hspi->Instance);
	
	/* if master and if driver state is not HAL_SPI_STATE_BUSY_RX then make state */
	if(Hspi->Init.Slave_Master_Config && (Hspi->SPI_state != HAL_SPI_STATE_BUSY_RX))
	{
		Hspi->SPI_state = HAL_SPI_STATE_READY;	
	}
}
