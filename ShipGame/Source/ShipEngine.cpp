#include "Includes/ShipEngine.h"
#include "Includes/Ship.h"
#include "Includes/EnemyShip.h"
#include "tinyxml2.h"
#include <Windows.h>
#include <string> 
#include <fstream>

using namespace tinyxml2;

ShipEngine::ShipEngine(){ 
	_WaveManager = new WaveManager(this);
}

ShipEngine::~ShipEngine()
{
	delete _WaveManager;
}

void ShipEngine::Initialize(void)
{
	GameEngine::Initialize();

	_Matrix[N_ROW - 4]->BGColor = 0;  _Matrix[N_ROW - 4]->FGColor = 3;
	_Matrix[N_ROW - 3]->BGColor = 0;  _Matrix[N_ROW - 3]->FGColor = 3;
	_Matrix[N_ROW - 2]->BGColor = 0;  _Matrix[N_ROW - 2]->FGColor = 3;

	// Create the file to save the record if it doesn't exist
	std::ifstream inFile("./Data/Record.txt");
	if(inFile.good() == false) { 
		std::ofstream saveFile("./Data/Record.txt", std::ios::out);
		saveFile << "0";
	}
	else
	{
		int previousScore;
		inFile >> previousScore;
		_ScoreManager->OverrideRecord(previousScore);
	}
}

void ShipEngine::Start(void)
{
	AddGameObject(new Ship(this, 1, SHIP_CHAR, 8, N_ROW / 2));

	// Load wave data
	_WaveManager->Start();
}

void ShipEngine::Update(const float& dt)
{
	_WaveManager->Update(dt);
}

void ShipEngine::OnObjectRemoved(GameObject* pointer)
{
	if (EnemyShip* ship = dynamic_cast<EnemyShip*>(pointer)) {
		if (ship->Position->X <= 1) { _ScoreManager->IncreaseScore(ship->GetPoints() * -1); }
		else { _ScoreManager->IncreaseScore(ship->GetPoints()); }	
	}
	else if(dynamic_cast<Ship*>(pointer)) {
		ExitKeyPressed = true;
	}
}

bool ShipEngine::GameFinished(void)
{
	return _WaveManager->Finished == true && NoEnemiesLeft() || ExitKeyPressed;
}

void ShipEngine::Cleanup(void)
{
	GameEngine::Cleanup();

	std::ofstream file;
	file.open("./Data/Record.txt");
	file << _ScoreManager->GetRecord();
	file.close();
}

void ShipEngine::CreateAdditionalUI(void)
{
	_Matrix[1]->StoreString(30, "NEXT WAVE IN: ");
	if(_WaveManager->Finished == false) { _Matrix[1]->StoreString(44, std::to_string((int)_WaveManager->GetRawTimeLeft())); }
	else { _Matrix[1]->StoreString(44, "NONE");	}
}

// Additional methods

bool ShipEngine::NoEnemiesLeft(void)
{
	for (GameObject* obj : ActiveObjects) {
		if (dynamic_cast<EnemyShip*>(obj)) {
			return false;
		}
	}

	return true;
}
