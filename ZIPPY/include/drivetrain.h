#pragma once 

float tovolt(float percentage);


/////master control functions//////
int DriveTrainControls();
int IntakeControls();
int OutakeControls();
int DrivePTOcontrols();
int Loadercontrols();
int liftercontrols();
int Hookcontrols();



/////slave control functions//////
int slavePTOcontrol();
int slaveWINGcontrol();
int slaveLOADERcontrol();
