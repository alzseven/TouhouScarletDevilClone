#include "Shape.h"

Shape::Shape(D2DImage* image)
{
	this->image = image;
}

ShapeRect::ShapeRect(D2DImage* image, float scaleX, float scaleY, float width, float height)
{
	this->image = image;
	this->scaleX = scaleX;
	this->scaleY = scaleY;
	this->width = width * scaleX;
	this->height = height * scaleY;
}

float ShapeRect::getHitWidth()
{
	return width;
}

float ShapeRect::getHitHeight()
{
	return height;
}

ShapeCircle::ShapeCircle(D2DImage* image, float radius)
{
	this->image = image;
	this->radius = radius;
}

float ShapeCircle::getHitWidth()
{
	return radius * 2;
}

float ShapeCircle::getHitHeight()
{
	return radius * 2;
}


