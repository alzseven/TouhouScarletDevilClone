#pragma once
#include "config.h"
#include "ICircleCollideable.h"

class Image;
class BHObject : public ICircleCollideable
{
protected:
	bool isAlive;
	
	FPOINT* position;
	float radianAngle;

	//TODO: ICollideable
	float hit;

	//TODO:
	Image* image;
	
	//identifier for determine if something could be harmful to player
public:
	BHObject() = default;
	virtual ~BHObject() = default;

	virtual void Init(Image* image, float hit, FPOINT position, float radianAngle);

	virtual void Release() = 0;
	
	virtual void Update() = 0;

	virtual void Render(HDC hdc);

	virtual void Move(float angle, float speed);

	
	// bool IsHit(BHObject* BHObject);
	
	//TODO: Quad-Tree Optimization how?
	//bool IsHit(CTaskList * list);

	//TODO:
	// inline void SetShape(int shape_id) { Shape = new SHAPE(); };

	FPOINT* GetPos() override { return position; }
};
