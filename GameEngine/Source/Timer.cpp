#include "Includes/Timer.h"

Timer::Timer() {
	_maxTime = 0;
	OnStart = nullptr;
	OnUpdating = nullptr;
	OnFinish = nullptr;
}

Timer::Timer(
	float maxTime,
	std::function<void()> StartFunc, 
	std::function<void()> UpdateFunc, 
	std::function<void()> FinishFunc)
{
	_maxTime = maxTime;

	OnStart = StartFunc;
	OnUpdating = UpdateFunc;
	OnFinish = FinishFunc;
}

Timer::~Timer()
{
}

void Timer::Tick(float dt)
{
	if (Enabled && Finished == false)
	{
		if (_currentTime < _maxTime) {
			if (_currentTime == 0.0f) { if (OnStart) { OnStart(); }	}
			else { if (OnUpdating) { OnUpdating(); } }

			_currentTime += dt;
		}
		else
		{
			if (OnFinish) { OnFinish(); }
			if (Repeating == false) { Finished = true; }
			
			_currentTime = 0.0f;
		}
	}
}

float Timer::Progress(void) const { return _currentTime / _maxTime; }
float Timer::RawProgress(void) const { return _maxTime - _currentTime; }

void Timer::Stop(void) { Enabled = false; }
void Timer::Play(void) { Enabled = true; }
void Timer::Reset(void) { _currentTime = 0.0f; }
void Timer::FullReset(void) { Finished = false; Reset(); }
void Timer::StopExecution(bool callFinishFunction = true) { 
	if (OnFinish && callFinishFunction == true) { OnFinish(); }
	Finished = true;
	Reset();
	Stop();
}

void Timer::UpdateMaxTime(int newMaxTime, bool triggerFunc){
	_maxTime = newMaxTime;
	Reset();
	if (triggerFunc == false) { return; }

	if (OnFinish) { OnFinish(); }
}