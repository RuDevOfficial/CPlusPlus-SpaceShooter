#include "Includes/EnemyShip.h"
#include "Includes/ShipEngine.h"
#include <Windows.h>
#include "Particle.h"

EnemyShip::EnemyShip(
	ShipEngine* engine, int health, float moveTime, int points,
	char c, int xPos, int yPos) : GameObject(c, xPos, yPos) {
	
	Engine = engine;

	_health = health;
	_charRef = c;
	_points = points;
	
	_timer = std::make_unique<Timer>(
		moveTime,
		nullptr,
		nullptr,
		[this]() { this->Move(); }
	);

	_flickTimer = std::make_unique<Timer>(
		0.12f,
		[this]() { *this->Letter = ' '; },
		nullptr,
		[this]() { *this->Letter = _charRef; }
	);

	_timer.get()->Play();
	_timer.get()->Repeating = true;
}

EnemyShip::~EnemyShip() {

}

void EnemyShip::Update(const float& dt)
{
	_timer.get()->Tick(dt);
	_flickTimer.get()->Tick(dt);
}

void EnemyShip::OnCollision(GameObject* collidedObject)
{
	if (dynamic_cast<EnemyShip*>(collidedObject)) { return; }

	// There was a bug where the explosion particle would also kill other ships close to the exploding one
	// If you wanna make it harder for you just uncomment the lines below
	
	// if (dynamic_cast<Particle*>(collidedObject)) { return; }

	// and comment this one
	if (dynamic_cast<Particle*>(collidedObject)) { _health = 0; }

	_flickTimer.get()->FullReset();
	_flickTimer.get()->Play();
	_health -= 1;
	
	if (_health <= 0) {

		for (char row = -1; row < 2; row++)	{
			for (char col = -1; col < 2; col++)
			{
				Engine->AddGameObject(new Particle(
					0.15f,
					'*',
					Position->X + col,
					Position->Y + row
				));
			}
		}

		SetForRemoval = true;
	}
}

void EnemyShip::Move(void) {
	SetPosition(Position->X - 1, Position->Y);
	if (Position->X == 0) {	SetForRemoval = true; }
}