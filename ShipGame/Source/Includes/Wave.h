#pragma once
#include <queue>
#include "GameObject.h"
#include "tinyxml2.h"

struct Wave
{
public:
	Wave(float time);
	~Wave();
	std::queue<GameObject*> Objects;

	void AddEnemy(GameObject* enemy);
	float Runtime = 0;

private:
	Wave();

};
