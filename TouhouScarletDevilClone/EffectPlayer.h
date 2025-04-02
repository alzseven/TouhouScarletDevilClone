#pragma once
#include "config.h"
#include "Singleton.h"


class D2DImage;
class EffectTask;
class Effect;
class EffectPlayer : public Singleton<EffectPlayer>
{
private:
	list<Effect*> activeEffects;
	list<Effect*> freeEffects;
	map<string, Effect*> mapEffects;
public:
	void Init(int size);
	void PlayEffect(string key, FPOINT pos);
	void AddEffect(string key, Effect* effect);
	Effect* FindEffectAdd(string key);
	Effect* FindEffect(string key);
	void Update(float dt);
	void Render();
	void Release();
};

//동작들의 모음 = 1effect
class Effect
{
public:
	vector<EffectTask> tasks;
	FPOINT pos = { 0,0 };
	float currentTime = 0;
	float endTime = 0;
	void On(FPOINT pos) { this->pos = pos; currentTime = 0; }
	inline void Off() { this->pos = { 0,0 }; currentTime = 0; }
	void Update(float dt);
	void Render();
	void pushEffectTask(EffectTask effectTask);

	void Clone(Effect* from);
};

//하나의 동작
class EffectTask
{
public:
	D2DImage* image = nullptr;
	FPOINT offset = { 0,0 };
	float startTime = 0.0f;
	float endTime = 0.0f;

	float image_angle = 0;
	float image_alpha = 0.0f;
	FPOINT image_scale = { 1.0f,1.0f };

	// fade in/out
	bool fadeFlag = false;
	float startAlpha = 0;
	float endAlpha = 0;
	// roll
	bool rollFlag = false;
	float startAngle = 0;
	float endAngle = 0;
	// spin
	bool spinFlag = false;
	float spinSpeed = 0;
	//Zoom in/out
	bool zoomFlag = false;
	float startZoom = 0;
	float endZoom = 0;
	//Move
	bool moveFlag = false;
	float move_angle;
	float move_speed;
	float move_speedRate;

	void Init(D2DImage* image,float startTime, float endTime,
		FPOINT offset = { 0,0 }, float angle = 0,
		float alpha = 1.0f, FPOINT scale = { 1.0f,1.0f });

	void Update(float time);
	void Render(FPOINT pos);

	float calcAlpha(float time);
	float calcAngle(float time);
	float calcZoom(float time);
	void makeSpin(float& angle);
	FPOINT calcMove(float time);

	void setOffset(FPOINT offset);
	void setFade(float startAlpha, float endAlpha);
	void setRoll(float startAngle, float endAngle);
	void setSpin(float speed);
	void setZoom(float startSize, float endSize);
	void setMove(float angle, float speed, float speedRate);
};

