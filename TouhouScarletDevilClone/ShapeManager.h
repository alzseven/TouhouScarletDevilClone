#pragma once
#include "Singleton.h"
#include "config.h"

///*
//	배열 : 인덱스 -> 데이터
//	stl::vector : 인덱스 -> 데이터
//	std::map : 키 -> 데이터
//
//	레드-블랙 트리 구현 : 삽입, 삭제, 검색 O(logN) 시간복잡도
//*/

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
	Shape* FindShape(string key);
};



