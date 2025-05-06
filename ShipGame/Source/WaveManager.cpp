#include "Includes/WaveManager.h"
#include "Includes/EnemyShip.h"
#include "Includes/ShipEngine.h"
#include "tinyxml2.h"

WaveManager::WaveManager(ShipEngine* engine)
{
	Engine = engine;

	_Timer = new Timer(
		0,
		[this]() { this->SpawnEnemies(); },
		nullptr,
		[this]()
		{
			Waves->pop();

			if (this->Waves->size() == 0) {
				this->Finished = true;
				this->_Timer->Stop();
				return;
			}

			int newWaveTime = Waves->front().Runtime;
			this->_Timer->UpdateMaxTime(newWaveTime);
			this->_Timer->Play();
		});

	_Timer->Repeating = true;
}

WaveManager::~WaveManager()
{
	delete _Timer;
	delete Waves;
}

void WaveManager::Start() {
	tinyxml2::XMLDocument doc;
	doc.LoadFile("./Data/WaveData.xml");

	tinyxml2::XMLElement* waveData = doc.FirstChildElement("WAVEDATA");
	if (waveData) {
		tinyxml2::XMLElement* wave = waveData->FirstChildElement("WAVE");
		while (wave)
		{
			float time = wave->FirstChildElement("TIME")->FloatText();
			Wave newWave(time);

			// loop stuff

			tinyxml2::XMLElement* enemiesSection = wave->FirstChildElement("ENEMIES");
			if (enemiesSection) {
				tinyxml2::XMLElement* enemy = enemiesSection->FirstChildElement("ENEMY");
				while (enemy) {

					EnemyShip* enemyShip = new EnemyShip(
						Engine,
						enemy->IntAttribute("health"),
						enemy->FloatAttribute("moveTime"),
						enemy->IntAttribute("points"),
						*enemy->Attribute("character"),
						ShipEngine::N_COL - 2,
						enemy->IntAttribute("position")
					);

					newWave.AddEnemy(enemyShip);

					enemy = enemy->NextSiblingElement("ENEMY");
				}
			}

			Waves->push(newWave);

			// Go to the next
			wave = wave->NextSiblingElement("WAVE");
		}
	}

	Finished = false;

	_Timer->UpdateMaxTime(Waves->front().Runtime, false);
	_Timer->Play();
}

void WaveManager::Update(const float& dt) {
	_Timer->Tick(dt);
}

void WaveManager::SpawnEnemies() {
	int size = Waves->front().Objects.size();
	for (int i = 0; i < size; i++)	{

		GameObject* pointer = Waves->front().Objects.front();
		Waves->front().Objects.pop();

		Engine->AddGameObject(pointer);
	}
}

float WaveManager::GetRawTimeLeft() {
	if (Finished == false) { return _Timer->RawProgress(); }
	return 0;
}
