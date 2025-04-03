#pragma once
#include "GameObject.h"
#include <vector>
#include <unordered_set>
#include "raymath.h"

class SpatialGrid
{
public:
	SpatialGrid(int width, int height, int size);

	void clearGrid();
	void insert(GameObject* object);
	std::vector<GameObject*> getNearby(GameObject* object);

#ifdef DEBUG_MODE
	void drawDebugGrid();
#endif // DEBUG_MODE

private:
	int cols;
	int rows;
	int numCells;
	int cellSize;
	std::vector<std::unordered_set<GameObject*>> cells;
	int minCol;
	int maxCol;
	int minRow;
	int maxRow;

	int getCellIndex(int col, int rows) const;
	void obtainColRow(GameObject* object);
};