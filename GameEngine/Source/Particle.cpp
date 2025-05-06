#include "Includes/Particle.h"


Particle::Particle(float lifetime, char c, int xPos, int yPos) : GameObject(c, xPos, yPos)
{
	_lifetime = lifetime;
}

Particle::~Particle()
{
}

void Particle::Update(const float& dt)
{
	if (_currentLifetime < _lifetime) { _currentLifetime += dt; }
	else { SetForRemoval = true; }
}

void Particle::OnCollision(GameObject* collidedObject)
{
	
}