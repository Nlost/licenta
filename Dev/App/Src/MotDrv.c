#include "Motdrv.h"

int i=0;

static void setSpeed(Motor_Select motor, uint32_t Speed)
{
	uint32_t power = (uint32_t)(Speed/(float)100 * TIM4->ARR);
	switch(motor)
	{
	case Motor1:
		TIM4->CCR1 = power;
		HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
		break;
	case Motor2:
		HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_2);
		TIM4->CCR2 = Speed;
		HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
		break;
	default:
		TIM4->CCR1 = 0;
		TIM4->CCR2 = 0;
		break;
	}
}

static void MotDrv_GoFront(uint32_t speed)
{
	//Set Motor1 to go front
	HAL_GPIO_WritePin(Motor1_Con1_GPIO_Port, Motor1_Con1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Motor1_Con2_GPIO_Port, Motor1_Con2_GPIO_Port, GPIO_PIN_RESET);

	//Set Motor2 to go front
	HAL_GPIO_WritePin(Motor2_Con1_GPIO_Port, Motor2_Con1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Motor2_Con2_GPIO_Port, Motor2_Con2_GPIO_Port, GPIO_PIN_RESET);

	setSpeed(Motor1, speed);
	setSpeed(Motor2, speed);

}

static void MotDrv_GoBack(uint32_t speed)
{
	(void)speed;
}

static void MotDrv_TurnRight(uint32_t speed)
{
	(void)speed;
}

static void MotDrv_TurnLeft(uint32_t speed)
{
	(void)speed;
}

static void MotDrv_Stay()
{
	//Set Motor1 to go front
	HAL_GPIO_WritePin(Motor1_Con1_GPIO_Port, Motor1_Con1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Motor1_Con2_GPIO_Port, Motor1_Con2_GPIO_Port, GPIO_PIN_RESET);

	//Set Motor2 to go front
	HAL_GPIO_WritePin(Motor2_Con1_GPIO_Port, Motor2_Con1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Motor2_Con2_GPIO_Port, Motor2_Con2_GPIO_Port, GPIO_PIN_RESET);

	setSpeed(Motor1, 0);
	setSpeed(Motor2, 0);
}



void MotDrv_TakeDecision(OpenMV_ML_Data cameraData1, OpenMV_ML_Data cameraData2)
{
	(void)cameraData1;
	(void)cameraData2;
	if(i==100)
	{
		i=0;
	}

	else
	{
		i++;
	}
	MotDrv_GoFront(i);
	HAL_Delay(10);
	MotDrv_GoBack(0);
	MotDrv_TurnRight(0);
	MotDrv_TurnLeft(0);
	//MotDrv_Stay();

}



