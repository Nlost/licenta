#include "Motdrv.h"


static void setSpeed(Motor_Select motor, uint32_t Speed)
{
	switch(motor)
	{
	case FrontLeft:
		HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_1);
		TIM4->CCR1 = Speed;
		HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
		break;
	case FrontRight:
		HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_2);
		TIM4->CCR2 = Speed;
		HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
		break;
	case BackLeft:
		HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
		TIM4->CCR3 = Speed;
		HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
		break;
	case BackRight:
		HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_4);
		TIM4->CCR4 = Speed;
		HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
		break;
	default:
		(void)Speed;
		break;
	}
}


static void setDirection(Motor_Select motor, Motor_Direction direction)
{
	switch(motor)
		{
		case FrontLeft:
			if(direction == Back)
			{
				HAL_GPIO_WritePin(Left_GPIO_Port, FrontLeft_Con1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(Left_GPIO_Port, FrontLeft_Con2_Pin, GPIO_PIN_RESET);
			}
			else if(direction == Front)
			{
				HAL_GPIO_WritePin(Left_GPIO_Port, FrontLeft_Con1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(Left_GPIO_Port, FrontLeft_Con2_Pin, GPIO_PIN_SET);
			}
			else if(direction == Stop)
			{
				HAL_GPIO_WritePin(Left_GPIO_Port, FrontLeft_Con1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(Left_GPIO_Port, FrontLeft_Con2_Pin, GPIO_PIN_RESET);
			}
			break;
		case FrontRight:
			if(direction == Back)
			{
				HAL_GPIO_WritePin(Right_GPIO_Port, FrontRight_Con1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(Right_GPIO_Port, FrontRight_Con2_Pin, GPIO_PIN_RESET);
			}
			else if(direction == Front)
			{
				HAL_GPIO_WritePin(Right_GPIO_Port, FrontRight_Con1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(Right_GPIO_Port, FrontRight_Con2_Pin, GPIO_PIN_SET);
			}
			else if(direction == Stop)
			{
				HAL_GPIO_WritePin(Right_GPIO_Port, FrontRight_Con1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(Right_GPIO_Port, FrontRight_Con2_Pin, GPIO_PIN_RESET);
			}
			break;
		case BackLeft:
			if(direction == Back)
			{
				HAL_GPIO_WritePin(Left_GPIO_Port, BackLeft_Con1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(Left_GPIO_Port, BackLeft_Con2_Pin, GPIO_PIN_RESET);
			}
			else if(direction == Front)
			{
				HAL_GPIO_WritePin(Left_GPIO_Port, BackLeft_Con1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(Left_GPIO_Port, BackLeft_Con2_Pin, GPIO_PIN_SET);
			}
			else if(direction == Stop)
			{
				HAL_GPIO_WritePin(Left_GPIO_Port, BackLeft_Con1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(Left_GPIO_Port, BackLeft_Con2_Pin, GPIO_PIN_RESET);
			}
			break;
		case BackRight:
			if(direction == Back)
			{
				HAL_GPIO_WritePin(Right_GPIO_Port, BackRight_Con1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(Right_GPIO_Port, BackRight_Con2_Pin, GPIO_PIN_RESET);
			}
			else if(direction == Front)
			{
				HAL_GPIO_WritePin(Right_GPIO_Port, BackRight_Con1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(Right_GPIO_Port, BackRight_Con2_Pin, GPIO_PIN_SET);
			}
			else if(direction == Stop)
			{
				HAL_GPIO_WritePin(Right_GPIO_Port, BackRight_Con1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(Right_GPIO_Port, BackRight_Con2_Pin, GPIO_PIN_RESET);
			}
			break;
		default:
			(void)direction;
			break;
		}
}

static void MotDrv_GoFront(uint32_t speed)
{
	setSpeed(FrontLeft, speed);
	setSpeed(FrontRight, speed);
	setSpeed(BackLeft, speed);
	setSpeed(BackRight, speed);

	setDirection(FrontLeft, Front);
	setDirection(FrontRight, Front);
	setDirection(BackLeft, Front);
	setDirection(BackRight, Front);
}

static void MotDrv_GoBack(uint32_t speed)
{
	setSpeed(FrontLeft, speed);
	setSpeed(FrontRight, speed);
	setSpeed(BackLeft, speed);
	setSpeed(BackRight, speed);

	setDirection(FrontLeft, Back);
	setDirection(FrontRight, Back);
	setDirection(BackLeft, Back);
	setDirection(BackRight, Back);
}

static void MotDrv_TurnRight(uint32_t speed)
{
	setDirection(FrontLeft, Front);
	setDirection(FrontRight, Front);
	setDirection(BackLeft, Front);
	setDirection(BackRight, Front);

	setSpeed(FrontLeft, 0);
	setSpeed(FrontRight, speed);
	setSpeed(BackLeft, speed);
	setSpeed(BackRight, 0);
}

static void MotDrv_TurnLeft(uint32_t speed)
{
	setDirection(FrontLeft, Back);
	setDirection(FrontRight, Back);
	setDirection(BackLeft, Back);
	setDirection(BackRight, Back);

	setSpeed(FrontLeft, 0);
	setSpeed(FrontRight, speed);
	setSpeed(BackLeft, speed);
	setSpeed(BackRight, 0);


}

static void MotDrv_Stay()
{
	setSpeed(FrontLeft, 0);
	setSpeed(FrontRight, 0);
	setSpeed(BackLeft, 0);
	setSpeed(BackRight, 0);

	setDirection(FrontLeft, Stop);
	setDirection(FrontRight, Stop);
	setDirection(BackLeft, Stop);
	setDirection(BackRight, Stop);
}

void MotDrv_TakeDecision(OpenMV_ML_Data cameraData1, OpenMV_ML_Data cameraData2)
{
    if(cameraData1.camera_x != 0 && cameraData2.camera_x != 0)
    {
    	int avgX = (cameraData1.camera_x + cameraData2.camera_x) / 2;
    	int avgY = (cameraData1.camera_y + cameraData2.camera_y) / 2;

    	int offsetX = avgX - CENTER_X;
    	int offsetY = avgY - CENTER_Y;

    	if(offsetY < -Y_TOLERANCE)
    	{
    		printf("Go Front\n");
    		MotDrv_GoBack(30000);
    	}else if(offsetY > Y_TOLERANCE)
    	{
    		printf("Go Back\n");
    		MotDrv_GoFront(40000);
    	}else
    	{
    		if(offsetX < -X_TOLERANCE)
    		{
    			MotDrv_TurnLeft(50000);
    		}else if(offsetX > X_TOLERANCE)
    		{
    			MotDrv_TurnRight(50000);
    		}else
    		{
    			MotDrv_Stay();
    		}
    	}
    }
}



