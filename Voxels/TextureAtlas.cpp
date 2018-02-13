#include "TextureAtlas.h"



TextureAtlas::TextureAtlas()
{
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
}


TextureAtlas::~TextureAtlas()
{
	IMG_Quit();
}

GLuint TextureAtlas::loadTexture(const std::string& filePath)
{
	SDL_Surface* surface;
	surface = IMG_Load(filePath.c_str());
	if (surface == NULL)
		printf("Could not load texture: %s\n", IMG_GetError());

	int Mode = GL_RGBA;

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	/*glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);*/

	glTexImage2D(GL_TEXTURE_2D, 0, Mode, surface->w, surface->h, 0, Mode, GL_UNSIGNED_BYTE, surface->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	return texture;
}

glm::vec2* TextureAtlas::getUv(blockTextures texture)
{
	glm::vec2* uvs = new glm::vec2[6];

	float xOffset = getXOffset(texture);
	float yOffset = getYOffset(texture);

	for (int i = 0; i < 6; i++)
	{
		uvs[0] = glm::vec2(xOffset, yOffset);
		uvs[1] = glm::vec2(xOffset, yOffset + 0.25f);
		uvs[2] = glm::vec2(xOffset + 0.25f, yOffset);
		uvs[3] = glm::vec2(xOffset + 0.25f, yOffset);
		uvs[4] = glm::vec2(xOffset, yOffset + 0.25f);
		uvs[5] = glm::vec2(xOffset + 0.25f, yOffset + 0.25f);
	}

	return uvs;
}

float TextureAtlas::getXOffset(blockTextures index)
{
	int i = index;
	int column = i % TEXTURES_IN_ROW;
	return (float)column / (float)TEXTURES_IN_ROW;
}

float TextureAtlas::getYOffset(blockTextures index)
{
	int i = index;
	int row = i / TEXTURES_IN_ROW;
	return (float)row / (float)TEXTURES_IN_ROW;
}
