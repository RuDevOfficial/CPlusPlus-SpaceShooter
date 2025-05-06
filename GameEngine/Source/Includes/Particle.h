#pragma once
#include "GameObject.h"

class Particle : public GameObject
{
private:
	float _currentLifetime = 0.0f;
	float _lifetime = 0.0f;

	Particle();

public:

	void Update(const float& dt) override;
	void OnCollision(GameObject* collidedObject) override;

	Particle(float lifetime, char c, int xPos, int yPos);
	~Particle();
};

