#include "TextureManager.h"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_BMP
#include "stb_image.h"

TextureManager & TextureManager::getInstance()
{
	static TextureManager instance;
	return instance;
}

GLuint TextureManager::loadTexture(char const * filename)
{
	int w;
	int h;
	int comp;
	unsigned char* image = stbi_load(filename, &w, &h, &comp, 0);

	if (image == nullptr)
	{
		printf("Could not read texture from source file");
		return 0;
	}

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	if (comp == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	else if (comp == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image);

	return textureID;
}

void TextureManager::loadTextures()
{
	getInstance().block_textures[0] = loadTexture("..\\res\\brick.bmp");
	getInstance().block_textures[1] = loadTexture("..\\res\\sea.bmp");
	getInstance().ball_texture = loadTexture("..\\res\\ball.bmp");
}
