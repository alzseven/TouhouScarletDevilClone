#include "ShapeManager.h"
#include "Shape.h"
#include "D2DImage.h"

void ShapeManager::Init()
{
}

void ShapeManager::Release()
{
    map<string, Shape*>::iterator iter;
    for (iter = mapShapes.begin(); iter != mapShapes.end(); iter++)
    {
        if (iter->second)
        {
            delete (iter->second);
            (iter->second) = nullptr;
        }
    }
    mapShapes.clear();
    ReleaseInstance();
}

Shape* ShapeManager::AddShapeCharacter(string key, D2DImage* image, float radius)
{
    Shape* shape = nullptr;
    shape = FindShape(key);
    if (shape) return shape;

    shape = new ShapeCircle(image, radius);
    mapShapes.insert(make_pair(key, shape));
    return shape;
}

Shape* ShapeManager::AddShapeCircle(string key, const wchar_t* filePath, float radius)
{
    Shape* shape = nullptr;
    shape = FindShape(key);
    if (shape) return shape;

    D2DImage* image = ImageManager::GetInstance()->AddImage(key, filePath);
    shape = new ShapeCircle(image, radius);
    mapShapes.insert(make_pair(key, shape));
    return shape;
}

Shape* ShapeManager::AddShapeRect(string key, const wchar_t* filePath, float scaleX, float scaleY, float width, float height)
{
    Shape* shape = nullptr;
    shape = FindShape(key);
    if (shape) return shape;

    D2DImage* image = ImageManager::GetInstance()->AddImage(key, filePath);
    shape = new ShapeRect(image, scaleX, scaleY, width, height);
    mapShapes.insert(make_pair(key, shape));
    return shape;
}

void ShapeManager::DeleteShape(string key)
{
    map<string, Shape*>::iterator iter;
    iter = mapShapes.find(key);

    if (iter == mapShapes.end()) return;

    delete (iter->second);
    (iter->second) = nullptr;

    mapShapes.erase(iter);
}

Shape* ShapeManager::FindShape(string key)
{
    map<string, Shape*>::iterator iter;
    iter = mapShapes.find(key);

    if (iter == mapShapes.end()) return nullptr;

    return iter->second;
}
