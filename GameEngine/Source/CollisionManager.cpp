#include "Includes/CollisionManager.h"
#include "Includes/GameEngine.h"

CollisionManager::CollisionManager(GameEngine* engine)
{
	Engine = engine;
}

CollisionManager::~CollisionManager()
{

}

// This is okay for a low amount of objects
void CollisionManager::Update(GameObject* objectA)
{
	if (objectA->SetForRemoval == true) { return; }

	for (GameObject* objectB : Engine->ActiveObjects) {
		if (objectB->SetForRemoval == true) { continue; }
		if (objectB == objectA) { continue; }
		if (*objectA->Position != *objectB->Position) { continue; }

		TriggerCollision(objectA, objectB);
		break;
	}
}

void CollisionManager::TriggerCollision(GameObject* objectA, GameObject* objectB)
{
	objectA->OnCollision(objectB);
	objectB->OnCollision(objectA);
}
