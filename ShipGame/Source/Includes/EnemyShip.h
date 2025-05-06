#pragma once
#include "GameObject.h"

#include "Timer.h"
#include <memory>
class ShipEngine;

class EnemyShip : public GameObject
{
public:
	EnemyShip(ShipEngine* engine,
		int health, float moveTime, int points,
		char c, int xPos, int yPos);
	~EnemyShip();

	void Update(const float& dt) override;
	void OnCollision(GameObject* collidedObject) override;

	void Move(void);
	int GetPoints(void) const { return _points; }

private:
	int _charRef = ' ';
	int _health = 1;
	int _points = 1;

	ShipEngine* Engine = nullptr;

	std::unique_ptr<Timer> _timer = nullptr;
	std::unique_ptr<Timer> _flickTimer = nullptr;

	EnemyShip();
};

