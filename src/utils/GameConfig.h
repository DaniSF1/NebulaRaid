#pragma once

class GameConfig
{
public:
	static GameConfig& instance()
	{
		static GameConfig instance;
		return instance;
	}

	void setResolution(int width, int height)
	{
		screenWidth = width;
		screenHeight = height;
	}

	int screenWidth = 720;
	int screenHeight = 1280;
	int gridCellSize = 128;

private:
	GameConfig() = default;
};