#pragma once
#include "Singleton.h"
#include "config.h"

#define MAX_KEY_COUNT	256

class KeyManager : public Singleton<KeyManager>
{
private:
	bitset<MAX_KEY_COUNT> keyUp;
	bitset<MAX_KEY_COUNT> keyDown;

public:
	HRESULT Init();
	void Release();

	bool IsOnceKeyDown(int key);
	bool IsOnceKeyUp(int key);
	bool IsStayKeyDown(int key);

	void SetKeyDown(int key, bool state) { this->keyDown.set(key, state); }
	void SetKeyUp(int key, bool state) { this->keyUp.set(key, state); }

};

