#pragma once
#include "config.h"

class D2DImage;

class Shape
{
public:
	D2DImage* image = nullptr;

	Shape() = default;
	Shape(D2DImage* image);
	virtual ~Shape() = default;
	virtual float getHitWidth() = 0;
	virtual float getHitHeight() = 0;
};

class ShapeRect : public Shape
{
public:
	float width = 0.f;
	float height = 0.f;
	float scaleX = 1.f, scaleY = 1.f;
	ShapeRect(D2DImage* image, float scaleX = 1.f, float scaleY = 1.f,
		float width = 0.f, float height = 0.f);
	virtual float getHitWidth() override;
	virtual float getHitHeight() override;
};

class ShapeCircle : public Shape
{
public:
	float radius;
	ShapeCircle(D2DImage* image, float radius = 0.f);
	virtual float getHitWidth() override;
	virtual float getHitHeight() override;
};

