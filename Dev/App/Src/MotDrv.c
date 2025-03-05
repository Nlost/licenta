#include "Motdrv.h"

static void MotDrv_GoFront()
{

}

static void MotDrv_GoBack()
{

}

static void MotDrv_TurnRight()
{

}

static void MotDrv_TurnLeft()
{

}

static void MotDrv_Stay()
{

}



void MotDrv_TakeDecision(OpenMV_ML_Data cameraData1, OpenMV_ML_Data cameraData2)
{
	(void)cameraData1;
	(void)cameraData2;
	MotDrv_GoFront();
	MotDrv_GoBack();
	MotDrv_TurnRight();
	MotDrv_TurnLeft();
	MotDrv_Stay();
}



