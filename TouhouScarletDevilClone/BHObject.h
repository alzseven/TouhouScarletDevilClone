#pragma once
#include "config.h"
#include "ICircleCollideable.h"

class IObjectActionPattern;
class Image;
class D2DImage;
class BHObject : public ICircleCollideable
{
protected:
	bool isAlive;
	FPOINT position;
	float radianAngle;

	// D2DImage* image;
	Shape* shape;

public:
	BHObject() = default;
	~BHObject() override = default;

	virtual void Init(string shapeKey, float hitRadius, FPOINT pos, float radianAngle);
	// virtual void Init(D2DImage* image, float hitRadius, FPOINT position, float radianAngle);
	virtual void Release() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render(HDC hdc);
	bool IsOutofScreen();

	void OnHit(ICollideable* hitObject) override = 0;
	
	inline FPOINT* GetPos() override { return &position; }

	// inline void AddAction(IObjectActionPattern* actions) { this->actions.push_back(actions); }
	// inline void SetPattern(IObjectActionPattern* newPatterns) { this->patterns = newPatterns; }

	//Controlables
	virtual void Move(float angle, float moveSpeed, float dt) = 0;
	virtual void Shoot(float angle, int shootAmount = 1) = 0;
};
