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
#include "aes-gcm.h"

#ifndef OPENMV_H_INCLUDED
#define OPENMV_H_INCLUDED

#define CAMERA_NOT_INIT (uint8_t)0xFF
#define CAMERA_INIT (uint8_t) 0xAA
#define CAMERA_READ_LENGTH 5
#define SPI1_NSS2_Pin GPIO_PIN_3
#define SPI1_NSS2_GPIO_Port GPIOE
#define SPI1_NSS1_Pin GPIO_PIN_4
#define SPI1_NSS1_GPIO_Port GPIOE
#define LD3_Pin GPIO_PIN_14
#define LD3_GPIO_Port GPIOB

#define IMAGE_SIZE 38400

#define AES128_KeyLength 128
#define AES128_IVLength 128

/* Start of OpenMV data types */

typedef enum
{
	NoBoard_Selected,
	OpenMV1_Selected,
	OpenMV2_Selected
}OpenMV_SelectedBoard;

typedef struct{
	uint16_t camera_x;
	uint16_t camera_y;
	uint16_t camera_h;
}OpenMV_ML_Data;

/* End of OpenMV data types */

extern UART_HandleTypeDef huart4; //Used for OpenMV1
extern UART_HandleTypeDef huart5; //Used for OpenMV2
extern UART_HandleTypeDef huart7; //Used for ESP32
extern uint8_t OpenMV_CameraPhoto[IMAGE_SIZE];
extern uint8_t OpenMV_CypherPhoto[IMAGE_SIZE];
extern const uint8_t AESKey[AES128_KeyLength];
extern const uint8_t AESIv[AES128_IVLength];


/* Start of functions prototype declaration */

void OpenMV_Init(void);
void OpenMV_SPI_MainFunction(SPI_HandleTypeDef *hspi1);
void OpenMV_UART_MainFunction(UART_HandleTypeDef *huart1, UART_HandleTypeDef *huart2);



/* End of functions prototype declaration */

#endif
