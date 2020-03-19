#ifndef TIMER_H
#define TIMER_H
#include "SDL.h"
class Timer
{
private:
	static Timer* ptr;
	unsigned int startTicks;
	unsigned int elapsedTime;
	float deltaTime;
	float timeScale;
	Timer();
	~Timer();
public:
	static Timer* getPTR();
	static void Release();
	void Reset();
	float DeltaTime();
	void TimeScale(float timeScale);
	float TimeScale();
	void Update();



};

#endif // !TIMER_H
