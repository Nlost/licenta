/*              openmv_h7_diaG.h 			 */
/* This file describes all prototypes 		 */
/* for communication with OpenMV H7 module 	 */
/*    Date 	  |   Author  |    Description 	 */
/* 19.02.2025 | Dan Balan | Creation of file */

#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_spi.h"
#include "stm32f4xx_hal_gpio.h"

#ifndef OPENMV_H7_H
#define OPENMV_H7_H
#endif

#define CAMERA_NOT_INIT (uint8_t)0xFF
#define CAMERA_INIT (uint8_t) 0xAA
#define CAMERA_READ_LENGTH 5
#define SPI1_CS_OpenMV1_Pin GPIO_PIN_14
#define SPI1_CS_OpenMV1_GPIO_Port GPIOD
#define SPI1_CS_OpenMV2_Pin GPIO_PIN_15
#define SPI1_CS_OpenMV2_GPIO_Port GPIOD
#define LD3_Pin GPIO_PIN_14
#define LD3_GPIO_Port GPIOB

/* Start of OpenMV data types */

typedef enum
{
	CAMERA_NOT_OK,
	CAMERA_OK
}OpenMV_ReturnType;

typedef enum
{
	CAMERA_READ_X,
	CAMERA_READ_Y,
	CAMERA_READ_H,
	CAMERA_READ_W,
	CAMERA_READ_COMMAND
}OpenMV_SPI_Command;

typedef struct{
	int16_t camera_x;
	int16_t camera_y;
	int16_t camera_h;
	int16_t camera_w;
	uint8_t command;
}OpenMV_ML_Data;

/* End of OpenMV data types */

/* Start of functions prototype declaration */

void OpenMV_Init(void);
void OpenMV_DeInit(void);
OpenMV_ReturnType OpenMV_Read(SPI_HandleTypeDef *hspi, OpenMV_ML_Data *cameraData);
OpenMV_ReturnType OpenMV_Write(SPI_HandleTypeDef *hspi, uint8_t* data);
void OpenMV_MainFunction(SPI_HandleTypeDef *hspi1, OpenMV_ML_Data *cameraData);

/* End of functions prototype declaration */
