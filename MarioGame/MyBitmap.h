#pragma once
#include "Bitmap_OP.h"

class MyBitmap
{
public:
	MyBitmap(void);
	MyBitmap(LPCTSTR str);
	HBITMAP hBitmap;
	
	void DrawTransparent(HDC pDC, int x, int y, COLORREF crColour);
	void DrawTransparent(HDC pDC, int x, int y,int x1, int y1,int width,int height, COLORREF crColour);
public:
	~MyBitmap(void);
};
