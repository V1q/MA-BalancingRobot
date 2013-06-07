typedef struct
{

	float kp; // proportional gain of PID controller
	float ki; // integral gain of PID controller
	float kd; // derivative gain od PID controller

	float oldError;		// error from previous steering loop
	float currentError; // actual error

	float workingPoint; // desired angle

	float integral; // integrated error

	float maxRange;
	float minRange;

}PIDStruct;


float pid(PIDStruct* CurrentPIDStruct);
void PIDStructInit(PIDStruct* InitializedPIDStruct);
