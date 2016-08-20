#pragma once
#include "GameObject.h"
#include "glew.h"
#include "ParticleSystem.h"

/*
idea 1:
classe padre: Block
classi figlie: ColorBlock, TextureBlock

pro: ognuna ha la sua implementazione di render();
contro: la grid non può avere un array di Block che sia cache friendly;
si può avere un array di puntatori Block*, ma ciascun Block verrebbe creato in un punto casuale dello heap

idea 2:
unica classe Block

pro: cache friendly! array di Block in stack;
contro: devo distinguere internamente se è un blocco colorato o un blocco con texture

scelgo la seconda alternativa

*/

enum Block_Type
{
	COLOR_BLOCK,
	TEXTURE_BLOCK,

	//RED_BLOCK,
	//GREEN_BLOCK,
	//BLUE_BLOCK,
	//WHITE_BLOCK,
	//BLACK_BLOCK,
	//BRICK_BLOCK,
	//SEA_BLOCK,				static_cast<Block_Type>(rand() % (N_BLOCK_TYPES - 1))
	//RANDOM_BLOCK,

	N_BLOCK_TYPES
};

// in model space, a block is a rectangle of dimensions width x height
class Block : public GameObject
{
private:
	vec3 color;
	GLuint textureID;
	Block_Type type;
	bool alive;
	int hp;
	bool hasParticleSystem;
	ParticleSystem ps;

	void init();

	void initAsColorBlock(int colorIdx);
	void initAsTextureBlock(int textureIdx);

	void renderColorBlock() const;
	void renderTextureBlock() const;

	static const int nColors = 5;
	static const vec3 colors[nColors];
	static const int nTextures = 2;
	static const float width;
	static const float height;

protected:
	virtual void render() const;

public:
	Block();
	Block(Transform t);
	virtual ~Block();

	void initAsRandomBlock();

	vec3 getColor() const;
	GLuint getTextureID() const;
	Block_Type getType() const;
	float getWidth() const;
	float getHeight() const;

	static float getUnscaledWidth();
	static float getUnscaledHeight();

	virtual void onCollision(GameObject* other);
};

