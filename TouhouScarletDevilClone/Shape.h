#pragma once
#include "config.h"

class D2DImage;

class Shape
{
public:
	D2DImage* image = nullptr;

	Shape() {};
	Shape(D2DImage* image);
	virtual ~Shape() {};
};

class ShapeRect : public Shape
{
public:
	float width = 0.f;
	float height = 0.f;
	float scaleX = 1.f, scaleY = 1.f;
	ShapeRect(D2DImage* image, float scaleX = 1.f, float scaleY = 1.f,
		float width = 0.f, float height = 0.f);
};

class ShapeCircle : public Shape
{
public:
	float radius;
	ShapeCircle(D2DImage* image, float radius = 0.f);
};

