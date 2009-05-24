#pragma once
#include "mmsystem.h"
#include "MyBitmap.h"
#include "Sprite.h"

#define SCREENWIDTH 640
#define SCREENHEIGHT 480
#define FRAMES_PER_SEC 50
#define KEY_DOWN(vk_code) ( (GetAsyncKeyState(vk_code) & 0x8000)? 1 : 0 )
class CGame
{
private:
	HWND mainWnd;
	HDC wndDC;
	HDC memDC;
	HBITMAP memBitmap;
	HBITMAP oldBitmap;
	Bitmap_Operations* pBmOp;
	Sprite* character;
	long iTick;
	int LoadBackground(LPCTSTR bgName);
public:
	int Init(HWND hWnd);
	int Run();
	int End();
	CGame(void);	
	~CGame(void);
	int OnKeyDown(WPARAM wParam, LPARAM lParam);
	int OnKeyUp(WPARAM wParam, LPARAM lParam);	
	
	void InitHDC();
	void CopyToScreen();
	void ReleaseHDC();
	
};
