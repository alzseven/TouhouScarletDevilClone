#pragma once
#include "Singleton.h"
#include "config.h"

class Image;
class EffectPlayer : public Singleton<EffectPlayer>
{
private:
	list<Effect*> activeEffects;
	map<string, Effect*> effectLists;
	void Init();
	void PlayEffect(string key, FPOINT pos);
	void Update(float time);
	void Release();
};

//동작들의 모음 = 1effect
class Effect
{
	vector<EffectTask> tasks;
	FPOINT pos;
	int currentTask;
	void Update(float time);
};

//하나의 동작
class EffectTask
{
public:
	Image* image;
	FPOINT offset;
	float startTime;
	float endTime;
	virtual ~EffectTask() {};
	virtual void Update() = 0;
	virtual float GetCurrentAngle(float time) = 0;
	virtual float GetCurrentPos(float time) = 0;
	virtual float GetCurrentAlpha(float time) = 0;
	virtual float GetCurrentSize(float time) = 0;
};

class FadeEffectTask :public EffectTask
{
	float startAlpha;
	float endAlpha;
};

class RollEffectTask :public EffectTask
{
	float startAngle;
	float endAngle;
};

class SpinEffectTask : public EffectTask
{
	float spinSpeed;
};

class SizeEffectTask :public EffectTask
{
	float startSize;
	float endSize;
};