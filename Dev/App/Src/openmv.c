/*              openmv.c 			 */
/* This file implements all prototypes 		 */
/* for communication with OpenMV H7 module 	 */
/*    Date 	  |   Author  |    Description 	 */
/* 19.02.2025 | Dan Balan | Creation of file */

#include "openmv.h"


static uint8_t rx_dma1 = 1;
static uint8_t rx_dma2 = 2;
static uint8_t cameraSelected;
OpenMV_ML_Data cameraData1 = {0};
OpenMV_ML_Data cameraData2 = {0};
static uint8_t rxBuffer[7] = {0};
static uint8_t rxBuffer1[7] = {0};


/* Extern API`s */
void OpenMV_Init(void)
{
	HAL_GPIO_WritePin(SPI1_NSS1_GPIO_Port,  SPI1_NSS1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(SPI1_NSS2_GPIO_Port,  SPI1_NSS2_Pin, GPIO_PIN_SET);
	HAL_Delay(10);
	rx_dma1 = 1;
	rx_dma2 = 1;
	cameraSelected = 0;
}

void OpenMV_SPI_MainFunction(SPI_HandleTypeDef *hspi1)
{
    // --- START SPI1 SLAVE1 COMMUNICATION ---
    rx_dma1 = 0;
    cameraSelected = 1;
    HAL_SPI_Receive_DMA(hspi1, rxBuffer, 7); // Start DMA BEFORE asserting NSS
    HAL_GPIO_WritePin(SPI1_NSS2_GPIO_Port, SPI1_NSS2_Pin, GPIO_PIN_SET); // disable slave 2
    HAL_GPIO_WritePin(SPI1_NSS1_GPIO_Port, SPI1_NSS1_Pin, GPIO_PIN_RESET); // enable slave 1
    HAL_Delay(10); // give slave time to send
    HAL_GPIO_WritePin(SPI1_NSS1_GPIO_Port, SPI1_NSS1_Pin, GPIO_PIN_SET); // end transaction

    while (!rx_dma1); // wait for DMA complete
    if (rxBuffer[0] == 85) {
        cameraData2.camera_x = rxBuffer[1] | (rxBuffer[2] << 8);
        cameraData2.camera_y = rxBuffer[3] | (rxBuffer[4] << 8);
        cameraData2.camera_h = rxBuffer[5] | (rxBuffer[6] << 8);
        printf("Camera2 data x=%d y=%d h=%d\n", cameraData1.camera_x, cameraData1.camera_y, cameraData1.camera_h);
    }

    // --- START SPI1 SLAVE2 COMMUNICATION ---
    rx_dma2 = 0;
    cameraSelected = 2;
    HAL_SPI_Receive_DMA(hspi1, rxBuffer1, 7); // Start DMA BEFORE asserting NSS
    HAL_GPIO_WritePin(SPI1_NSS1_GPIO_Port, SPI1_NSS1_Pin, GPIO_PIN_SET); // disable slave 1
    HAL_GPIO_WritePin(SPI1_NSS2_GPIO_Port, SPI1_NSS2_Pin, GPIO_PIN_RESET); // enable slave 2
    HAL_Delay(10); // give slave time to send
    HAL_GPIO_WritePin(SPI1_NSS2_GPIO_Port, SPI1_NSS2_Pin, GPIO_PIN_SET); // end transaction

    while (!rx_dma2); // wait for DMA complete
    if (rxBuffer1[0] == 85) {
    	cameraData1.camera_x = rxBuffer1[1] | (rxBuffer1[2] << 8);
    	cameraData1.camera_y = rxBuffer1[3] | (rxBuffer1[4] << 8);
    	cameraData1.camera_h = rxBuffer1[5] | (rxBuffer1[6] << 8);
        printf("Camera1 data x=%d y=%d h=%d\n", cameraData2.camera_x, cameraData2.camera_y, cameraData2.camera_h);
    }
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if(cameraSelected == 1)
	{
		rx_dma1 = 1;
	}
	else if(cameraSelected == 2)
	{
		rx_dma2 = 1;
	}
}


