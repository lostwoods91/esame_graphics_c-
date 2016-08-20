#pragma once
#include "glew.h"

class TextureManager
{
private:
	TextureManager() {};

public:
	TextureManager(TextureManager const&) = delete;
	void operator=(TextureManager const&) = delete;
	static TextureManager& getInstance();

	static const int n_block_textures = 2;
	GLuint block_textures[n_block_textures];
	GLuint ball_texture;

	static GLuint loadTexture(char const * filename);
	static void loadTextures();
};

