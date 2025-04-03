#include "SpatialGrid.h"

SpatialGrid::SpatialGrid(int width, int height, int size)
{
	cellSize = size;
	cols = (width + cellSize - 1) / cellSize;
	rows = (height + cellSize - 1) / cellSize;
	numCells = cols * rows;
	cells = std::vector<std::unordered_set<GameObject*>>(numCells);
}

void SpatialGrid::clearGrid()
{
	for (std::unordered_set<GameObject*>& cell : cells)
	{
		cell.clear();
	}
}

void SpatialGrid::insert(GameObject* object)
{
	obtainColRow(object);
	for (int i = minRow; i <= maxRow; i++)
	{
		for (int j = minCol; j <= maxCol; j++)
		{
			int index = getCellIndex(j, i);
			cells[index].insert(object);
		}
	}
}

std::vector<GameObject*> SpatialGrid::getNearby(GameObject* object)
{
	obtainColRow(object);

	std::unordered_set<GameObject*> objects;
	for (int i = minRow; i <= maxRow; i++)
	{
		for (int j = minCol; j <= maxCol; j++)
		{
			int index = getCellIndex(j, i);
			objects.insert(cells[index].begin(), cells[index].end());
		}
	}

	objects.erase(object);

	return std::vector<GameObject*>(objects.begin(), objects.end());
}

int SpatialGrid::getCellIndex(int col, int rows) const
{
	return col + cols * rows;
}

void SpatialGrid::drawDebugGrid()
{
	Color gridColor = RED;

	int gridWidth = cols * cellSize;
	int gridHeight = rows * cellSize;

	for (int i = 0; i <= cols; i++)
	{
		int x = i * cellSize;
		DrawLine(x, 0, x, gridHeight, gridColor);
	}

	for (int j = 0; j <= rows; j++)
	{
		int y = j * cellSize;
		DrawLine(0, y, gridWidth, y, gridColor);
	}
}

void SpatialGrid::obtainColRow(GameObject* object)
{
	Rectangle hitbox = object->getHitbox();
	minCol = hitbox.x / cellSize;
	maxCol = (hitbox.x + hitbox.width) / cellSize;
	minRow = hitbox.y / cellSize;
	maxRow = (hitbox.y + hitbox.height) / cellSize;

	minCol = Clamp(minCol, 0, cols - 1);
	maxCol = Clamp(maxCol, 0, cols - 1);
	minRow = Clamp(minRow, 0, rows - 1);
	maxRow = Clamp(maxRow, 0, rows - 1);
}
