#include "config.h"
#include "MainGame.h"
#include "TouhouScarletDevilCloneGame.h"
#include "UI.h"
#include "D2DImage.h"
#include "BHObjectManager.h"
#include "BHitem.h"

void MainGame::Init()
{
	KeyManager::GetInstance()->Init();
	BHObjectManager::GetInstance()->Init();
	
	D2DImage::InitD2D(g_hWnd);
	ShapeManager::GetInstance()->Init();
	
	gameInstance = new TouhouScarletDevilCloneGame();
	gameInstance->Init();
	eSpawn = 100;
	SoundPlayer::GetInstance()->SoundOn("stage3_boss");
	//SoundPlayer::GetInstance()->SoundOn("background");
}

void MainGame::Release()
{
	if (gameInstance)
	{
		gameInstance->Release();
		delete gameInstance;
		gameInstance = nullptr;
	}

	KeyManager::GetInstance()->Release();
	BHObjectManager::GetInstance()->Release();
	
	ReleaseDC(g_hWnd, hdc);
}

void MainGame::Update(float dt)
{
	eTimer += dt;
	gameInstance->Update(dt);
	InvalidateRect(g_hWnd, NULL, false);

	EffectPlayer::GetInstance()->Update(dt);
	if (eTimer >= enTimer)
	{
		enTimer += 2.f;
		eCount++;
		if (eCount > eSpawn) eCount = 0;
		EffectPlayer::GetInstance()->PlayEffect("Hit_blue", { 100.0f, 200.0f });
		EffectPlayer::GetInstance()->PlayEffect("Hit_white", { 150.0f, 200.0f });
		EffectPlayer::GetInstance()->PlayEffect("Hit_red", { 200.0f, 200.0f });
		EffectPlayer::GetInstance()->PlayEffect("Hit_green", { 250.0f, 200.0f });
		EffectPlayer::GetInstance()->PlayEffect("Kill", { 100, 250 });
		EffectPlayer::GetInstance()->PlayEffect("MagicCircle", { 150, 250 });
		EffectPlayer::GetInstance()->PlayEffect("NormalShoot_black", { 200, 250 });
		EffectPlayer::GetInstance()->PlayEffect("NormalShoot_blue", { 250, 250 });
		EffectPlayer::GetInstance()->PlayEffect("NormalShoot_green", { 100, 300 });
		EffectPlayer::GetInstance()->PlayEffect("NormalShoot_purple", { 150, 300 });
		EffectPlayer::GetInstance()->PlayEffect("NormalShoot_red", { 200, 300 });
		EffectPlayer::GetInstance()->PlayEffect("NormalShoot_sky", { 250, 300 });
		EffectPlayer::GetInstance()->PlayEffect("NormalShoot_yellow", { 100, 350 });
		EffectPlayer::GetInstance()->PlayEffect("NormalShoot_white", { 150, 350 });
		EffectPlayer::GetInstance()->PlayEffect("Kill_zako", { 100, 400 });
		EffectPlayer::GetInstance()->PlayEffect("Boss_phase", { 200, 400 });
		
	}

}

void MainGame::Render()
{
	D2DImage::BeginDraw();
	D2DImage::Clear(D2D1::ColorF(D2D1::ColorF::Black));
	
	if (gameInstance) gameInstance->Render(hdc);
	
	EffectPlayer::GetInstance()->Render();
	SoundPlayer::GetInstance()->Update();
	D2DImage::EndDraw();
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}
