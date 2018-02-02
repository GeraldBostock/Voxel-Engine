#include "Timer.h"



Timer::Timer()
{
	m_startTicks = 0;
	m_pausedTicks = 0;

	m_started = 0;
	m_paused = 0;
}


Timer::~Timer()
{
}

void Timer::start()
{
	m_started = true;
	m_paused = false;

	m_startTicks = SDL_GetTicks();
	m_pausedTicks = 0;
}

void Timer::stop()
{
	m_started = false;
	m_paused = false;

	m_startTicks = 0;
	m_pausedTicks = 0;
}

void Timer::pause()
{
	m_paused = true;

	m_pausedTicks = SDL_GetTicks() - m_startTicks;
	m_startTicks = 0;
}

void Timer::unpause()
{
	if (m_started && m_paused)
	{
		m_paused = false;
		m_startTicks = SDL_GetTicks() - m_pausedTicks;

		m_pausedTicks = 0;
	}
}

Uint32 Timer::getTicks()
{
	Uint32 time = 0;
	
	if (m_started)
	{
		if (m_paused)
		{
			time = m_pausedTicks;
		}
		else
		{
			time = SDL_GetTicks() - m_startTicks;
		}
	}

	return time;
}
