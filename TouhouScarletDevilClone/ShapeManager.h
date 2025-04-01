#pragma once
#include "Singleton.h"
#include "config.h"



class Shape;
class D2DImage;
class ShapeManager : public Singleton<ShapeManager>
{
private:
	map<string, Shape*> mapShapes;

public:
	void Init();
	void Release();

	Shape* AddShapeCharacter(string key, D2DImage* image, float radius = 0.f);

	Shape* AddShapeCircle(string key, const wchar_t* filePath, float radius = 0.f);

	Shape* AddShapeRect(string key, const wchar_t* filePath,
		float scaleX = 1.f, float scaleY = 1.f,
		float width = 0.f, float height = 0.f);

	void DeleteShape(string key);
	Shape* FindShapeAdd(string key);
	Shape* FindShape(string key);
};



