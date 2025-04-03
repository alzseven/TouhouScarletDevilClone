#pragma once
#include "Singleton.h"
#include "config.h"

class SoundPlayer : public Singleton<SoundPlayer>
{
private:
	FMOD::System* fmodSystem = nullptr;
	FMOD::Sound* bgm = nullptr;
    map<string, FMOD::Sound*> sounds;
    map<string, FMOD::Channel*> channels;

public:
    void Init();
    void Update();
    void Release();
    void LoadSound(const string& key, const char* filepath, bool loop = false);
    void SoundOn(const string& key, float volume = 1.0f);
    void SoundOff(const string& key);
};

