#pragma once
#include "GameObject.h"

class FallingObject : public GameObject
{
private:
	float _currentfallTime = 0.0f;
	float _maxFallTime = 0.0f;

	FallingObject();

public:
	bool HasShield = false;

	void Update(const float& dt) override;

	FallingObject(char c, int xPos, int yPos, float fallTime, bool hasShield);
	~FallingObject();
};

