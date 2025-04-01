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

private:
	int cols;
	int rows;
	int numCells;
	int cellSize;
	std::vector<std::unordered_set<GameObject*>> cells;

	int getCellIndex(int col, int rows) const;

	int minCol;
	int maxCol;
	int minRow;
	int maxRow;

	void obtainColRow(GameObject* object);
};