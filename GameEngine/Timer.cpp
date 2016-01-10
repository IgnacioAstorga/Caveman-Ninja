#include "Timer.h"

void Timer::SetTimer(float time, bool reset)
{
	timerTime = time;
	if (reset)
		ResetTimer();
}

void Timer::ResetTimer()
{
	timerDuration = 0.0f;
}

bool Timer::IsTimerExpired(bool reset)
{
	bool expired = timerDuration >= timerTime;
	if (expired && reset)
		timerDuration -= timerTime;
	return expired;
}

void Timer::Increment(float amount)
{
	timerDuration += amount;
}

void Timer::Pause()
{
	paused = true;
}

void Timer::Resume()
{
	paused = false;
}

bool Timer::IsPaused()
{
	return paused;
}
