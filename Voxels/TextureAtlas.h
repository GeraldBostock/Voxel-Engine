#pragma once
#include <string>
#include <glew.h>
#include <SDL_image.h>
#include <glm.hpp>

#include "Cube.h"

const int TEXTURES_IN_ROW = 4;

class TextureAtlas
{
public:
	TextureAtlas();
	~TextureAtlas();

	GLuint loadTexture(const std::string& filePath);
	glm::vec2* getUv(blockTextures texture);

private:
	float getXOffset(blockTextures index);
	float getYOffset(blockTextures index);
};

