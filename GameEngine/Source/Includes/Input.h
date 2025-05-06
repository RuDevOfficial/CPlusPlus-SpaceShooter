#pragma once
#include <functional>

struct Input
{
private:
	Input(void);
	bool isPressed = false;

public:
	int KeyValue = 0;
	
	void Check(void);

	std::function<void()> OnPress;
	std::function<void()> OnHold;
	std::function<void()> OnRelease;

	Input(int number);
	~Input(void);
};

