#pragma once
#include <Windows.h>
#include <memory>
#include <string>
#include "Includes/GameEngine.h"
#include "Includes/Utils.h"
#include "Includes/FallingObject.h"
#include "Includes/Timer.h"

#pragma region Constructors & Destructor

GameEngine::GameEngine(void)
{
	_Matrix = new CharArray* [N_ROW];
	_TimeManager = new TimeManager(0.0016f);
	_ScoreManager = new ScoreManager(this, 2, 72);
	_DrawManager = new DrawManager();
	_InputManager = new InputManager();
	_CollisionManager = new CollisionManager(this);
}

GameEngine::~GameEngine(void)
{
	// Free the timer and other complex classes
	delete _TimeManager;
	delete _ScoreManager;
	delete _DrawManager;
	delete _InputManager;
	delete _CollisionManager;

	// Free the memory occupied by the matrix
	for (char c = 0; c < N_ROW; c++) { delete _Matrix[c]; }
	delete[] _Matrix;
}

#pragma endregion

#pragma region Non-Overwriteable Loop Related Functions 

void GameEngine::BeginLoop(void)
{
	if (!_initialized) { Initialize(); _initialized = true; }
	Start();
	while(EndGameFlag() == false)
	{
		UpdateInput();

		if (_TimeManager->ShouldExecuteNextFrame())		{
			Utils::ClearScreen();
			StoreUI();

			RootUpdate(_TimeManager->GetElapsedTime());
			RemoveFlaggedObjects();
			
			Draw();
		}
	}

	Cleanup();
}

void GameEngine::Initialize(void)
{
	// It's a byte since the game will never be past FF in horizontal
	// or vertical syze
	for (char row = 0; row < N_ROW; row++) {
		_Matrix[row] = new CharArray(N_COL);
	}

	// Add pressing exit key on input manager
	Input* input = _InputManager->RegisterInput(VK_ESCAPE);
	input->OnPress = [this]() { this->ExitKeyPressed = true; };
}

void GameEngine::RootUpdate(const float& dt)
{
	int* xPos = nullptr;
	int* yPos = nullptr;
	char* c = nullptr;

	for (int i = 0; i < ActiveObjects.size(); i++)
	{
		if (ActiveObjects.at(i)->SetForRemoval) { continue; }

		xPos = &ActiveObjects.at(i)->Position->X;
		yPos = &ActiveObjects.at(i)->Position->Y;
		c = ActiveObjects.at(i)->Letter;

		// Update and then check if it collided
		ActiveObjects.at(i)->Update(dt);
		_CollisionManager->Update(ActiveObjects.at(i));

		// Then store again the char with the modified values
		_Matrix[*yPos]->StoreValue(*xPos, *c);
	}

	Update(dt);
}

void GameEngine::RemoveFlaggedObjects(void)
{
	// Clear any GameObjects flagged for Removal
	for (int i = ActiveObjects.size() - 1; i >= 0; i--)
	{
		if (ActiveObjects.at(i)) {
			if (ActiveObjects.at(i)->SetForRemoval == true) {

				int xPos = ActiveObjects.at(i)->Position->X;
				int yPos = ActiveObjects.at(i)->Position->Y;

				OnObjectRemoved(ActiveObjects.at(i));

				// Check if any game object is in the position of the deleted object and write that instead
				if (ActiveObjects.size() != 0) {
					for (GameObject* c : ActiveObjects) {
						if (c->Position->X == xPos
							&& c->Position->Y == yPos) {
							_Matrix[yPos]->StoreValue(xPos, *c->Letter);
							break;
						}
					}
				}

				delete ActiveObjects.at(i);
				ActiveObjects.erase(ActiveObjects.begin() + i);
			}
		}
		else
		{
			ActiveObjects.erase(ActiveObjects.begin() + i);
		}
	}
}

void GameEngine::UpdateInput(void) {
	_InputManager->Check();
}

void GameEngine::Cleanup(void)
{
	// Free every object, then clear
	for (GameObject* obj : ActiveObjects) {	delete obj;	}
	ActiveObjects.clear();
	_ScoreManager->SetNewRecord();
	ExitKeyPressed = false;
}

void GameEngine::Draw(void)
{
	_DrawManager->Draw(_Matrix);
}

