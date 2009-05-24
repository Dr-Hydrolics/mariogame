#pragma once
#include "MyBitmap.h"

class Sprite
{
public:
	int mFrameDirection; //0 vertical, 1 horizontal
	int mLoopType; //0 loop back to begining, 1 bounce between begin and end
	int mLoopDirection;
	int mFrameCount;
	int mCurrentFrame;
	int mXPos;
	int mYPos;
	int mFrameDelay;
	int mCurDelay;
	MyBitmap *mImage;
	int mFrameWidth;
	int mFrameHeight;
	int mXMove;
	int mYMove;
	Sprite(int srcX, int srcY, int Width, int Height, int frameDirection, int frameCount, int frameDelay, MyBitmap *image);
	void SetLoopType(int loopType);
	void NextFrame();
	void PreviousFrame();
	void SetDelay(int Delay);
	void Render(HDC pDC);
	Sprite(void);
	~Sprite(void);
};
