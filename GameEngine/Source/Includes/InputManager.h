#pragma once
#include "Input.h"
#include <vector>

class InputManager
{
private:
	std::vector<Input*>* Inputs = nullptr;

public:
	void Check(void);

	Input* RegisterInput(int keyValue);
	Input* GetInput(int keyValue);

	InputManager(void);
	~InputManager(void);
};

