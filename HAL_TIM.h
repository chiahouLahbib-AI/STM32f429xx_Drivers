
#ifndef HAL_TIM
#define HAL_TIM

/* MC specific header file for stm32f429ZITx based Discovery board  */

#include "stm32f429xx.h"
#include <stdint.h>

/*Define Macros*/
/***************************************************************/
/*									1. Global Macros									 				 */
/***************************************************************/
/**@Brief : Struct for Timer Paramters
 */
typedef struct
	{
		uint32_t Counter_Enable_u8;
		uint32_t Counter_u8;
		uint32_t Prescaler_u8;
		uint32_t Auto_Reload_Reg_u8;
	}Tim_Cfg_t;

/***************************************************************/
/*									2. Global functions								 				 */
/***************************************************************/
void Tim_Cfg(TIM_TypeDef *Tim, Tim_Cfg_t *Tim_Cfg);



	



#endif /*HAL_TIM*/