#pragma once
#include "config.h"

class Image;
class BHObject
{
protected:
	//TODO: ICollideable, IRenderable
	SHAPE* Shape;
	float scale;
	float imgAlpha;
	bool isAlive;

	FPOINT position;
	float radianAngleDirection;
	//identifier for determine if something could be harmful to player
public:
	BHObject() = default;
	virtual ~BHObject() = default;

	virtual void Update() = 0;

	virtual void Init(SHAPE* shape, FPOINT position, float angle);

	void RenderSub(HDC hdc, Image* image, float size, float fade);
	//void RenderSub(CTexture* texture, float size, float fade);
	void Render(HDC hdc);
	
	bool IsHit(BHObject* BHObject);
	//TODO: Quad-Tree Optimization how?
	//bool IsHit(CTaskList * list);

	//TODO:
	inline void SetShape(int shape_id) { Shape = new SHAPE(); };
};

