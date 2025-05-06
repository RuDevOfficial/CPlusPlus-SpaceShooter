#pragma once
class GameEngine;

class ScoreManager
{
private:
    GameEngine* Engine = nullptr;

    int _score = 0;
    int _record = 0;

    ScoreManager(void);

public:
    // 2 and 70 are recommended
    int ScoreStringIndex = 0;
    int RecordStringIndex = 0;

    // 14 and 78 are recommended
    int ScoreIndex = 0;
    int RecordIndex = 0;

    void SetNewRecord(void);
    void OverrideRecord(int record);
    void IncreaseScore(int amount);

    int& GetScore(void);
    int& GetRecord(void);

    ScoreManager(GameEngine* engine, int scoreStringIndex, int recordStringIndex);
    ~ScoreManager();
};
