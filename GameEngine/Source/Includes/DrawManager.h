#pragma once
#include "CharArray.h"
#include "Windows.h"

class DrawManager
{
private:
	HANDLE console = nullptr;

public:
	DrawManager();
	~DrawManager();

	void Draw(CharArray** _Matrix);
	void SetColor(int textColor, int bgColor);
};

