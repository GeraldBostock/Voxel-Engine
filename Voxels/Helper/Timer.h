#pragma once
#include <SDL.h>

class Timer
{
public:
	Timer();
	~Timer();

	void start();
	void stop();
	void pause();
	void unpause();

	Uint32 getTicks();

private:
	Uint32 m_startTicks;
	Uint32 m_pausedTicks;

	bool m_paused;
	bool m_started;
};

