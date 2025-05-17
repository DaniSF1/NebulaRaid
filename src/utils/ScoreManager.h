#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <ctime>
#include "../external/json.hpp"

struct ScoreEntry 
{
	std::string name;
	int score;
	int level;
	std::string timeStamp;
};

class ScoreManager
{
public:
	static ScoreManager& instance();

	void addScore(const std::string& name, int score, int level);
	void save(const std::string& path = "json/scores.json");
	void load(const std::string& path = "json/scores.json");
	void sortScore();

private:
	ScoreManager() = default;
	~ScoreManager() = default;

	std::vector<ScoreEntry> scores;
};