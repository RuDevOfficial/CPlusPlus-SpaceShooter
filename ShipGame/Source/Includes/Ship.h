#pragma once
#include "GameObject.h"
#include "ShipEngine.h"
#include "Vector2.h"

class Ship : public GameObject
{
private:
	Vector2 Direction;
	ShipEngine* Engine = nullptr;

	float _currentShootTimer = 0.0f;
	float _shootTimer = 0.0f;

public:
	void Update(const float& dt);
	void OnCollision(GameObject* collidedObject);

	Ship(ShipEngine* engine, int shootTime, char c, int xPos, int yPos);
	~Ship();

	// Custom Methods
	void ChangeDirection(int xDirPos, int yDirPos);
	void Shoot(void);
};

