#include "AudioManager.h"

AudioManager& AudioManager::instance()
{
	static AudioManager inst;
	return inst;
}

void AudioManager::init()
{
	InitAudioDevice();

    soundEffects["death"] = LoadSound("assets/sound/death.wav");
    soundEffects["explosion"] = LoadSound("assets/sound/explosion.wav");
    soundEffects["gameover"] = LoadSound("assets/sound/gameover.wav");
    soundEffects["laser"] = LoadSound("assets/sound/laser.wav");
    soundEffects["laser2"] = LoadSound("assets/sound/laser2.wav");
    soundEffects["nextLevel"] = LoadSound("assets/sound/nextLevel.wav");
    soundEffects["startgame"] = LoadSound("assets/sound/startgame.wav");
    soundEffects["win"] = LoadSound("assets/sound/win.wav");

    for (auto& pair : soundEffects) {
        SetSoundVolume(pair.second, soundVolume);
    }
}

void AudioManager::update()
{
    if (musicLoaded) UpdateMusicStream(currentMusic);
}

void AudioManager::unload()
{
    for (auto& pair : soundEffects)
    {
        UnloadSound(pair.second);
    }
    soundEffects.clear();

    if (musicLoaded)
    {
        UnloadMusicStream(currentMusic);
        musicLoaded = false;
    }

    CloseAudioDevice();
}

void AudioManager::playSound(const std::string& name)
{
    auto it = soundEffects.find(name);
    if (it != soundEffects.end()) PlaySound(it->second);
}

void AudioManager::playMusic(const std::string& path)
{
    if (musicLoaded)
    {
        StopMusicStream(currentMusic);
        UnloadMusicStream(currentMusic);
        musicLoaded = false;
    }

    currentMusic = LoadMusicStream(path.c_str());
    PlayMusicStream(currentMusic);
    SetMusicVolume(currentMusic, musicVolume);
    musicLoaded = true;
}

void AudioManager::stopMusic()
{
    if (musicLoaded) StopMusicStream(currentMusic);
}

void AudioManager::setSoundVolume(float volume)
{
    soundVolume = Clamp(volume, 0.0f, 1.0f);
    for (auto& pair : soundEffects) {
        SetSoundVolume(pair.second, soundVolume);
    }
}

void AudioManager::setMusicVolume(float volume)
{
    musicVolume = Clamp(volume, 0.0f, 1.0f);
    if (musicLoaded) {
        SetMusicVolume(currentMusic, musicVolume);
    }
}
