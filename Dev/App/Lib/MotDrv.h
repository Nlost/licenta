
#include "openmv.h"

#ifndef MOTDRV_H_INCLUDED
#define MOTDRV_H_INCLUDED

#define FrontRight_Con1_Pin GPIO_PIN_4
#define FrontRight_Con2_Pin GPIO_PIN_5
#define BackRight_Con1_Pin GPIO_PIN_6
#define BackRight_Con2_Pin GPIO_PIN_7
#define Right_GPIO_Port GPIOA


#define FrontLeft_Con1_Pin GPIO_PIN_6
#define FrontLeft_Con2_Pin GPIO_PIN_7
#define BackLeft_Con1_Pin GPIO_PIN_8
#define BackLeft_Con2_Pin GPIO_PIN_9
#define Left_GPIO_Port GPIOC


#define IMAGE_WIDTH 240
#define CENTER_TOLERANCE 20
#define NEAR_THRESHOLD 80
#define FAR_THRESHOLD 30

typedef enum
{
	FrontLeft,
	FrontRight,
	BackLeft,
	BackRight
}Motor_Select;

typedef enum
{
	Front,
	Back,
	Stop
}Motor_Direction;

void MotDrv_Init();
void MotDrv_TakeDecision(OpenMV_ML_Data cameraData1, OpenMV_ML_Data cameraData2);


extern TIM_HandleTypeDef htim4;

#endif
