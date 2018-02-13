#include "Camera.h"



Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::move(bool* keys, float time)
{
	float mouseSensitivity = 0.07f;
	float movementSpeed = 35.f;

	if (keys[SDLK_w])
	{
		m_position.z -= (movementSpeed * (float)cos(m_yaw * M_PI / 180)) * (float)cos(-m_pitch * M_PI / 180) * time;
		m_position.x += (movementSpeed * (float)sin(m_yaw * M_PI / 180)) * (float)cos(-m_pitch * M_PI / 180) * time;
		//For flight mode
		m_position.y += (movementSpeed * (float)sin(-m_pitch * M_PI / 180)) * time;
	}
	if (keys[SDLK_s])
	{
		m_position.z += (movementSpeed * (float)cos(m_yaw * M_PI / 180)) * (float)cos(-m_pitch * M_PI / 180) * time;
		m_position.x -= (movementSpeed * (float)sin(m_yaw * M_PI / 180)) * (float)cos(-m_pitch * M_PI / 180) * time;
		//For flight mode
		m_position.y -= (movementSpeed * (float)sin(-m_pitch * M_PI / 180)) * time;
	}
	if (keys[SDLK_a])
	{
		m_position.z += (movementSpeed * (float)cos((m_yaw + 90) * M_PI / 180)) * time;
		m_position.x -= (movementSpeed * (float)sin((m_yaw + 90) * M_PI / 180)) * time;
	}
	if (keys[SDLK_d])
	{
		m_position.z -= (movementSpeed * (float)cos((m_yaw + 90) * M_PI / 180)) * time;
		m_position.x += (movementSpeed * (float)sin((m_yaw + 90) * M_PI / 180)) * time;
	}
}

void Camera::updateCamera(SDL_Event e)
{
	if (e.type == SDL_MOUSEMOTION)
	{
		if (e.motion.yrel < 0 && m_pitch >= -90)
		{
			m_pitch -= 0.4f;
		}
		if (e.motion.yrel > 0 && m_pitch <= 90)
		{
			m_pitch += 0.4f;
		}
		if (e.motion.xrel < 0)
		{
			m_yaw -= 0.4f;
		}
		if (e.motion.xrel > 0)
		{
			m_yaw += 0.4f;
		}
	}
}

glm::vec3 Camera::getPosition()
{
	return m_position;
}

float Camera::getPitch()
{
	return m_pitch;
}

float Camera::getYaw()
{
	return m_yaw;
}

float Camera::getRoll()
{
	return m_roll;
}