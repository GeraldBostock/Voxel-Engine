#include "MainGame.h"



MainGame::MainGame()
{
}


MainGame::~MainGame()
{
}

void MainGame::run()
{
	m_running = true;
	m_display.createDisplay();

	StaticShader shader("Shaders/vertexShader.vert", "Shaders/fragmentShader.frag");
	StaticShader waterShader("Shaders/water.vert", "Shaders/water.frag");
	Camera camera;
	bool keysHeld[323] = { false };

	glm::mat4 projMatrix = Maths::CreateProjectionMatrix(WINDOW_WIDTH, WINDOW_HEIGHT, 70, 0.1f, 1000.0f);
	shader.start();
	shader.loadProjectionMatrix(projMatrix);
	shader.stop();

	waterShader.start();
	waterShader.loadProjectionMatrix(projMatrix);
	waterShader.stop();

	Terrain terrain;
	unsigned char* heightMap = terrain.GenerateTerrain();

	Chunk chunk(heightMap);

	/*Mesh mesh;
	mesh.generateMesh(heightMap);*/
	//GLuint texture = mesh.loadTexture();
	GLuint texture = m_atlas.loadTexture("res/mcAtlas.png");

	Timer timer;
	timer.start();

	fpsInit();
	while (m_running)
	{
		float time = m_stepTimer.getTicks() / 1000.f;
		m_stepTimer.start();

		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
			{
				m_running = false;
				m_display.closeDisplay();
			}

			if (e.type == SDL_KEYDOWN && e.key.keysym.sym < 323)
			{
				keysHeld[e.key.keysym.sym] = true;
			}
			if (e.type == SDL_KEYUP && e.key.keysym.sym < 323)
			{
				keysHeld[e.key.keysym.sym] = false;
			}

			camera.updateCamera(e);
		}

		camera.move(keysHeld, time);

		shader.start();
		shader.loadViewMatrix(camera);

		m_renderer.prepare();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);


		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		m_renderer.renderMesh(chunk.getTerrainMesh());

		shader.stop();

		waterShader.start();
		waterShader.loadViewMatrix(camera);
		
		glDisable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		m_renderer.renderMesh(chunk.getWaterMesh());
		waterShader.stop();
		glDisable(GL_BLEND);


		m_display.updateDisplay();
		fpsThink();
		if (timer.getTicks() > FPS_INTERVAL * 1000)
		{
			printf("FPS: %f\n", m_framespersecond);
			timer.start();
		}
	}
}

void MainGame::fpsInit()
{
	memset(m_frametimes, 0, sizeof(m_frametimes));
	m_framecount = 0;
	m_framespersecond = 0;
	m_frametimelast = SDL_GetTicks();
}

void MainGame::fpsThink()
{
	Uint32 frametimesindex;
	Uint32 getticks;
	Uint32 count;
	Uint32 i;

	frametimesindex = m_framecount % FRAME_VALUES;

	getticks = SDL_GetTicks();

	m_frametimes[frametimesindex] = getticks - m_frametimelast;

	m_frametimelast = getticks;

	m_framecount++;

	if (m_framecount < FRAME_VALUES) {

		count = m_framecount;

	}
	else {

		count = FRAME_VALUES;

	}

	m_framespersecond = 0;
	for (i = 0; i < count; i++) {

		m_framespersecond += m_frametimes[i];

	}

	m_framespersecond /= count;

	m_framespersecond = 1000.f / m_framespersecond;
}
