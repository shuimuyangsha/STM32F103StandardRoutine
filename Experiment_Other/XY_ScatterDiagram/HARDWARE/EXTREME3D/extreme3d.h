#ifndef EXTREME3D_H
#define EXTREME3D_H

#include "sys.h"

typedef struct buttons{
	u8 getButtonsState;
	u8 setButtonsState;
}Buttons;

typedef struct slider{
	u16 getSliderState;
	u16 setSliderState;
}Slider;

typedef  struct joystick{
	u16 getJoystickState;
	u16 setjoystickState;
}Joystick;

typedef  struct point_of_view{
	short int getPointOfViewState;
	short int setPointOfViewState;
}PointOfView;

typedef  struct extreme3dStruct{
	Buttons buttons0;
	Buttons buttons1;
	Buttons buttons2;
	Buttons buttons3;
	Buttons buttons4;
	Buttons buttons5;
	Buttons buttons6;
	Buttons buttons7;
	Buttons buttons8;
	Buttons buttons9;
	Buttons buttons10;
	Buttons buttons11;

	Slider  slider0;
	Joystick joystickX;
	Joystick joystickY;
	Joystick joystickRotationZ;

	PointOfView pointOfView;
}Extreme3dStruct;

extern u16 Compass;

extern Extreme3dStruct extreme3d;

#endif // EXTREME3D_H
