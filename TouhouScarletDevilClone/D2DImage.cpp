#include "D2DImage.h"

ID2D1Factory* D2DImage::factory = nullptr;
ID2D1HwndRenderTarget* D2DImage::renderTarget = nullptr;

HRESULT D2DImage::InitD2D(HWND hWnd) {
    if (!factory) {
        D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
    }

    RECT rc;
    GetClientRect(hWnd, &rc);

    if (!renderTarget) {
        D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);
        D2D1_RENDER_TARGET_PROPERTIES rtProps = D2D1::RenderTargetProperties();
        D2D1_HWND_RENDER_TARGET_PROPERTIES hwndProps = D2D1::HwndRenderTargetProperties(hWnd, size);

        return factory->CreateHwndRenderTarget(rtProps, hwndProps, &renderTarget);
    }
    return S_OK;
}

HRESULT D2DImage::BeginDraw() {
    if (!renderTarget) return E_FAIL;
    renderTarget->BeginDraw();
    return S_OK;
}

HRESULT D2DImage::EndDraw() {
    if (!renderTarget) return E_FAIL;
    return renderTarget->EndDraw();
}

void D2DImage::Clear(D2D1::ColorF color) {
    if (renderTarget) renderTarget->Clear(color);
}

HRESULT D2DImage::LoadFromFile(const wchar_t* filePath) {
    IWICImagingFactory* wicFactory = nullptr;
    IWICBitmapDecoder* decoder = nullptr;
    IWICBitmapFrameDecode* frame = nullptr;
    IWICFormatConverter* converter = nullptr;
    
    HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&wicFactory));
    if (FAILED(hr)) return hr;

    hr = wicFactory->CreateDecoderFromFilename(filePath, NULL, GENERIC_READ,
        WICDecodeMetadataCacheOnLoad, &decoder);
    if (FAILED(hr)) return hr;

    hr = decoder->GetFrame(0, &frame);
    if (FAILED(hr)) return hr;

    hr = wicFactory->CreateFormatConverter(&converter);
    if (FAILED(hr)) return hr;

    hr = converter->Initialize(frame, GUID_WICPixelFormat32bppPBGRA,
        WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);
    if (FAILED(hr)) return hr;

    hr = renderTarget->CreateBitmapFromWicBitmap(converter, NULL, &bitmap);

    if (converter) converter->Release();
    if (frame) frame->Release();
    if (decoder) decoder->Release();
    if (wicFactory) wicFactory->Release();

    return hr;
}

HRESULT D2DImage::LoadFromFile(const wchar_t* filePath, int maxFrameX, int maxFrameY) {
    HRESULT hr = LoadFromFile(filePath);
    if (FAILED(hr)) return hr;
    if (!bitmap) return E_FAIL;
    D2D1_SIZE_F size = bitmap->GetSize();

    this->maxFrameX = maxFrameX;
    this->maxFrameY = maxFrameY;
    this->frameWidth = static_cast<int>(size.width) / maxFrameX;
    this->frameHeight = static_cast<int>(size.height) / maxFrameY;

    return S_OK;
}

