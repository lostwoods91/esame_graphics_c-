#include "Grid.h"
#include "RenderingEngine.h"
#include "PhysicsEngine.h"
#include "glew.h"
#include <iostream>

const float Grid::blocks_size = 0.8f;
const float Grid::horizontal_padding = 0.2f;
const float Grid::vertical_padding = horizontal_padding;

void Grid::generateRandomGrid()
{
	const float block_width = Block::getUnscaledWidth() * blocks_size;
	const float block_height = Block::getUnscaledHeight() * blocks_size;
	const float offsetH = block_width / 2;
	const float offsetV = block_height / 2;

	for (int i = 0; i < capacity; ++i)
	{
		int r = i / cols;
		int c = i % cols;
		blocks[i].setTransform(Transform(
			vec3(c * (block_width + horizontal_padding) + offsetH, -(r * (block_height + vertical_padding) + offsetV), 0), quat(1, 0, 0, 0), blocks_size));
		blocks[i].initAsRandomBlock();
		blocks[i].setCollider(Collider(
			block_width * blocks[i].getGlobalScale(), block_height * blocks[i].getGlobalScale()));
	}
	alive_blocks = capacity;
}

void Grid::init(int rows, int cols)
{
	this->rows = rows;
	this->cols = cols;

	capacity = rows * cols;
	alive_blocks = capacity;

	blocks = new Block[capacity];
	for (int i = 0; i < capacity; ++i)
	{
		RenderingEngine::getInstance().registerRenderObject(&blocks[i]);
		PhysicsEngine::getInstance().registerCollidableObject(&blocks[i]);
		blocks[i].setParent(this);
	}
	
	width = Block::getUnscaledWidth() * blocks_size * cols + horizontal_padding * (cols - 1);
	height = Block::getUnscaledHeight() * blocks_size * rows + vertical_padding * (rows - 1);
}

// debug: render a point at the pivot
void Grid::render() const
{
	//glPointSize(5.0f);
	//glColor3f(1, 0, 0);
	//glBegin(GL_POINTS);
	//glVertex2f(0, 0);
	//glEnd();
}

Grid::Grid(Transform t, int rows, int cols/*, Level level*/) : GameObject(t)
{
	init(rows, cols);
}

Grid::Grid(int rows, int cols) : GameObject()
{
	init(rows, cols);
}

float Grid::getWidth() const
{
	return getGlobalScale() * width;
}

float Grid::getHeight() const
{
	return getGlobalScale() * height;
}

int Grid::getNumberOfAliveBlocks() const
{
	return alive_blocks;
}

void Grid::changeBlocksDisposition()
{
	for (int i = 0; i < capacity; ++i)
	{
		int rand_pos = rand() % capacity;
		Transform temp = blocks[i].getTransform();
		blocks[i].setTransform(blocks[rand_pos].getTransform());
		blocks[rand_pos].setTransform(temp);
	}
}

void Grid::decrementBlockNumber()
{
	alive_blocks--;
	std::cout << "Distruggi ancora " << alive_blocks << " blocchi per vincere!" << std::endl;
}

Grid::~Grid()
{
	for (int i = 0; i < capacity; ++i)
	{
		RenderingEngine::getInstance().unregisterRenderObject(&blocks[i]);
		PhysicsEngine::getInstance().unregisterCollidableObject(&blocks[i]);
	}
	delete[] blocks;
}
