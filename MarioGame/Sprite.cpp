#include "StdAfx.h"
#include "Sprite.h"

Sprite::Sprite(void)
{
}

Sprite::~Sprite(void)
{
}


Sprite::Sprite(int srcX, int srcY, int width, int height, int frameDirection, int frameCount, int frameDelay, MyBitmap *image)
{
	mXPos = srcX;
	mYPos = srcY;
	mFrameWidth = width;
	mFrameHeight = height;
	mFrameDirection = frameDirection;
	mFrameCount = frameCount;
	mFrameDelay = frameDelay;
	mImage = image;
	mCurrentFrame = 0;
	mLoopType = 0;
	mCurDelay = 0;
	mLoopDirection = 1;
	mXMove = 3;
	mYMove = 3;
}

void Sprite::SetLoopType(int loopType)
{
	if((0 <= loopType) && (loopType <= 1))
		mLoopType = loopType;
}

void Sprite::NextFrame()
{
	if(mCurDelay >= mFrameDelay)
	{
		mCurDelay = 0;
		mCurrentFrame = (mCurrentFrame+1)% mFrameCount;
		/*mCurrentFrame += mLoopDirection;
		if(mCurrentFrame >= mFrameCount && mLoopType == 0)
			mCurrentFrame = 0;
		if(mCurrentFrame >= mFrameCount && mLoopType == 1) 
		{
			mLoopDirection *= -1;
			mCurrentFrame = mFrameCount-1;
		}
		if(mCurrentFrame < 0 && mLoopType == 1) 
		{
			mLoopDirection *= -1;
			mCurrentFrame = 1;
		}		*/
	}
	else
		mCurDelay++;
}

void Sprite::PreviousFrame()
{
	if(mCurDelay >= mFrameDelay)
	{
		mCurDelay = 0;
		mCurrentFrame = (mCurrentFrame - 1+mFrameCount)%mFrameCount;
		/*mCurrentFrame -= mLoopDirection;
		if(mCurrentFrame < 0 && mLoopType == 0)
			mCurrentFrame = mFrameCount-1;
		if(mCurrentFrame >= mFrameCount && mLoopType == 1) 
		{
			mLoopDirection *= -1;
			mCurrentFrame = mFrameCount-1;
		}
		if(mCurrentFrame < 0 && mLoopType == 1) 
		{
			mLoopDirection *= -1;
			mCurrentFrame = 1;
		}*/
	}
	else
		mCurDelay++;	
}

void Sprite::SetDelay(int Delay)
{
	mFrameDelay = Delay;
}

void Sprite::Render(HDC pDC)
{
	int imageX, imageY;
	imageX = 0;
	imageY = 0;
	if(mFrameDirection == 0)
		imageY += (mCurrentFrame*mFrameHeight);
	else
		imageX += (mCurrentFrame*mFrameWidth);	
	mImage->DrawTransparent(pDC,mXPos,mYPos,imageX,imageY,mFrameWidth,mFrameHeight,RGB(255,255,255));	
}