void D2DImage::Middle_Render(float x, float y, float angle, 
    bool flipX, bool flipY, float alpha) {
    if (!bitmap || !renderTarget) return;

    D2D1_SIZE_F bmpSize = bitmap->GetSize();
    D2D1_RECT_F destRect = D2D1::RectF(x - bmpSize.width / 2, y - bmpSize.height / 2, x + bmpSize.width/2, y + bmpSize.height/2);

    D2D1::Matrix3x2F transform = D2D1::Matrix3x2F::Identity();
    transform = transform * D2D1::Matrix3x2F::Translation(-bmpSize.width / 2.0f, -bmpSize.height / 2.0f);
    transform = transform * D2D1::Matrix3x2F::Scale(flipX ? -1.0f : 1.0f, flipY ? -1.0f : 1.0f);
    transform = transform * D2D1::Matrix3x2F::Rotation(angle);
    transform = transform * D2D1::Matrix3x2F::Translation(x + bmpSize.width / 2.0f, y + bmpSize.height / 2.0f);

    renderTarget->SetTransform(transform);
    renderTarget->DrawBitmap(bitmap, D2D1::RectF(0, 0, bmpSize.width, bmpSize.height), alpha);
    renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void D2DImage::Middle_RenderFrame(float x, float y, int frameIndex,
    float angle, bool flipX, bool flipY, float alpha) {
    if (!bitmap || !renderTarget || maxFrameX <= 0 || maxFrameY <= 0) return;

    int totalFrames = maxFrameX * maxFrameY;
    frameIndex %= totalFrames;

    int fx = frameIndex % maxFrameX;
    int fy = frameIndex / maxFrameX;

    D2D1_RECT_F srcRect = D2D1::RectF(
        static_cast<float>(fx * frameWidth),
        static_cast<float>(fy * frameHeight),
        static_cast<float>((fx + 1) * frameWidth),
        static_cast<float>((fy + 1) * frameHeight)
    );

    float centerX = x;
    float centerY = y;

    D2D1_RECT_F destRect = D2D1::RectF(
        centerX - (float)frameWidth / 2.0f,
        centerY - (float)frameHeight / 2.0f,
        centerX + (float)frameWidth / 2.0f,
        centerY + (float)frameHeight / 2.0f
    );

    D2D1::Matrix3x2F transform = D2D1::Matrix3x2F::Identity();
    transform = transform * D2D1::Matrix3x2F::Scale(
        flipX ? -1.0f : 1.0f,
        flipY ? -1.0f : 1.0f,
        D2D1::Point2F(centerX, centerY)
    );
    transform = transform * D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(centerX, centerY));

    renderTarget->SetTransform(transform);
    renderTarget->DrawBitmap(bitmap, destRect, alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, srcRect);
    renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void D2DImage::Middle_RenderFrameScale(float x, float y, float scaleX, float scaleY, int frameIndex, float angle, bool flipX, bool flipY, float alpha)
{
    if (!bitmap || !renderTarget || maxFrameX <= 0 || maxFrameY <= 0) return;

    int totalFrames = maxFrameX * maxFrameY;
    frameIndex %= totalFrames;

    int fx = frameIndex % maxFrameX;
    int fy = frameIndex / maxFrameX;

    D2D1_RECT_F srcRect = D2D1::RectF(
        static_cast<float>(fx * frameWidth),
        static_cast<float>(fy * frameHeight),
        static_cast<float>((fx + 1) * frameWidth),
        static_cast<float>((fy + 1) * frameHeight)
    );

    float halfWidth = frameWidth  / 2.0f;
    float halfHeight = frameHeight / 2.0f;

    float centerX = x;
    float centerY = y;

    D2D1_RECT_F destRect = D2D1::RectF(
        centerX - halfWidth,
        centerY - halfHeight,
        centerX + halfWidth,
        centerY + halfHeight
    );

    D2D1::Matrix3x2F transform = D2D1::Matrix3x2F::Identity();

    float finalScaleX = scaleX * (flipX ? -1.0f : 1.0f);
    float finalScaleY = scaleY * (flipY ? -1.0f : 1.0f);

    transform = transform * D2D1::Matrix3x2F::Scale(
        finalScaleX, finalScaleY,
        D2D1::Point2F(centerX, centerY)
    );

    transform = transform * D2D1::Matrix3x2F::Rotation(
        angle,
        D2D1::Point2F(centerX, centerY)
    );

    renderTarget->SetTransform(transform);
    renderTarget->DrawBitmap(bitmap, destRect, alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, srcRect);
    renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void D2DImage::Render(float x, float y, float angle, bool flipX, bool flipY, float alpha)
{
    D2D1_SIZE_F bmpSize = bitmap->GetSize();
    Middle_Render(x + bmpSize.width / 2, y + bmpSize.height / 2, angle, flipX, flipY, alpha);
}

void D2DImage::RenderFrame(float x, float y, int frameIndex, float angle, bool flipX, bool flipY, float alpha)
{
    Middle_RenderFrame(x + frameWidth / 2, y + frameHeight / 2, frameIndex, angle, flipX, flipY, alpha);
}

void D2DImage::RenderFrameScale(float x, float y, float scaleX, float scaleY, int frameIndex, float angle, bool flipX, bool flipY, float alpha)
{
    Middle_RenderFrameScale(x + frameWidth / 2, y + frameHeight / 2, scaleX, scaleY, frameIndex, angle, flipX, flipY, alpha);
}

ID2D1HwndRenderTarget* D2DImage::GetRenderTarget() {
    return renderTarget;
}

void D2DImage::Release() {
    if (renderTarget) {
        renderTarget->Release();
        renderTarget = nullptr;
    }
    

}

//프로그램이 종료될 때 단 한번만 호출
//factory가 static임
void D2DImage::ReleaseLast()
{
    if (factory) {
        factory->Release();
        factory = nullptr;
    }
}

