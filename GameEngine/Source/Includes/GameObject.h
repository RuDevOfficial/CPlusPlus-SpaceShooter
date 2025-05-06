#pragma once
#include <vector>
#include "Vector2.h"

class GameObject
{
private:
	GameObject();

public:
	Vector2* Position;
	char* Letter = nullptr;
	bool SetForRemoval = false;

	void SetPosition(int xPos, int yPos);

	GameObject(char c, int xPos, int yPos);
	~GameObject();

	// Abstract Methods
	virtual void Update(const float& dt) = 0;
	virtual void OnCollision(GameObject* collidedObject) = 0;
};

