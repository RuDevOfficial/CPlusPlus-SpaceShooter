#include "Includes/Projectile.h"
#include "Includes/ShipEngine.h"
#include "Particle.h"

Projectile::Projectile(char c, int xPos, int yPos)
	: GameObject(c, xPos, yPos)
{
}

Projectile::~Projectile()
{

}

void Projectile::Update(const float& dt)
{
	if (SetForRemoval == false) {
		if (Position->X >= ShipEngine::N_COL - 3) { SetForRemoval = true; }
		SetPosition(Position->X + 1, Position->Y);
	}
}

void Projectile::OnCollision(GameObject* collidedObject)
{
	if (dynamic_cast<Particle*>(collidedObject)) { return; }

	SetForRemoval = true;
}
