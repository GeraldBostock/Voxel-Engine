#version 400 core

in vec3 surfaceNormal;
in vec3 vectorTowardsLight;
in vec4 color;

out vec4 out_color;

const vec3 light_color = normalize(vec3(1.0, 1.0, 1.0));

void main()
{
	//Normalize our vectors so the size of these vector do not effect the dot product value. Dot product value should be between 0 and 1
	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitLightVector = normalize(vectorTowardsLight);

	float nDotProduct = dot(unitNormal, unitLightVector);
	float brightness = max(nDotProduct, 0.35);
	
	vec3 diffuse = brightness * light_color;

	out_color = vec4(diffuse, 1.0) * color;
}