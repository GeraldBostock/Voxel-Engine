#include "Camera.h"



Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::move(bool* keys)
{
	float mouseSensitivity = 0.07f;
	float movementSpeed = 0.08f;

	if (keys[SDLK_w])
	{
		m_position.z -= (movementSpeed * (float)cos(m_yaw * M_PI / 180));
		m_position.x += (movementSpeed * (float)sin(m_yaw * M_PI / 180));
		//For flight mode
		m_position.y += (movementSpeed * (float)sin(-m_pitch * M_PI / 180));
	}
	if (keys[SDLK_s])
	{
		m_position.z += (movementSpeed * (float)cos(m_yaw * M_PI / 180));
		m_position.x -= (movementSpeed * (float)sin(m_yaw * M_PI / 180));
		//For flight mode
		m_position.y -= (movementSpeed * (float)sin(-m_pitch * M_PI / 180));
	}
	if (keys[SDLK_a])
	{
		m_position.z += (movementSpeed * (float)cos((m_yaw + 90) * M_PI / 180));
		m_position.x -= (movementSpeed * (float)sin((m_yaw + 90) * M_PI / 180));
	}
	if (keys[SDLK_d])
	{
		m_position.z -= (movementSpeed * (float)cos((m_yaw + 90) * M_PI / 180));
		m_position.x += (movementSpeed * (float)sin((m_yaw + 90) * M_PI / 180));
	}
}

void Camera::updateCamera(SDL_Event e)
{
	if (e.type == SDL_MOUSEMOTION)
	{
		if (e.motion.yrel < 0 && m_pitch >= -90)
		{
			m_pitch -= 0.2f;
		}
		if (e.motion.yrel > 0 && m_pitch <= 90)
		{
			m_pitch += 0.2f;
		}
		if (e.motion.xrel < 0)
		{
			m_yaw -= 0.2f;
		}
		if (e.motion.xrel > 0)
		{
			m_yaw += 0.2f;
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