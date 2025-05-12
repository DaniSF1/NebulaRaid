#pragma once
#include "raylib.h"
#include "raymath.h"
#include <string>
#include <unordered_map>

class AudioManager
{
public:
	static AudioManager& instance();

	void init();
	void update();
	void unload();

	void playSound(const std::string& name);
	void playMusic(const std::string& path);
	void stopMusic();

	float getSoundVolume() const { return soundVolume; }
	void setSoundVolume(float volume);
	float getMusicVolume() const { return musicVolume; }
	void setMusicVolume(float volume);

private:
	AudioManager() = default;
	~AudioManager() = default;

	std::unordered_map<std::string, Sound> soundEffects;
	Music currentMusic;
	bool musicLoaded = false;

	float soundVolume = 0.1f;
	float musicVolume = 0.1f;
};