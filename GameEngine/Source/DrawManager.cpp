#include "Includes/DrawManager.h"
#include "Includes/CharArray.h"
#include "Includes/GameEngine.h"

DrawManager::DrawManager()
{
	console = GetStdHandle(STD_OUTPUT_HANDLE);
}

DrawManager::~DrawManager(){}

void DrawManager::Draw(CharArray** _Matrix)
{
	for (char row = 0; row < GameEngine::N_ROW; row++) {

		for (char col = 0; col < GameEngine::N_COL; col++) {
			if (col == 1) { SetColor(_Matrix[row]->FGColor, _Matrix[row]->BGColor); }
			else if (col == GameEngine::N_COL - 1) { SetColor(0, 7); }

			std::cout << _Matrix[row]->GetValue(col);
		}

		

		std::cout << "\n";
	}
}

void DrawManager::SetColor(int textColor, int bgColor)
{
	SetConsoleTextAttribute(console, (textColor << 4) | bgColor);
}