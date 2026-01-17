#pragma once 

float tovolt(float percentage);


/////master control functions//////
int DriveTrainControls();
int IntakeControls();
int IntakerevControls();
int OutakeControls();
int OutakerevControls();
int slowOutakeControls();
int DrivePTOcontrols();
int Parkcontrols();
int Loadercontrols();
int liftercontrols();
int Hookcontrols();



/////slave control functions//////
int slavePTOcontrol();
int slaveWINGcontrol();
int slaveLOADERcontrol();
