#version 400 core

in vec3 position;
in vec3 normal;
in vec2 uv;

out vec3 surfaceNormal;
out vec3 vectorTowardsLight;
out vec4 color;
out vec2 texCoords;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

const vec3 light_direction = vec3(150.0, 500.0, 150.0);

void main()
{
	gl_Position = projectionMatrix * viewMatrix * vec4(position, 1.0);
	texCoords = uv;

	surfaceNormal = (vec4(normal, 0.0)).xyz;
	vectorTowardsLight = light_direction - position;
	color = vec4(position.y / 20, position.y / 20, position.y / 20, 1.0);
}