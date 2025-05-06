#pragma once
#include "GameObject.h"

class Projectile : public GameObject
{
public:
	Projectile(char c, int xPos, int yPos);
	~Projectile();

	void Update(const float& dt);
	void OnCollision(GameObject* collidedObject);
};

