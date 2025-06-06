#include "SoundPlayer.h"
#include <iostream>

void SoundPlayer::Init()
{
    FMOD::System_Create(&fmodSystem); // 시스템 생성
    fmodSystem->init(128, FMOD_INIT_NORMAL, nullptr); // 초기화

    //soundEffects
    {
        LoadSound("cancel", "Sound/Effect/cancel.wav", false);
        LoadSound("click", "Sound/Effect/click.wav", false);
        LoadSound("hit", "Sound/Effect/hit.wav", false);
        LoadSound("item", "Sound/Effect/item.wav", false);
        LoadSound("lazerA", "Sound/Effect/lazerA.wav", false);
        LoadSound("lazerB", "Sound/Effect/lazerB.wav", false);
        LoadSound("marisa_bomb", "Sound/Effect/marisa_bomb.wav", false);
        LoadSound("player_dead", "Sound/Effect/player_dead.wav", false);
        LoadSound("player_shoot", "Sound/Effect/player_shoot.wav", false);
        LoadSound("powerup", "Sound/Effect/powerup.wav", false);
        LoadSound("select", "Sound/Effect/select.wav", false);
        LoadSound("timeout", "Sound/Effect/timeout.wav", false);
        LoadSound("enemy_shoot", "Sound/Effect/enemy_shoot.wav", false);
        LoadSound("boss_dead", "Sound/Effect/boss_dead.wav", false);
    }
    //bmg
    {
        LoadSound("ending", "Sound/Bgm/ending.mp3", true);
        LoadSound("extra_boss", "Sound/Bgm/extra_boss.mp3", true);
        LoadSound("extra_normal", "Sound/Bgm/extra_normal.mp3", true);
        LoadSound("staff", "Sound/Bgm/staff.mp3", true);
        LoadSound("stage1_boss", "Sound/Bgm/stage1_boss.mp3", true);
        LoadSound("stage1_normal", "Sound/Bgm/stage1_normal.mp3", true);
        LoadSound("stage2_boss", "Sound/Bgm/stage2_boss.mp3", true);
        LoadSound("stage2_normal", "Sound/Bgm/stage2_normal.mp3", true);
        LoadSound("stage3_boss", "Sound/Bgm/stage3_boss.mp3", true);
        LoadSound("stage3_normal", "Sound/Bgm/stage3_normal.mp3", true);
        LoadSound("stage4_boss", "Sound/Bgm/stage4_boss.mp3", true);
        LoadSound("stage4_normal", "Sound/Bgm/stage4_normal.mp3", true);
        LoadSound("stage5_boss", "Sound/Bgm/stage5_boss.mp3", true);
        LoadSound("stage5_normal", "Sound/Bgm/stage5_normal.mp3", true);
        LoadSound("stage6_boss", "Sound/Bgm/stage6_boss.mp3", true);
        LoadSound("stage6_normal", "Sound/Bgm/stage6_normal.mp3", true);
        LoadSound("title", "Sound/Bgm/title.mp3", true);

    }
}

void SoundPlayer::Update()
{
    timer++;
    if (fmodSystem) fmodSystem->update();

    
    if (timer > 1000)
    {
        for (auto it = channels.begin(); it != channels.end(); ) {
            bool isPlaying = false;
            (*it).second->isPlaying(&isPlaying);
            if (!isPlaying) {
                (*it).second->stop();
                it = channels.erase(it);
            }
            else {
                ++it;
            }
        }
        timer = 0;
    }
}

void SoundPlayer::Release()
{
    for (auto& s : sounds)
        s.second->release();

    sounds.clear();
    fmodSystem->close();
    fmodSystem->release();
}

void SoundPlayer::LoadSound(const string& key, const char* filepath, bool loop)
{
    FMOD_MODE mode = FMOD_DEFAULT | FMOD_CREATESAMPLE;
    if (loop) mode |= FMOD_LOOP_NORMAL;
    else mode |= FMOD_LOOP_OFF;

    FMOD::Sound* sound = nullptr;
    fmodSystem->createSound(filepath, mode, nullptr, &sound);
    sounds[key] = sound;
}

void SoundPlayer::SoundOn(const string& key, float volume)
{
    auto it = sounds.find(key);
    if (it == sounds.end()) return;

    FMOD::Channel* channel = nullptr;
    fmodSystem->playSound(it->second, nullptr, false, &channel);
    if (channel) {
        channel->setVolume(volume);

        // 사운드의 모드를 확인하여 루프 사운드인 경우에만 channels에 저장합니다.
        FMOD_MODE mode;
        it->second->getMode(&mode);
        if (mode & FMOD_LOOP_NORMAL) { // 루프 설정된 사운드인 경우
            channels.insert({ key, channel });
        }
    }
}

void SoundPlayer::SoundOff(const string& key)
{
    auto it = channels.find(key);
    if (it != channels.end() && it->second) {
        it->second->stop();
        channels.erase(it);
    }
}
