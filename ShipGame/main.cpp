#include "Source/Includes/ShipEngine.h"

int main()
{
	ShipEngine* Engine = new ShipEngine();

	char answer = 'Y';
	while (answer == 'Y')
	{
		Engine->BeginLoop();
		std::cout << "\033[2J\033[H";
		std::cout << "Would you like to play again? Y or N: ";
		std::cin >> answer;
		answer = std::toupper(answer);
	}
}