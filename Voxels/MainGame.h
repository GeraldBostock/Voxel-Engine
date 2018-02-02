#pragma once
#include <SDL.h>

#include "Helper\Timer.h"
#include "Display.h"
#include "Renderer.h"
#include "Shaders\StaticShader.h"
#include "Entities\Camera.h"
#include "Terrain.h"

#define FRAME_VALUES 20
#define FPS_INTERVAL 1.0

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:
	Display m_display;
	Renderer m_renderer;

	bool m_running;
	Uint32 m_frametimes[FRAME_VALUES];
	Uint32 m_frametimelast;
	Uint32 m_framecount;

	float m_framespersecond;

	void fpsInit();
	void fpsThink();
};

