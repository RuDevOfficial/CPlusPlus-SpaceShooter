#include "Includes/Wave.h"

Wave::Wave(float time) : Runtime(time)
{

}

Wave::~Wave()
{
}

void Wave::AddEnemy(GameObject* enemy)
{
	Objects.push(enemy);
}
