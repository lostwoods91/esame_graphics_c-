#pragma once
#include "Block.h"

// pivot is at up left corner
class Grid : public GameObject
{
private:
	int rows;
	int cols;
	int capacity;
	int alive_blocks;
	Block* blocks;
	float width;
	float height;

	void init(int rows, int cols);

protected:
	virtual void render() const;
public:
	Grid(Transform t, int rows, int cols);
	Grid(int rows, int cols);
	virtual ~Grid();

	void generateRandomGrid();

	float getWidth() const;
	float getHeight() const;
	int getNumberOfAliveBlocks() const;

	void changeBlocksDisposition();
	void decrementBlockNumber();

	virtual void doPhysicStep() {};

	static const float blocks_size;
	static const float vertical_padding;
	static const float horizontal_padding;
};

