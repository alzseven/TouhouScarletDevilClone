#include "KeyManager.h"

HRESULT KeyManager::Init()
{
    keyUp.set();
    keyDown.reset();

    return S_OK;
}

void KeyManager::Release()
{
    ReleaseInstance();
}

bool KeyManager::IsOnceKeyDown(int key)
{
    if (GetAsyncKeyState(key) & 0x8000)
    {
        if (keyDown[key] == false)
        {
            keyDown[key] = true;
            return true;
        }
    }
    else
    {
        keyDown[key] = false;
    }

    return false;
}

bool KeyManager::IsOnceKeyUp(int key)
{
    if (GetAsyncKeyState(key) & 0x8000)
    {
        keyUp[key] = false;
    }
    else
    {
        if (keyUp[key] == false)
        {
            keyUp[key] = true;
            return true;
        }
    }

    return false;
}

bool KeyManager::IsStayKeyDown(int key)
{
    if (GetAsyncKeyState(key) & 0x8000)
    {
        return true;
    }
    return false;
}
