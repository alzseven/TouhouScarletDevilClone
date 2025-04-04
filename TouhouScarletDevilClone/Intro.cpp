#include "Intro.h"
#include "D2DImage.h"
#include "ImageManager.h"
#include "config.h"
#include "KeyManager.h"


Intro::~Intro()
{
}

void Intro::Init()
{
	SoundPlayer::GetInstance()->SoundOn("title");
	IntroImage = ImageManager::GetInstance()->AddImage("Intro", TEXT("./Image/Intro/UI_loading.jpg"));
}

void Intro::Release()
{
}

void Intro::Update(float dt)
{
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_RETURN))
	{
		
		if (currentScene)
			*currentScene = mainMenu;
	}
}

void Intro::Render(HDC hdc)
{
	if (IntroImage)
	{
		IntroImage->Render(-WINSIZE_X / 2, -WINSIZE_Y / 2);
	}
}
