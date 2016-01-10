#ifndef __TIMER_H__
#define __TIMER_H__

class Timer
{
public:
	void SetTimer(float time, bool reset = true);
	void ResetTimer();
	bool IsTimerExpired(bool reset = false);
	void Increment(float amount);
	void Pause();
	void Resume();
	bool IsPaused();

public:
	float timerTime;
	float timerDuration;
	bool paused;
};
#endif