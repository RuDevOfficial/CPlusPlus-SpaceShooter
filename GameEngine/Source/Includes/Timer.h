#pragma once
#include <iostream>
#include <functional>

class Timer
{
private:

	float _currentTime = 0.0f;
	float _maxTime = 0.0f;

	std::function<void()> OnStart = nullptr;
	std::function<void()> OnUpdating = nullptr;
	std::function<void()> OnFinish = nullptr;

public:
	Timer();
	Timer(float maxTime,
		std::function<void()> StartFunc = nullptr,
		std::function<void()> UpdateFunc = nullptr,
		std::function<void()> FinishFunc = nullptr);
	~Timer();

	std::string Name = "";
	bool Enabled = false;
	bool Repeating = false;
	bool Finished = false;

	void Tick(float dt);
	float Progress(void) const;
	float RawProgress(void) const;

	void Stop(void);
	void Play(void);
	void Reset(void);
	void FullReset(void);
	void StopExecution(bool callFinishFunction);

	void UpdateMaxTime(int newMaxTime, bool triggerFunc = false);
};