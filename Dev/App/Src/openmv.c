/*              openmv_h7_diag.c 			 */
/* This file implements all prototypes 		 */
/* for communication with OpenMV H7 module 	 */
/*    Date 	  |   Author  |    Description 	 */
/* 19.02.2025 | Dan Balan | Creation of file */

#include <openmv.h>


volatile uint8_t tx_complete = 0;



/* Static functions */
static void OpenMV_SPI_ReadWrite(SPI_HandleTypeDef *hspi)
{
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
			camdata.camera_x |= (uint16_t)(data[0]<<8);
			HAL_Delay(20);
		}
	}
	if(HAL_SPI_TransmitReceive(hspi, RX_SS2, data, 1, 1000) == HAL_OK)
	{
		camdata.camera_y = (uint16_t)data[0];
		HAL_Delay(20);
		if(HAL_SPI_TransmitReceive(hspi, RX_SS2, data, 1, 1000) == HAL_OK)
		{
			camdata.camera_y |= (uint16_t)(data[0]<<8);
			HAL_Delay(20);
		}
	}
	if(HAL_SPI_TransmitReceive(hspi, RX_SS4, data, 1, 1000) == HAL_OK)
	{
		camdata.camera_h = (uint16_t)data[0];
		HAL_Delay(20);
		if(HAL_SPI_TransmitReceive(hspi, RX_SS4, data, 1, 1000) == HAL_OK)
		{
			camdata.camera_h |= (uint16_t)(data[0]<<8);
			HAL_Delay(20);
		}
	}

	if(HAL_SPI_TransmitReceive(hspi, RX_SS3, data, 1, 1000) == HAL_OK)
	{
		camdata.camera_w = (uint16_t)data[0];
		HAL_Delay(20);
		if(HAL_SPI_TransmitReceive(hspi, RX_SS3, data, 1, 1000) == HAL_OK)
		{
			camdata.camera_w |= (uint16_t)(data[0]<<8);
			HAL_Delay(20);
		}
	}

	cameraData = camdata;
}




static void OpenMV_UART_ReceivePhoto(UART_HandleTypeDef *huart)
{
	uint32_t bytes_sent = 0;
	while (bytes_sent < IMAGE_SIZE)
	{
		uint16_t bytes_to_send = (IMAGE_SIZE - bytes_sent > CHUNK_SIZE) ? CHUNK_SIZE : (IMAGE_SIZE - bytes_sent);

		tx_complete = 0;
		HAL_UART_Receive_DMA(huart, &OpenMV_CameraPhoto[bytes_sent], bytes_to_send);

		while(!tx_complete); //Wait for tx_com
		bytes_sent += bytes_to_send;
	}
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	tx_complete = 1;  // Image fully received

	// Crypto things :TBD

}

/* Extern API`s */
void OpenMV_Init(void)
{
	HAL_GPIO_WritePin(GPIOD,  SPI1_CS_OpenMV1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD,  SPI1_CS_OpenMV2_Pin, GPIO_PIN_RESET);
	SelectedBoard = NoBoard_Selected;
	tx_complete = 1;
}

/*OpenMV_MainFunction */
void OpenMV_SPI_MainFunction(SPI_HandleTypeDef *hspi1)
{
	//START OF SPI1 SLAVE1 Communication
	HAL_GPIO_WritePin(GPIOD,  SPI1_CS_OpenMV1_Pin, GPIO_PIN_RESET);
	HAL_Delay(10);
	OpenMV_SPI_ReadWrite(hspi1);
	HAL_GPIO_WritePin(GPIOD,  SPI1_CS_OpenMV1_Pin, GPIO_PIN_SET);
	//END OF SPI1 SLAVE1 Communication

	//START OF SPI1 SLAVE2 Communication
	HAL_GPIO_WritePin(GPIOD,  SPI1_CS_OpenMV2_Pin, GPIO_PIN_RESET);
	HAL_Delay(10);
	OpenMV_SPI_ReadWrite(hspi1);
	HAL_GPIO_WritePin(GPIOD,  SPI1_CS_OpenMV2_Pin, GPIO_PIN_SET);
	//END OF SPI1 SLAVE2 Communication
}

void OpenMV_UART_MainFunction(UART_HandleTypeDef *huart1, UART_HandleTypeDef *huart2)
{
	//START OF OpenMV1 UART Communication
	if(SelectedBoard == OpenMV1_Selected && tx_complete == 1)
	{
		OpenMV_UART_ReceivePhoto(huart1);
	}
	//END OF OpenMV1 UART Communication

	//START OF OpenMV2 UART Communication
	else if(SelectedBoard == OpenMV2_Selected && tx_complete == 1)
	{
		OpenMV_UART_ReceivePhoto(huart2);
	}
	//END OF OpenMV2 UART Communication
}


