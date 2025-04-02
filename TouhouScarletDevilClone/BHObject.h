#pragma once
#include "config.h"
#include "ICircleCollideable.h"
#include "IObjectActionPattern.h"

class IObjectActionPattern;
class Image;
class D2DImage;
class BHObject : public ICircleCollideable
{
protected:
	bool isAlive;
	FPOINT position;
	float radianAngle;
	Shape* shape;

public:
	BHObject();
	~BHObject() override = default;

	virtual void Init(string shapeKey, float hitRadius, FPOINT pos, float radianAngle);
	virtual void Release() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render(HDC hdc);
	virtual bool IsOutofScreen();

	void OnHit(ICollideable* hitObject) override = 0;
	
	inline FPOINT* GetPos() override { return &position; }
	
	//Controlables
	virtual void Move(float angle, float moveSpeed, float dt) = 0;
	virtual void Shoot(FPOINT init_pos, float angle, float angleRate, float shootSpeed, float shootSpeedRate) = 0;

	inline bool IsValid() override { return isAlive; }
};
