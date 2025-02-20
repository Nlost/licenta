/*              openmv_h7_diag.c 			 */
/* This file implements all prototypes 		 */
/* for communication with OpenMV H7 module 	 */
/*    Date 	  |   Author  |    Description 	 */
/* 19.02.2025 | Dan Balan | Creation of file */

#include "openmv_h7_diag.h"

void OpenMV_Init(void)
{
	return;
}

void OpenMV_DeInit(void)
{
	return;
}

OpenMV_ReturnType OpenMV_Read(SPI_HandleTypeDef *hspi, OpenMV_ML_Data *cameraData)
{
	OpenMV_ReturnType retVal = CAMERA_OK;
	OpenMV_ML_Data data = {0};
	uint8_t spi_data;
	/* Read Camera x position */
	if(HAL_SPI_TransmitReceive_IT(hspi, CAMERA_READ_X, &spi_data, 8) == HAL_OK)
	{
		data.camera_x = (uint16_t)spi_data;
		if(HAL_SPI_TransmitReceive_IT(hspi, CAMERA_READ_X, &spi_data, 8) == HAL_OK)
		{
			data.camera_x |= (uint16_t)(spi_data<<8);
		}
		else
		{
			retVal = CAMERA_NOT_OK;
		}
	}
	else
	{
		retVal = CAMERA_NOT_OK;
	}
	/* Read Camera y position */
	if(HAL_SPI_TransmitReceive_IT(hspi, CAMERA_READ_Y, &spi_data, 8) == HAL_OK)
	{
		data.camera_y = (uint16_t)spi_data;
		if(HAL_SPI_TransmitReceive_IT(hspi, CAMERA_READ_Y, &spi_data, 8) == HAL_OK)
		{
			data.camera_y |= (uint16_t)(spi_data<<8);
		}
		else
		{
			retVal = CAMERA_NOT_OK;
		}
	}
	else
	{
		retVal = CAMERA_NOT_OK;
	}
	/* Read Camera h position */
	if(HAL_SPI_TransmitReceive_IT(hspi, CAMERA_READ_H, &spi_data, 8) == HAL_OK)
	{
		data.camera_h = (uint16_t)spi_data;
		if(HAL_SPI_TransmitReceive_IT(hspi, CAMERA_READ_H, &spi_data, 8) == HAL_OK)
		{
			data.camera_h |= (uint16_t)(spi_data<<8);
		}
		else
		{
			retVal = CAMERA_NOT_OK;
		}
	}
	else
	{
		retVal = CAMERA_NOT_OK;
	}
	/* Read Camera w position */
	if(HAL_SPI_TransmitReceive_IT(hspi, CAMERA_READ_W, &spi_data, 8) == HAL_OK)
	{
		data.camera_w = (uint16_t)spi_data;
		if(HAL_SPI_TransmitReceive_IT(hspi, CAMERA_READ_W, &spi_data, 8) == HAL_OK)
		{
			data.camera_w |= (uint16_t)(spi_data<<8);
		}
		else
		{
			retVal = CAMERA_NOT_OK;
		}
	}
	else
	{
		retVal = CAMERA_NOT_OK;
	}
	/* Copy data to a global variable */
	*cameraData = data;
	return retVal;
}

OpenMV_ReturnType OpenMV_Write(SPI_HandleTypeDef *hspi, uint16_t data)
{
	//TO DO
	return CAMERA_OK;
}

/*OpenMV_MainFunction */
void OpenMV_MainFunction(SPI_HandleTypeDef *hspi)
{
	// TO DO
}
