#pragma once
#include "config.h"
#include "ICircleCollideable.h"

class Image;
class BHObject : public ICircleCollideable
{
protected:
	bool isAlive;
	FPOINT position;
	float radianAngle;

	Image* image;
public:
	BHObject() = default;
	~BHObject() override = default;

	virtual void Init(Image* image, float hit, FPOINT position, float radianAngle);
	virtual void Release() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render(HDC hdc);

	void OnHit(ICollideable* hitObject) override = 0;
	
	inline FPOINT* GetPos() override { return &position; }
};
