#include <iostream>
#include "Includes/FallingObject.h"

void FallingObject::Update(const float& dt)
{
	if (_currentfallTime < _maxFallTime) {
		_currentfallTime += dt;
	}
	else { 
		_currentfallTime = 0.0f;
		SetPosition(Position->X, Position->Y);
	}
}

FallingObject::FallingObject(char c, int xPos, int yPos, float fallTime, bool hasShield) : GameObject(c, xPos, yPos)
{
	_maxFallTime = fallTime;
	HasShield = hasShield;
}

FallingObject::~FallingObject()
{

}
