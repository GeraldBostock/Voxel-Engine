#pragma once
#include <glm.hpp>
#include <SDL.h>
#include <stdio.h>

class Camera
{
public:
	Camera();
	~Camera();

	glm::vec3 getPosition();
	float getPitch();
	float getYaw();
	float getRoll();

	void updateCamera(SDL_Event e);
	void move(bool* keys, float time);

private:
	glm::vec3 m_position = glm::vec3(0.0f);
	float m_pitch = 0.0f;
	float m_yaw = 0.0f;
	float m_roll = 0.0f;
};

