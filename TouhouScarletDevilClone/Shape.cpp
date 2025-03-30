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

ShapeCircle::ShapeCircle(D2DImage* image, float radius)
{
	this->image = image;
	this->radius = radius;
}


