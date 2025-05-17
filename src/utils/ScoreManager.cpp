#include "ScoreManager.h"

using json = nlohmann::json;

ScoreManager& ScoreManager::instance()
{
	static ScoreManager inst;
	return inst;
}

void ScoreManager::addScore(const std::string& name, int score, int level)
{
	time_t thisTime = time(nullptr);
	std::tm local_tm;
	localtime_s(&local_tm, &thisTime);

	char timeBuffer[32];
	strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%dT%H:%M:%S", &local_tm);

	ScoreEntry entry = { name, score, level, timeBuffer };
	scores.push_back(entry);
	sortScore();
	save();
}

void ScoreManager::save(const std::string& path)
{
	json j;
	for (const auto& score : scores)
	{
		j.push_back({
			{"name", score.name},
			{"score", score.score},
			{"level", score.level},
			{"timestamp", score.timeStamp}
		});
	}

	std::ofstream file(path);
	file << j.dump(4);
}

void ScoreManager::load(const std::string& path)
{
	scores.clear();
	std::ifstream file(path);
	if (!file.is_open()) return;

	json j;
	try 
	{
		file >> j;
		for (const auto& entry : j)
		{
			ScoreEntry score;
			score.name = entry.value("name", "Player");
			score.score = entry.value("score", 0);
			score.level = entry.value("level", 0);
			score.timeStamp = entry.value("timestamp", "");
			scores.push_back(score);
		}
	}
	catch (const std::exception& e)
	{

	}
}

void ScoreManager::sortScore()
{
	std::sort(scores.begin(), scores.end(), [](const ScoreEntry& a, const ScoreEntry& b) 
	{
		return b.score < a.score;
	});
}
