/*              openmv.h 			 */
/* This file describes all prototypes 		 */
/* for communication with OpenMV H7 module 	 */
/*    Date 	  |   Author  |    Description 	 */
/* 19.02.2025 | Dan Balan | Creation of file */

#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_spi.h"
#include "stm32f4xx_hal_gpio.h"


#ifndef OPENMV_H_INCLUDED
#define OPENMV_H_INCLUDED

#define SPI1_NSS2_Pin GPIO_PIN_3
#define SPI1_NSS2_GPIO_Port GPIOE
#define SPI1_NSS1_Pin GPIO_PIN_4
#define SPI1_NSS1_GPIO_Port GPIOE
#define LD3_Pin GPIO_PIN_14
#define LD3_GPIO_Port GPIOB


/* Start of OpenMV data types */

typedef struct{
	uint16_t camera_x;
	uint16_t camera_y;
	uint16_t camera_h;
}OpenMV_ML_Data;

/* End of OpenMV data types */


/* Start of functions prototype declaration */

void OpenMV_Init(void);
void OpenMV_SPI_MainFunction(SPI_HandleTypeDef *hspi1);



/* End of functions prototype declaration */

#endif
