#include <Windows.h>
#include "Includes/Ship.h"
#include "Includes/Projectile.h"
#include "Particle.h"
#include "Includes/EnemyShip.h"

#pragma region Core

Ship::Ship(ShipEngine* engine, int shootTime, char c, int xPos, int yPos) : GameObject(c, xPos, yPos)
{
	Engine = engine;

	Input* input = nullptr;

	input = engine->_InputManager->RegisterInput(VK_UP);
	input->OnPress = [this]() {this->ChangeDirection(0, -1); };
	input->OnHold = [this]() {this->ChangeDirection(0, -1); };
	input->OnRelease = [this]() {this->ChangeDirection(0, 0); };

	input = engine->_InputManager->RegisterInput(VK_DOWN);
	input->OnPress = [this]() {this->ChangeDirection(0, 1); };
	input->OnHold = [this]() {this->ChangeDirection(0, 1); };
	input->OnRelease = [this]() {this->ChangeDirection(0, 0); };

	_shootTimer = shootTime;
}

Ship::~Ship()
{

}

void Ship::OnCollision(GameObject* collidedObject)
{
	if (dynamic_cast<EnemyShip*>(collidedObject)) {
		SetForRemoval = true;
	}
}

void Ship::Update(const float& dt)
{
	Position->X += Direction.X;
	Position->Y += Direction.Y;

	if (Position->Y < 4) { Position->Y += 1; }
	else if (Position->Y > ShipEngine::N_ROW - 2) { Position->Y -= 1; }

	if (Position->Y == ShipEngine::N_ROW - 4
		&& Direction.Y == 1) {
		Engine->AddGameObject(new Particle(0.5f, '¦', Position->X, Position->Y - Direction.Y));
	}

	// Shooting projectiles
	if (_currentShootTimer < _shootTimer) { _currentShootTimer += dt; }
	else { _currentShootTimer = 0.0f; Shoot(); }
}

#pragma endregion

#pragma region Custom Methods

void Ship::ChangeDirection(int xDirPos, int yDirPos)
{
	Direction.X = xDirPos;
	Direction.Y = yDirPos;
}

void Ship::Shoot(void)
{
	Beep(523, 5);

	Engine->AddGameObject(
		new Projectile(
			'-', 
			Position->X + 1, 
			Position->Y)
	);
}

#pragma endregion