
#include "openmv.h"

#ifndef MOTDRV_H_INCLUDED
#define MOTDRV_H_INCLUDED

#define MIN_DISTANCE
#define MAX_DISTANCE
#define MAX_WIDTH
#define MAX_HEIGHT
#define Motor1_Con1_Pin GPIO_PIN_2
#define Motor1_Con1_GPIO_Port GPIOE
#define Motor1_Con2_Pin GPIO_PIN_3
#define Motor1_Con2_GPIO_Port GPIOE
#define Motor2_Con1_Pin GPIO_PIN_4
#define Motor2_Con1_GPIO_Port GPIOE
#define Motor2_Con2_Pin GPIO_PIN_5
#define Motor2_Con2_GPIO_Port GPIOE

typedef enum
{
	Motor1,
	Motor2
}Motor_Select;

void MotDrv_TakeDecision(OpenMV_ML_Data cameraData1, OpenMV_ML_Data cameraData2);


extern TIM_HandleTypeDef htim4;

#endif
