
#ifndef __HAL_SPI_Matser
#define __HAL_SPI_Matser

#include "stdint.h"

#define GPIO_BUTTON_PIN 0

#define CMD_MASTER_WRITE ((uint16_t)0x5678)
#define SPI_ACK_BYTES 0xD5E5
#define DATA_LENGTH 4
#define CMD_LENGTH 2
#define ACK_LENGTH 2



uint8_t TestReady = 0;






/* salve will relpay this data when master issues read command */
 uint8_t slave_replay_data[4]={0x55, 0xbb, 0x55, 0xbb};

 /* master read/write buffers*/
 uint8_t master_write_buff[4]={0x0a, 0x0b, 0x0c, 0x0d};
 uint8_t master_read_buff[4];
 
 
void delay_gen(void);
void SPI2_IRQHandler(void);
void EXTI0_IRQHandler(void);
	
	
	
	
#endif __HAL_SPI_Matser







