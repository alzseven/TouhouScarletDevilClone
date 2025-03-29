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

    void Draw(float x, float y, float angle = 0.0f, bool flipX = false, bool flipY = false);
    void DrawFrame(float x, float y, int frameIndex, float angle = 0.0f, bool flipX = false, bool flipY = false);

    void Release();
};
