#pragma once
#include "config.h"

class D2DImage;

class Shape
{
protected:
	D2DImage* image;
public:
	Shape() = default;
	Shape(D2DImage* image);
	virtual ~Shape() = default;
	virtual float GetHitWidth() = 0;
	virtual float GetHitHeight() = 0;
	inline D2DImage* GetImage() const { return image; }
};

class ShapeRect : public Shape
{
	float width = 0.f;
	float height = 0.f;
	float scaleX = 1.f, scaleY = 1.f;
public:
	ShapeRect(D2DImage* image, float scaleX = 1.f, float scaleY = 1.f,
		float width = 0.f, float height = 0.f);
	inline float GetHitWidth() override { return width; }
	inline float GetHitHeight() override { return height; }
};

class ShapeCircle : public Shape
{
	float radius;
public:
	ShapeCircle(D2DImage* image, float radius = 0.f);
	inline float GetHitWidth() override { return radius * 2; }
	inline float GetHitHeight() override { return radius * 2; }
};

