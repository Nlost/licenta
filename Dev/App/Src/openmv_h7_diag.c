/*              openmv_h7_diag.c 			 */
/* This file implements all prototypes 		 */
/* for communication with OpenMV H7 module 	 */
/*    Date 	  |   Author  |    Description 	 */
/* 19.02.2025 | Dan Balan | Creation of file */

#include "openmv_h7_diag.h"

void OpenMV_Init(void)
{
	HAL_GPIO_WritePin(GPIOD,  SPI1_CS_OpenMV1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD,  SPI1_CS_OpenMV2_Pin, GPIO_PIN_RESET);
}

void OpenMV_DeInit(void)
{
	return;
}

OpenMV_ReturnType OpenMV_Read(SPI_HandleTypeDef *hspi, OpenMV_ML_Data *cameraData)
{
	OpenMV_ReturnType retVal = CAMERA_OK;
	OpenMV_ML_Data camdata = {
			.camera_x = 0XFFFF,
			.camera_y = 0xFFFF,
			.camera_h = 0XFFFF,
			.camera_w = 0xFFFF,
			.command = 0xFF,
	};
	uint8_t data[] = {0};
	uint8_t RX_SS1[] = "A";
	uint8_t RX_SS2[] = "Y";
	uint8_t RX_SS3[] = "W";
	uint8_t RX_SS4[] = "H";

	if(HAL_SPI_TransmitReceive(hspi, RX_SS1, data, 1, 1000) == HAL_OK)
	{
		camdata.camera_x = (uint16_t)data[0];
		HAL_Delay(20);
		if(HAL_SPI_TransmitReceive(hspi, RX_SS1, data, 1, 1000) == HAL_OK)
		{
			camdata.camera_x |=(uint16_t)(data[0]<<8);
			HAL_Delay(20);
		}
	}
	if(HAL_SPI_TransmitReceive(hspi, RX_SS2, data, 1, 1000) == HAL_OK)
	{
		camdata.camera_y = (uint16_t)data[0];
		HAL_Delay(20);
		if(HAL_SPI_TransmitReceive(hspi, RX_SS2, data, 1, 1000) == HAL_OK)
		{
			camdata.camera_y |=(uint16_t)(data[0]<<8);
			HAL_Delay(20);
		}
	}
	if(HAL_SPI_TransmitReceive(hspi, RX_SS4, data, 1, 1000) == HAL_OK)
	{
		camdata.camera_h = (uint16_t)data[0];
		HAL_Delay(20);
		if(HAL_SPI_TransmitReceive(hspi, RX_SS4, data, 1, 1000) == HAL_OK)
		{
			camdata.camera_h |=(uint16_t)(data[0]<<8);
			HAL_Delay(20);
		}
	}

	if(HAL_SPI_TransmitReceive(hspi, RX_SS3, data, 1, 1000) == HAL_OK)
	{
		camdata.camera_w = (uint16_t)data[0];
		HAL_Delay(20);
		if(HAL_SPI_TransmitReceive(hspi, RX_SS3, data, 1, 1000) == HAL_OK)
		{
			camdata.camera_w |=(uint16_t)(data[0]<<8);
			HAL_Delay(20);
		}
	}

	*cameraData = camdata;
	return retVal;
}

OpenMV_ReturnType OpenMV_Write(SPI_HandleTypeDef *hspi, uint8_t* data)
{
	OpenMV_ReturnType retVal = CAMERA_OK;
	if(HAL_SPI_Transmit(hspi, data, 1, 5000) == HAL_OK)
	{
		HAL_GPIO_TogglePin(GPIOB, LD3_Pin);
	}
	else
	{
		retVal = CAMERA_NOT_OK;
	}
	return retVal;
}

/*OpenMV_MainFunction */
void OpenMV_MainFunction(SPI_HandleTypeDef *hspi1, OpenMV_ML_Data *cameraData)
{
	//START OF SPI1 SLAVE1 Communication
	HAL_GPIO_WritePin(GPIOD,  SPI1_CS_OpenMV1_Pin, GPIO_PIN_RESET);
	OpenMV_Read(hspi1, cameraData);
	HAL_GPIO_WritePin(GPIOD,  SPI1_CS_OpenMV1_Pin, GPIO_PIN_SET);
	//END OF SPI1 SLAVE1 Communication

	//START OF SPI1 SLAVE2 Communication
	HAL_GPIO_WritePin(GPIOD,  SPI1_CS_OpenMV2_Pin, GPIO_PIN_RESET);
	OpenMV_Read(hspi1, cameraData);
	HAL_GPIO_WritePin(GPIOD,  SPI1_CS_OpenMV2_Pin, GPIO_PIN_SET);


	//END OF SPI1 SLAVE2 Communication
}
