#include "Ending.h"
#include "D2DImage.h"
#include "ImageManager.h"
#include "config.h"
#include "KeyManager.h"

void Ending::Init()
{
	EndingImage = ImageManager::GetInstance()->AddImage("EndingScene", TEXT("Image/Intro/result.jpg"));
}

void Ending::Release()
{
}

void Ending::Update(float dt)
{
}

void Ending::Render(HDC hdc)
{
	if (EndingImage)
	{
		EndingImage->Middle_RenderFrameScale(WINSIZE_X/2, WINSIZE_Y/2, 1.4f,1.2f, 1);
	}
}
