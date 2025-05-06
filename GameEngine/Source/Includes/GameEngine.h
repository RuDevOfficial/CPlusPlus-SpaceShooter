#pragma once
#include <memory>
#include "CharArray.h"
#include "TimeManager.h"
#include "GameObject.h"
#include "ScoreManager.h"
#include "DrawManager.h"
#include "InputManager.h"
#include "CollisionManager.h"

class GameEngine
{
private:
	TimeManager* _TimeManager = nullptr;
	DrawManager* _DrawManager = nullptr;
	CollisionManager* _CollisionManager = nullptr;

	bool _initialized = false;

	// Matrix related methods
	bool PositionIsCorner(const int& row, const int& col);
	bool PositionIsEdge(const int& row, const int& col);
	bool PositionIsTopOrBottom(const int& row, const int& col);

	// Game Loop related methods
	void RootUpdate(const float& dt);
	void UpdateInput(void);
	void Draw(void);	void RemoveFlaggedObjects(void);

	// Game State Condition methods
	bool EndGameFlag(void);

	// Useful Methods
	void FlagObject(std::vector<int>* position, int i);
	void StoreUI(void);

protected:
	virtual void Initialize(void);
	virtual void Start(void) = 0;
	virtual void Update(const float& dt) = 0;
	virtual void OnObjectRemoved(GameObject* pointer) = 0;
	virtual bool GameFinished(void) = 0;
	virtual void Cleanup(void);
	virtual void CreateAdditionalUI(void) = 0;

public:
	InputManager* _InputManager = nullptr;

	std::vector<GameObject*> ActiveObjects;

	bool ExitKeyPressed = false;

	const static int N_COL = 96;
	const static int N_ROW = 32;
	const static int ROW_CHECK = 30;

	const static char UI_CORNER_CHAR = '0';
	const static char UI_SIDE_CHAR = 'I';
	const static char UI_SECTION_CHAR = '-';

	void BeginLoop(void);

	bool IsCharOnPosition(std::vector<int>* position, bool checkingGameObject, GameObject* object, char c);
	bool IsCharOnPosition(int& xPos, int& yPos, bool checkingGameObject, GameObject* object, char c);

	void AddGameObject(GameObject* object, bool insert = false, int index = 0);

	GameEngine(void);
	~GameEngine(void);

protected:
	ScoreManager* _ScoreManager = nullptr;
	CharArray** _Matrix = nullptr;
	void AddLineToMatrix(const int& row, const char& c);
};