#version 400 core

in vec3 position;
in vec3 normal;

out vec3 surfaceNormal;
out vec3 vectorTowardsLight;
out vec4 color;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

const vec3 light_direction = vec3(0.0, 0.0, 0.0);

void main()
{
	gl_Position = projectionMatrix * viewMatrix * vec4(position, 1.0);

	surfaceNormal = (vec4(normal, 0.0)).xyz;
	vectorTowardsLight = light_direction - position;
	color = vec4(position.y / 2, 0, 0, 1.0);
}