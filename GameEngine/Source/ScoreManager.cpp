#include "Includes/ScoreManager.h"
#include "Includes/GameEngine.h"

ScoreManager::ScoreManager()
{
    
}

ScoreManager::ScoreManager(GameEngine* engine, int scoreStringIndex, int recordStringIndex)
{
    Engine = engine;
    ScoreStringIndex = scoreStringIndex;
    RecordStringIndex = recordStringIndex;

    ScoreIndex = scoreStringIndex + 7;
    RecordIndex = recordStringIndex + 8;
}

ScoreManager::~ScoreManager()
{
}

void ScoreManager::SetNewRecord()
{
    _record = _score;
    _score = 0;
}

void ScoreManager::OverrideRecord(int record)
{
    _record = record;
}

int& ScoreManager::GetScore(void){ return _score; }
int& ScoreManager::GetRecord(void) { return _record; }

void ScoreManager::IncreaseScore(int amount) { _score += amount; }
