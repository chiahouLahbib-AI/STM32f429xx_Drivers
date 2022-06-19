
#include "spi_master.h"
#include "HAL_GPIO_Driver.h"
#include "application_SPI.h"

/**
	*@brief : delay
	*@param : None
	*@retval: void
	*/
	void delay_gen(void)
	{
		int i;
		for(i = 0 ;i<500000; i++ );
	}

/**
	*@brief : this function handle SPI2 interrupt request
	*@param : None
	*@retval: None
	*/
	
	void SPI2_IRQHandler(void)
	{
		/* call the driver api tp processinterrupt */
		HAL_I2C_SPI_IRQN_Interrupt(&spi_handle);
	}


/**
	*@brief : this function handle EXT0 interrupt request
	*@param : None
	*@retval: None
	*/
	
	void EXTI0_IRQHandler(void)
	{
		/*  clear ISR bit*/
		HAL_GPIO_Interrupt_Clear(GPIO_BUTTON_PIN);
		/* do your task here*/
		TestReady = 1;
	}
	
	/****************************************/
	/*			Master command sending data			*/
	/****************************************/
	
	