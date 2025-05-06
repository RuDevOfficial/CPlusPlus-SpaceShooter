#pragma once
#include "GameEngine.h"
#include "WaveManager.h"

class ShipEngine : public GameEngine
{
public:
	const char SHIP_CHAR = '>';

	ShipEngine();
	~ShipEngine();


private:
	WaveManager* _WaveManager = nullptr;

	void Initialize(void) override;
	void Start(void) override;
	void Update(const float& dt) override;
	void OnObjectRemoved(GameObject* pointer) override;
	bool GameFinished(void) override;
	void Cleanup(void) override;
	void CreateAdditionalUI(void) override;

	// Additonal methods

	bool NoEnemiesLeft(void);
};