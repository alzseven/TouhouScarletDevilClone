#pragma once
#include <windows.h>
#include <d2d1.h>
#include <wincodec.h>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "windowscodecs.lib")

class D2DImage {
private:
    static ID2D1Factory* factory;
    static ID2D1HwndRenderTarget* renderTarget;

    ID2D1Bitmap* bitmap = nullptr;

    int maxFrameX = 0;
    int maxFrameY = 0;
    int frameWidth = 0;
    int frameHeight = 0;

public:
    static HRESULT InitD2D(HWND hWnd);
    static HRESULT BeginDraw();
    static HRESULT EndDraw();
    static void Clear(D2D1::ColorF color);
    static ID2D1HwndRenderTarget* GetRenderTarget();

    HRESULT LoadFromFile(const wchar_t* filePath);
    HRESULT LoadFromFile(const wchar_t* filePath, int maxFrameX, int maxFrameY);

    //x좌표, y좌표, 각도(도),좌우반전,상하반전,투명도(0.0~1.0)
    void Render(float x, float y, float angle = 0.0f,
        bool flipX = false, bool flipY = false, 
        float alpha=1.0f);
    //x좌표, y좌표,현재프레임 ,각도(도),좌우반전,상하반전,투명도(0.0~1.0)
    void RenderFrame(float x, float y, int frameIndex, float angle = 0.0f, 
        bool flipX = false, bool flipY = false, 
        float alpha=1.0f);
    //x좌표, y좌표,가로배율,세로배율,현재프레임 ,각도(도),좌우반전,상하반전,투명도(0.0~1.0)
    void RenderFrameScale(float x, float y,float scaleX,float scaleY,
        int frameIndex, float angle = 0.0f,
        bool flipX = false, bool flipY = false,
        float alpha = 1.0f);
    //좌표의 기준이 중심
    void Middle_Render(float x, float y, float angle = 0.0f, 
        bool flipX = false, bool flipY = false, 
        float alpha = 1.0f);
    //좌표의 기준이 중심
    void Middle_RenderFrame(float x, float y, int frameIndex, float angle = 0.0f, 
        bool flipX = false, bool flipY = false, 
        float alpha = 1.0f);
    //좌표의 기준이 중심
    void Middle_RenderFrameScale(float x, float y, float scaleX, float scaleY,
        int frameIndex, float angle = 0.0f,
        bool flipX = false, bool flipY = false,
        float alpha = 1.0f);

    void Release();
    inline int GetMaxFrameX() { return maxFrameX; }
    inline int GetMaxFrameY() { return maxFrameY; }

    static void ReleaseLast();
};
