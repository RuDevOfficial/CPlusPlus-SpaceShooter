#include "Includes/InputManager.h"

InputManager::InputManager()
{
	Inputs = new std::vector<Input*>();
}

InputManager::~InputManager()
{
	for (int i = 0; i < Inputs->size(); i++) {
		if (Inputs->at(i)) {
			delete Inputs->at(i);
		}
	}

	if (Inputs) { delete Inputs; }
}

void InputManager::Check(void)
{
	for (int i = 0; i < Inputs->size(); i++) {
		Inputs->at(i)->Check();
	}
}

Input* InputManager::RegisterInput(int keyValue)
{
	Input* newInput = new Input(keyValue);
	Inputs->push_back(newInput);
	return newInput;
}

Input* InputManager::GetInput(int keyValue)
{
	for (int i = 0; i < Inputs->size(); i++) {
		if (Inputs->at(i)->KeyValue == keyValue) {
			return Inputs->at(i);
		}
	}
}
