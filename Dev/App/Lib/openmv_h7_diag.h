/*              openmv_h7_diaG.h 			 */
/* This file describes all prototypes 		 */
/* for communication with OpenMV H7 module 	 */
/*    Date 	  |   Author  |    Description 	 */
/* 19.02.2025 | Dan Balan | Creation of file */

#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_spi.h"

#ifndef OPENMV_H7_H
#define OPENMV_H7_H
#endif

#define CAMERA_NOT_INIT (uint8_t)0xFF
#define CAMERA_INIT (uint8_t) 0xAA
#define CAMERA_READ_X (const uint8_t*)1
#define CAMERA_READ_Y (const uint8_t*)2
#define CAMERA_READ_H (const uint8_t*)3
#define CAMERA_READ_W (const uint8_t*)4

/* Start of OpenMV data types */

typedef enum
{
	CAMERA_NOT_OK,
	CAMERA_OK
}OpenMV_ReturnType;

typedef struct{
	int16_t camera_x;
	int16_t camera_y;
	int16_t camera_h;
	int16_t camera_w;
}OpenMV_ML_Data;

/* End of OpenMV data types */

/* Start of functions prototype declaration */

void OpenMV_Init(void);
void OpenMV_DeInit(void);
OpenMV_ReturnType OpenMV_Read(SPI_HandleTypeDef *hspi, OpenMV_ML_Data *cameraData);
OpenMV_ReturnType OpenMV_Write(SPI_HandleTypeDef *hspi, uint16_t data);
void OpenMV_MainFunction(SPI_HandleTypeDef *hspi);

/* End of functions prototype declaration */
