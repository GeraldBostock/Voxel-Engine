#include "Display.h"



Display::Display()
{
}


Display::~Display()
{
}

void Display::createDisplay()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	m_window = SDL_CreateWindow("Voxels", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
	SDL_GL_CreateContext(m_window);

	GLenum status = glewInit();
	if (status != GLEW_OK)
	{
		printf("Could not initialize glew.\n");
	}
}

void Display::updateDisplay()
{
	SDL_GL_SwapWindow(m_window);
}

void Display::closeDisplay()
{
	SDL_GL_DeleteContext(m_glContext);

	SDL_DestroyWindow(m_window);
	m_window = NULL;

	SDL_Quit();
}
