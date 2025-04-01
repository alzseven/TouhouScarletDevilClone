#include "ImageManager.h"
#include "D2DImage.h"

void ImageManager::Init()
{
	AddImage("Error", TEXT("Image/MissingNo.png"));
}

void ImageManager::Release()
{
	
	map<string, D2DImage*>::iterator iter;
	for (iter = mapImages.begin(); iter != mapImages.end(); iter++)
	{
		if (iter->second)
		{
			(iter->second)->Release();
			delete (iter->second);
			(iter->second) = nullptr;
		}
	}
	mapImages.clear();
	D2DImage::ReleaseLast();
	ReleaseInstance();
}

D2DImage* ImageManager::AddImage(string key,
	const wchar_t* filePath)
{
	D2DImage* image = nullptr;
	image = FindImageAdd(key);
	if (image)	return image;

	image = new D2DImage();
	if (FAILED(image->LoadFromFile(filePath)))
	{
		if (image == nullptr)
		{
			delete image;
			return nullptr;
		}
		return  FindImage("Error");
	}

	mapImages.insert(make_pair(key, image));
	return image;
}

D2DImage* ImageManager::AddImage(string key,
	const wchar_t* filePath, int maxFrameX, int maxFrameY)
{
	D2DImage* image = nullptr;
	image = FindImageAdd(key);
	if (image)	return image;

	image = new D2DImage();
	if (FAILED(image->LoadFromFile(filePath,
		maxFrameX, maxFrameY)))
	{
		if (image == nullptr)
		{
			delete image;
			return nullptr;
		}
		return  FindImage("Error");
	}

	mapImages.insert(make_pair(key, image));
	return image;
}

void ImageManager::DeleteImage(string key)
{
	map<string, D2DImage*>::iterator iter;
	iter = mapImages.find(key);

	if (iter == mapImages.end()) return;

	(iter->second)->Release();
	delete (iter->second); 
	(iter->second) = nullptr;

	mapImages.erase(iter);
}

D2DImage* ImageManager::FindImageAdd(string key)
{
	map<string, D2DImage*>::iterator iter;
	iter = mapImages.find(key);

	if (iter == mapImages.end()) return nullptr;

	return iter->second;
}
D2DImage* ImageManager::FindImage(string key)
{
	map<string, D2DImage*>::iterator iter;
	iter = mapImages.find(key);

	if (iter == mapImages.end()) return mapImages["Error"];

	return iter->second;
}
