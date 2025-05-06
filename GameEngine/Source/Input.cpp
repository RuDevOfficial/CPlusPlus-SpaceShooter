#include "Includes/Input.h"
#include "Windows.h"

Input::Input(int number) : KeyValue(number){}
Input::~Input(void){}

void Input::Check(void)
{
	if ((GetKeyState(KeyValue) & 0x8000) && isPressed == false)	{
		if (OnPress) { OnPress(); }
		isPressed = true;
	}
	else if (GetKeyState(KeyValue) & 0x8000) {
		if (OnHold) { OnHold(); }
	}
	else {
		if (isPressed == true)
		{
			if (OnRelease) { OnRelease(); }
			isPressed = false;
		}
	}
}