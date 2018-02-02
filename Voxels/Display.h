#pragma once
#include <stdio.h>
#include <SDL.h>
#include <glew.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

class Display
{
public:
	Display();
	~Display();

	void createDisplay();
	void updateDisplay();
	void closeDisplay();

private:
	SDL_Window* m_window;
	SDL_GLContext m_glContext;
};

