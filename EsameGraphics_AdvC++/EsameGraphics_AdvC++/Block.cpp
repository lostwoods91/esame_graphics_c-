#include "Block.h"
#include "TextureManager.h"
#include "PhysicsEngine.h"
#include "GameManager.h"
#include "RenderingEngine.h"

const vec3 Block::colors[Block::nColors] = { vec3(1,0,0), vec3(0,1,0), vec3(0,0,1), vec3(1,1,1), vec3(0,0,0) };

const float Block::width = 1;
const float Block::height = 0.5f;


void Block::init()
{
	RenderingEngine::getInstance().registerRenderObject(&ps);
	PhysicsEngine::getInstance().registerMovableObject(&ps);
	ps.setParent(this);
}

void Block::initAsColorBlock(int colorIdx)
{
	this->color = colors[colorIdx];
	textureID = 0;
	type = COLOR_BLOCK;
	alive = true;
	//Red, blue and black blocks are destroyed in 1 hit, while green and white blocks in 2 hits
	hp = colorIdx % 2 + 1;
	hasParticleSystem = true;
	ps.init(color);
	ps.setActive(false);
}

void Block::initAsTextureBlock(int textureIdx)
{
	color = vec3();
	this->textureID = TextureManager::getInstance().block_textures[textureIdx];
	type = TEXTURE_BLOCK;
	alive = true;
	//Brick blocks are destroyed in 1 hit, while sea blocks in 2 hits
	hp = textureIdx % 2 + 1;
	hasParticleSystem = false;
	ps.setActive(false);
}

void Block::initAsRandomBlock()
{
	int random = rand() % (nColors + nTextures);
	if (random < nColors)
		initAsColorBlock(rand() % nColors);
	else
		initAsTextureBlock(rand() % TextureManager::n_block_textures);
}


void Block::renderColorBlock() const
{
	glColor3f(color.x, color.y, color.z);
	glBegin(GL_QUADS);
	glVertex2f(-width / 2, height / 2);
	glVertex2f(width / 2, height / 2);
	glVertex2f(width / 2, -height / 2);
	glVertex2f(-width / 2, -height / 2);
	glEnd();
}

void Block::renderTextureBlock() const
{
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(-width / 2, height / 2);
	glTexCoord2f(0.0, 1.0); glVertex2f(-width / 2, -height / 2);
	glTexCoord2f(1.0, 1.0); glVertex2f(width / 2, -height / 2);
	glTexCoord2f(1.0, 0.0); glVertex2f(width / 2, height / 2);
	glEnd();
	glFlush();
	glDisable(GL_TEXTURE_2D);
}

void Block::render() const
{
	if (!alive) return;
	switch (type)
	{
	case COLOR_BLOCK:
		renderColorBlock();
		break;
	case TEXTURE_BLOCK:
		renderTextureBlock();
		break;
	}
}

Block::Block()
{
	init();
	initAsRandomBlock();
	//initAsRandomTextureBlock();
}

Block::Block(Transform t) : GameObject(t)
{
	init();
	initAsRandomBlock();
	//initAsRandomTextureBlock();
}


Block::~Block()
{
	RenderingEngine::getInstance().unregisterRenderObject(&ps);
	PhysicsEngine::getInstance().unregisterMovableObject(&ps);
}

vec3 Block::getColor() const
{
	return color;
}

GLuint Block::getTextureID() const
{
	return textureID;
}

Block_Type Block::getType() const
{
	return type;
}

float Block::getUnscaledWidth()
{
	return width;
}

float Block::getUnscaledHeight()
{
	return height;
}

float Block::getWidth() const
{
	return width * getScale();
}

float Block::getHeight() const
{
	return height * getScale();
}

void Block::onCollision(GameObject * other)
{
	if (alive)
	{
		if (--hp == 0)
		{
			if (hasParticleSystem)
			{
				ps.setActive(true);
			}
			alive = false;
			collider.setAlive(false);
			GameManager::getInstance().getGrid()->decrementBlockNumber();
			if (GameManager::getInstance().getGrid()->getNumberOfAliveBlocks() == 0)
				GameManager::getInstance().onWin();
		}
	}
}
