#pragma once
#include "GameObject.h"
class GameEngine;

class CollisionManager
{
public:
	void Update(GameObject* objectA);

	CollisionManager(GameEngine* engine);
	~CollisionManager();

private:
	CollisionManager();
	GameEngine* Engine = nullptr;

	void TriggerCollision(GameObject* objectA, GameObject* objectB);
};