#pragma endregion 

#pragma region Game State

bool GameEngine::EndGameFlag(void) { return ExitKeyPressed || GameFinished(); }

#pragma endregion

#pragma region Matrix Related Methods

bool GameEngine::PositionIsCorner(const int& row, const int& col)
{
	bool rowAnswer = (row == 0 || row == N_ROW - 1);
	bool colAnswer = (col == 0 || col == N_COL - 1);

	return rowAnswer && colAnswer;
}

bool GameEngine::PositionIsEdge(const int& row, const int& col)
{
	bool isEdge = (col == 0 || col == N_COL - 1);

	return isEdge;
}

bool GameEngine::PositionIsTopOrBottom(const int& row, const int& col)
{
	bool isTopOrBottom = (row == 0 || row == N_ROW - 1);

	return isTopOrBottom;
}

void GameEngine::AddLineToMatrix(const int& row, const char& c)
{
	for (int i = 1; i < N_COL - 1; i++)	{
		_Matrix[row]->StoreValue(i, c);
	}
}


#pragma endregion

#pragma region Other Methods

void GameEngine::FlagObject(std::vector<int>* position, int i)
{
	int xPos = position->at(0);
	int yPos = position->at(1);

	_Matrix[yPos]->StoreValue(xPos, ' ');
	ActiveObjects.at(i)->SetForRemoval = true;
}

void GameEngine::StoreUI(void)
{
	for (char row = 0; row < N_ROW; row++) {
		for (char col = 0; col < N_COL; col++) {
			_Matrix[row]->StoreValue(col, ' ');

			if (PositionIsCorner(row, col)) { _Matrix[row]->StoreValue(col, UI_CORNER_CHAR); }
			else if (PositionIsEdge(row, col)) { _Matrix[row]->StoreValue(col, UI_SIDE_CHAR); }
			else if (PositionIsTopOrBottom(row, col)) { _Matrix[row]->StoreValue(col, UI_SECTION_CHAR); }
			else if (row == 2 || row == 3) { _Matrix[row]->StoreValue(col, UI_SECTION_CHAR); }
		}
	}

	_Matrix[1]->StoreString(_ScoreManager->ScoreStringIndex, "SCORE: ");
	_Matrix[1]->StoreString(_ScoreManager->RecordStringIndex, "RECORD: ");

	_Matrix[1]->StoreString(_ScoreManager->ScoreIndex, std::to_string(_ScoreManager->GetScore()));
	_Matrix[1]->StoreString(_ScoreManager->RecordIndex, std::to_string(_ScoreManager->GetRecord()));

	CreateAdditionalUI();
}

bool GameEngine::IsCharOnPosition(std::vector<int>* position, bool checkingGameObject, GameObject* object, char c)
{
	for (int i = 0; i < ActiveObjects.size(); i++)
	{
		GameObject* obj = ActiveObjects.at(i);

		if (obj == object) { continue; }
		if (*obj->Letter == c) {
			if (*obj->Position == *object->Position) {
				return true;
			}
		}
	}

	return false;
}

bool GameEngine::IsCharOnPosition(int& xPos, int& yPos, bool checkingGameObject, GameObject* object, char c)
{
	if (checkingGameObject == true) {
		for (int i = 0; i < ActiveObjects.size(); i++)
		{
			GameObject* obj = ActiveObjects.at(i);

			if (obj == object) { continue; }
			if (*obj->Letter == c) {
				if (obj->Position->X == xPos
					&& obj->Position->Y == yPos) {
					return true;
				}
			}
		}
	}
	else {
		return _Matrix[yPos]->GetValue(xPos) == c;
	}

	return false;
}

void GameEngine::AddGameObject(GameObject* object, bool insert, int index)
{
	if (insert) { ActiveObjects.insert(ActiveObjects.begin() + index, object); }
	else { ActiveObjects.push_back(object); }
}

#pragma endregion

#pragma region Abstract Methods

// Game Loop Related
void GameEngine::Start(void) {}
void GameEngine::Update(const float& dt) { }
void GameEngine::OnObjectRemoved(GameObject* pointer) { }
	

// Game State Related
bool GameEngine::GameFinished(void) { return false; }

// UI Related
void GameEngine::CreateAdditionalUI(void) {}

#pragma endregion