#pragma once
#include "config.h"

class Image;
class BHObject
{
protected:
	bool isAlive;
	
	FPOINT position;
	float radianAngle;

	//TODO: ICollideable
	float hit;

	//TODO:
	Image* image;
	
	//identifier for determine if something could be harmful to player
public:
	BHObject() = default;
	virtual ~BHObject() = default;

	virtual void Update() = 0;

	virtual void Init(Image* image, float hit, FPOINT position, float radianAngle);

	// void RenderSub(HDC hdc, Image* image, float size, float fade);
	virtual void Render(HDC hdc);
	
	// bool IsHit(BHObject* BHObject);
	//TODO: Quad-Tree Optimization how?
	//bool IsHit(CTaskList * list);

	//TODO:
	// inline void SetShape(int shape_id) { Shape = new SHAPE(); };
};
