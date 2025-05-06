#pragma once
#include <queue>
#include "tinyxml2.h"
#include "Timer.h"
#include "Wave.h"
class ShipEngine;

class WaveManager
{
public:
	ShipEngine* Engine = nullptr;
	Timer* _Timer = nullptr;
	std::queue<Wave>* Waves = new std::queue<Wave>();

	void Update(const float& dt);
	void Start();

	void SpawnEnemies();
	float GetRawTimeLeft();

	WaveManager(ShipEngine* engine);
	~WaveManager();

	bool Finished = false;

private:
	WaveManager();
};