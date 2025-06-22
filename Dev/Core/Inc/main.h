/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "openmv.h"
#include "MotDrv.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
extern OpenMV_ML_Data cameraData1;
extern OpenMV_ML_Data cameraData2;
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SPI1_NSS2_Pin GPIO_PIN_3
#define SPI1_NSS2_GPIO_Port GPIOE
#define SPI1_NSS1_Pin GPIO_PIN_4
#define SPI1_NSS1_GPIO_Port GPIOE
#define USER_Btn_Pin GPIO_PIN_13
#define USER_Btn_GPIO_Port GPIOC
#define FrontRight_Con1_Pin GPIO_PIN_4
#define FrontRight_Con1_GPIO_Port GPIOA
#define FrontRight_Con2_Pin GPIO_PIN_5
#define FrontRight_Con2_GPIO_Port GPIOA
#define BackRight_Con1_Pin GPIO_PIN_6
#define BackRight_Con1_GPIO_Port GPIOA
#define BackRight_Con2_Pin GPIO_PIN_7
#define BackRight_Con2_GPIO_Port GPIOA
#define LD3_Pin GPIO_PIN_14
#define LD3_GPIO_Port GPIOB
#define USB_PowerSwitchOn_Pin GPIO_PIN_6
#define USB_PowerSwitchOn_GPIO_Port GPIOG
#define USB_OverCurrent_Pin GPIO_PIN_7
#define USB_OverCurrent_GPIO_Port GPIOG
#define FrontLeft_Con1_Pin GPIO_PIN_6
#define FrontLeft_Con1_GPIO_Port GPIOC
#define FrontLeft_Con2_Pin GPIO_PIN_7
#define FrontLeft_Con2_GPIO_Port GPIOC
#define BackLeft_Con1_Pin GPIO_PIN_8
#define BackLeft_Con1_GPIO_Port GPIOC
#define BackLeft_Con2_Pin GPIO_PIN_9
#define BackLeft_Con2_GPIO_Port GPIOC
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_7
#define LD2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define AES128_KeyLength 128
#define AES128_IVLength 128
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
