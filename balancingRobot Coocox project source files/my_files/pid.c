#include "pid.h"

float pid(PIDStruct* CurrentPIDStruct) {

	float pError = CurrentPIDStruct->currentError;
	float iError = CurrentPIDStruct->currentError + CurrentPIDStruct->integral;
	CurrentPIDStruct->integral = iError;
	float dError = CurrentPIDStruct->currentError - CurrentPIDStruct->oldError;

	float output = (CurrentPIDStruct->kp*pError) + (CurrentPIDStruct->ki*iError) + (CurrentPIDStruct->kd*dError);

	CurrentPIDStruct->oldError = CurrentPIDStruct->currentError;

	if(output>CurrentPIDStruct->maxRange){

		output=CurrentPIDStruct->maxRange;

	}else if (output < CurrentPIDStruct->minRange){

		output=CurrentPIDStruct->minRange;
	}

	return output;

}

void PIDStructInit(PIDStruct* InitializedPIDStruct){

	InitializedPIDStruct->kp = 0;
	InitializedPIDStruct->ki = 0;
	InitializedPIDStruct->kd = 0;

	InitializedPIDStruct->oldError = 0;
	InitializedPIDStruct->currentError = 0;

	InitializedPIDStruct->workingPoint = 90;

	InitializedPIDStruct->integral = 0;

	InitializedPIDStruct->maxRange = 65534;		// max pulse width with current configutration
	InitializedPIDStruct->minRange = -65534;	// minus represents opposite direction

}

