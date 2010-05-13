// MarioLibrary.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "MarioLibrary.h"

#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
    return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif

//// This is an example of an exported variable
//MARIOLIBRARY_API int nMarioLibrary=0;
//
//// This is an example of an exported function.
//MARIOLIBRARY_API int fnMarioLibrary(void)
//{
//	return 42;
//}

// This is the constructor of a class that has been exported.
// see MarioLibrary.h for the class definition
CMarioLibrary::CMarioLibrary()
{
	return;
}


MyBitmap::MyBitmap(LPCTSTR bmName)
{	
	HINSTANCE hInst = NULL;
	if(hBitmap)
		DeleteObject(hBitmap);
	hBitmap = (HBITMAP)LoadImage(hInst, bmName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void MyBitmap::Draw(HDC pDC, int x, int y)
{
	if(!hBitmap)
		return;
	try
	{	
		HDC dcImage;
		dcImage = CreateCompatibleDC(pDC);		
		// Select the image into the appropriate dc
		HBITMAP pOldBitmapImage = (HBITMAP)SelectObject(dcImage,hBitmap);
		BITMAP bm;
		GetObject(hBitmap, sizeof(BITMAP), &bm);
		int nWidth = bm.bmWidth;
		int nHeight = bm.bmHeight;
		BitBlt(pDC, x, y, nWidth, nHeight, dcImage, 0, 0, SRCCOPY);
		// Restore settings
		SelectObject(dcImage, pOldBitmapImage);	
		// Delete DC and Bitmap
		DeleteDC(dcImage);	
	}
	catch(char* str)
	{

	}
}

void MyBitmap::Draw(HDC pDC, int x, int y,int x1, int y1,int nWidth,int nHeight)
{
	if(!hBitmap)
		return;
	try
	{	
		HDC dcImage;
		dcImage = CreateCompatibleDC(pDC);		
		// Select the image into the appropriate dc
		HBITMAP oldBitmap = (HBITMAP)SelectObject(dcImage,hBitmap);				
		BitBlt(pDC, x, y, nWidth, nHeight, dcImage, x1, y1, SRCCOPY);			
		// Delete DC and Bitmap
		SelectObject(dcImage, oldBitmap);
		DeleteDC(dcImage);	
	}
	catch(char* str)
	{

	}
}

void MyBitmap::DrawTransparent(HDC pDC, int x, int y, COLORREF crColour)
{
	if(!hBitmap)
		return;
	try
	{		
		COLORREF crOldBack = SetBkColor(pDC,RGB(255,255,255));
		COLORREF crOldText = SetTextColor(pDC,RGB(0,0,0));
		HDC dcImage, dcTrans;
		dcImage = CreateCompatibleDC(pDC);
		dcTrans = CreateCompatibleDC(pDC);

		// Select the image into the appropriate dc
		HBITMAP pOldBitmapImage = (HBITMAP)SelectObject(dcImage,hBitmap);

		// Create the mask bitmap
		HBITMAP bitmapTrans;
		BITMAP bm;

		GetObject(hBitmap, sizeof(BITMAP), &bm);
		int nWidth = bm.bmWidth;
		int nHeight = bm.bmHeight;
		bitmapTrans = CreateBitmap(abs(nWidth),abs(nHeight),1,1,NULL);
		// Select the mask bitmap into the appropriate dc
		HBITMAP pOldBitmapTrans = (HBITMAP)SelectObject(dcTrans,bitmapTrans);

		// Build mask based on transparent colour
		SetBkColor(dcImage, crColour);
		BitBlt(dcTrans, 0, 0, nWidth, nHeight, dcImage, 0, 0, SRCCOPY );	

		// Do the work - True Mask method - cool if not actual display		
		BitBlt(pDC, x, y, nWidth, nHeight, dcImage, 0, 0, SRCINVERT);
		BitBlt(pDC, x, y, nWidth, nHeight, dcTrans, 0, 0, SRCAND);
		BitBlt(pDC, x, y, nWidth, nHeight, dcImage, 0, 0, SRCINVERT);

		// Restore settings
		SelectObject(dcImage, pOldBitmapImage);		
		SelectObject(dcTrans, pOldBitmapTrans);
		SetBkColor(pDC, crOldBack);		
		SetTextColor(pDC, crOldText);
		// Delete DC and Bitmap
		DeleteObject(dcImage);
		DeleteObject(dcTrans);		
		DeleteObject(bitmapTrans);
	}
	catch(char* str)
	{

	}
}
void MyBitmap::DrawTransparent(HDC pDC, int x, int y, int x1, int y1, int nWidth, int nHeight, COLORREF crColour)
{
	if(!hBitmap)
		return;
	try
	{
		COLORREF crOldBack = SetBkColor(pDC,RGB(255,255,255));
		COLORREF crOldText = SetTextColor(pDC,RGB(0,0,0));
		HDC dcImage, dcTrans;
		dcImage = CreateCompatibleDC(pDC);
		dcTrans = CreateCompatibleDC(pDC);

		// Select the image into the appropriate dc
		HBITMAP pOldBitmapImage = (HBITMAP)SelectObject(dcImage,hBitmap);
		// Create the mask bitmap
		HBITMAP bitmapTrans;
		BITMAP bm;

		GetObject(hBitmap, sizeof(BITMAP), &bm);		
		bitmapTrans = CreateBitmap(abs(nWidth),abs(nHeight),1,1,NULL);
		// Select the mask bitmap into the appropriate dc
		HBITMAP pOldBitmapTrans = (HBITMAP)SelectObject(dcTrans,bitmapTrans);

		// Build mask based on transparent colour

		SetBkColor(dcImage, crColour);
		BitBlt(dcTrans, 0, 0, nWidth, nHeight, dcImage,  x1, y1, SRCCOPY );

		// Do the work - True Mask method - cool if not actual display		
		BitBlt(pDC, x, y, nWidth, nHeight, dcImage, x1, y1, SRCINVERT);
		BitBlt(pDC, x, y, nWidth, nHeight, dcTrans, 0, 0, SRCAND);
		BitBlt(pDC, x, y, nWidth, nHeight, dcImage, x1, y1, SRCINVERT);

		// Restore settings
		SelectObject(dcImage, pOldBitmapImage);		
		SelectObject(dcTrans, pOldBitmapTrans);
		SetBkColor(pDC, crOldBack);		
		SetTextColor(pDC, crOldText);
		// Delete DC and Bitmap
		DeleteObject(dcImage);
		DeleteObject(dcTrans);		
		DeleteObject(bitmapTrans);
	}
	catch(char* str)
	{

	}
}

void MyBitmap::DrawTransparent(HDC pDesDC, int desX, int desY, int srcX, int srcY, int nWidth, int nHeight, COLORREF crColour, int alphaBlend)
{
	nWidth = nWidth;
	nHeight = nHeight;
	HDC hDc = CreateCompatibleDC(pDesDC);
	HBITMAP hBm = CreateCompatibleBitmap(pDesDC, nWidth, nHeight);	
	HBITMAP oldBitmap = (HBITMAP)SelectObject(hDc,hBm);		
	DrawTransparent(pDesDC, desX, desY, srcX, srcY, nWidth, nHeight, crColour);
	DrawTransparent(hDc, 0, 0, srcX, srcY, nWidth, nHeight, RGB(0,0,0));
	// Select the image into the appropriate dc
	BLENDFUNCTION func;
	func.AlphaFormat = AC_SRC_ALPHA;
	func.BlendOp = AC_SRC_OVER;
	func.BlendFlags = 0;
	func.SourceConstantAlpha = alphaBlend;		
	BOOL succ = AlphaBlend(pDesDC, desX, desY, nWidth, nHeight, hDc, 0, 0, nWidth, nHeight, func);
	
	SelectObject(hDc, oldBitmap);	
	DeleteObject(hBm);
	DeleteDC(hDc);
}

void MyBitmap::DrawBlendEllipse(HDC pDesDC, int desX, int desY, int srcX, int srcY, int nWidth, int nHeight, COLORREF crColour, int alphaBlend)
{
	nWidth = nWidth + 8;
	nHeight = nHeight + 8;
	HDC hDc = CreateCompatibleDC(pDesDC);
	HBITMAP hBm = CreateCompatibleBitmap(pDesDC, nWidth, nHeight);	
	HBITMAP oldBitmap = (HBITMAP)SelectObject(hDc,hBm);	
	DrawTransparent(pDesDC, desX, desY, srcX, srcY, nWidth-8, nHeight-8, crColour);
	Ellipse(hDc, 0, 0, nWidth, nHeight);
	BLENDFUNCTION func;
	func.AlphaFormat = AC_SRC_ALPHA;
	func.BlendOp = AC_SRC_OVER;
	func.BlendFlags = 0;
	func.SourceConstantAlpha = alphaBlend;		
	BOOL succ = AlphaBlend(pDesDC, desX-4, desY-4, nWidth, nHeight, hDc, 0, 0, nWidth, nHeight, func);

	SelectObject(hDc, oldBitmap);	
	DeleteObject(hBm);
	DeleteDC(hDc);
}

void MyBitmap::DrawTransparent(HDC pDesDC, int x, int y, int nWidth,int nHeight, HDC pSrcDC, int x1, int y1, COLORREF crColour)
{	
	try
	{
		COLORREF crOldBack = SetBkColor(pDesDC,RGB(255,255,255));
		COLORREF crOldText = SetTextColor(pDesDC,RGB(0,0,0));
		HDC dcTrans;
		dcTrans = CreateCompatibleDC(pDesDC);

		// Create the mask bitmap
		HBITMAP bitmapTrans;		
		bitmapTrans = CreateBitmap(abs(nWidth),abs(nHeight),1,1,NULL);
		// Select the mask bitmap into the appropriate dc
		HBITMAP pOldBitmapTrans = (HBITMAP)SelectObject(dcTrans,bitmapTrans);

		// Build mask based on transparent colour
		SetBkColor(pSrcDC, crColour);
		BitBlt(dcTrans, 0, 0, nWidth, nHeight, pSrcDC,  x1, y1, SRCCOPY );

		// Do the work - True Mask method - cool if not actual display		
		BitBlt(pDesDC, x, y, nWidth, nHeight, dcTrans, 0, 0, SRCAND);
		BitBlt(pDesDC, x, y, nWidth, nHeight, pSrcDC, x1, y1, SRCINVERT);

		// Restore settings		
		SelectObject(dcTrans, pOldBitmapTrans);
		SetBkColor(pDesDC, crOldBack);		
		SetTextColor(pDesDC, crOldText);
		// Delete DC and Bitmap		
		DeleteObject(dcTrans);		
		DeleteObject(bitmapTrans);
	}
	catch(char* str)
	{

	}
}

void MyBitmap::DrawRect(HDC pDesDC, int x, int y, int nWidth, int nHeight, COLORREF color, int alphaBlend)
{
	HDC hDc = CreateCompatibleDC(pDesDC);
	HBITMAP hBm = CreateCompatibleBitmap(pDesDC,nWidth,nHeight);	
	HBITMAP oldBitmap = (HBITMAP)SelectObject(hDc,hBm);	
	LOGBRUSH lb;
	memset(&lb,0,sizeof(LOGBRUSH));
	lb.lbColor = color;
	lb.lbStyle = BS_SOLID;
	HBRUSH hBrush = CreateBrushIndirect(&lb);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDc,hBrush);
	RoundRect(hDc,0,0,nWidth,nHeight,20,20);
	// Select the image into the appropriate dc
	BLENDFUNCTION func;
	func.AlphaFormat = AC_SRC_ALPHA;
	func.BlendOp = AC_SRC_OVER;
	func.BlendFlags = 0;
	func.SourceConstantAlpha = alphaBlend;		
	BOOL succ = AlphaBlend(pDesDC,x,y,nWidth,nHeight,hDc,0,0,nWidth,nHeight,func);	

	SelectObject(hDc, oldBrush);
	SelectObject(hDc, oldBitmap);
	DeleteObject(hBrush);
	DeleteObject(hBm);
	DeleteDC(hDc);
}

int MyBitmap::FlipX()
{
	BITMAPINFO bi;
	int nLine = 0;
	int* buffer;

	HDC memDC = GetDC(GetDesktopWindow());
	HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, hBitmap);
	BITMAP bm;
	memset(&bm,0,sizeof(BITMAP));
	GetObject(hBitmap, sizeof(BITMAP), &bm);

	int nWidth = bm.bmWidth;
	int nHeight = bm.bmHeight;
	bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
	bi.bmiHeader.biWidth = nWidth;
	bi.bmiHeader.biHeight = - nHeight;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biCompression = BI_RGB;
	bi.bmiHeader.biSizeImage = nWidth * 4 * nHeight;
	bi.bmiHeader.biClrUsed = 0;
	bi.bmiHeader.biClrImportant = 0;

	buffer = new int[(nWidth * 4 * nHeight)];
	nLine = GetDIBits(memDC, hBitmap, 0, nHeight, buffer, &bi, DIB_RGB_COLORS);
	if (nLine > 0)
	{
		int i=0, j=0;
		int temp=0;
		for(i=0 ; i<nHeight ; i++)
		{
			for(j=0 ; j<nWidth/2 ; j++)
			{
				temp = buffer[i*nWidth + j];
				buffer[i*nWidth + j] = buffer[i*nWidth + (nWidth - 1 - j)];
				buffer[i*nWidth + (nWidth - 1 - j)] = temp;
			}
		}
		SetDIBits(memDC, hBitmap, 0, nHeight, buffer, &bi, DIB_RGB_COLORS);
	}	
	delete []buffer;
	SelectObject(memDC,oldBitmap);
	ReleaseDC(GetDesktopWindow(),memDC);	
	return nLine;
}

int MyBitmap::FlipX(int len)
{
	BITMAPINFO bi;
	int nLine = 0;
	int* buffer;

	HDC memDC = GetDC(GetDesktopWindow());
	HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, hBitmap);
	BITMAP bm;
	memset(&bm,0,sizeof(BITMAP));
	GetObject(hBitmap, sizeof(BITMAP), &bm);

	int nWidth = bm.bmWidth;
	int nHeight = bm.bmHeight;
	bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
	bi.bmiHeader.biWidth = nWidth;
	bi.bmiHeader.biHeight = - nHeight;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biCompression = BI_RGB;
	bi.bmiHeader.biSizeImage = nWidth * 4 * nHeight;
	bi.bmiHeader.biClrUsed = 0;
	bi.bmiHeader.biClrImportant = 0;

	buffer = new int[(nWidth * 4 * nHeight)];
	nLine = GetDIBits(memDC, hBitmap, 0, nHeight, buffer, &bi, DIB_RGB_COLORS);
	if (nLine > 0)
	{
		int i=0, j=0, k=0;
		int temp=0;
		int n = nWidth/len;
		for(i=0 ; i<nHeight ; i++)
		{
			for(j=0 ; j<n ; j++)
			{
				for(k=0 ; k<len/2 ; k++)
				{
					temp = buffer[i*nWidth + j*len + k];
					buffer[i*nWidth + j*len + k] = buffer[i*nWidth + j*len + len - 1 - k];
					buffer[i*nWidth + j*len + len - 1 - k] = temp;
				}				
			}
		}
		SetDIBits(memDC, hBitmap, 0, nHeight, buffer, &bi, DIB_RGB_COLORS);
	}	
	delete []buffer;
	SelectObject(memDC,oldBitmap);
	ReleaseDC(GetDesktopWindow(),memDC);	
	return nLine;
}
int MyBitmap::FlipY()
{
	return 1;
}

Sprite::Sprite(int srcX, int srcY, int width, int height, int frameDirection, int frameCount, int delayCount, MyBitmap *image)
{
	mXPos = srcX;
	mYPos = srcY;
	mFrameWidth = width;
	mFrameHeight = height;
	mFrameDirection = frameDirection;
	mFrameCount = frameCount;
	mDelayCount = delayCount;
	mImage = image;
	mCurFrame = 0;
	mLoopType = 0;
	mCurDelay = 0;
	mLoopDirection = 1;
}
Sprite::Sprite(int srcX, int srcY, int width, int height, int frameDirection, int frameCount, int delayCount, LPCTSTR bmSrpiteName)
{	
	mXPos = srcX;
	mYPos = srcY;
	mFrameWidth = width;
	mFrameHeight = height;
	mFrameDirection = frameDirection;
	mFrameCount = frameCount;
	mDelayCount = delayCount;
	mImage = new MyBitmap(bmSrpiteName);
	mCurFrame = 0;
	mLoopType = 0;
	mCurDelay = 0;
	mLoopDirection = 1;
}
void Sprite::SetCurrentFrame(int iFrame)
{
	mCurFrame = iFrame;
}

void Sprite::SetLoopType(int loopType)
{
	if((0 <= loopType) && (loopType <= 1))
		mLoopType = loopType;
}
int Sprite::GetCurDelay()
{
	return mCurDelay;
}
void Sprite::SetCurDelay(int curDelay)
{
	mCurDelay = curDelay;
}
void Sprite::NextFrame()
{
	if(mCurDelay >= mDelayCount)
	{
		mCurDelay = 0;
		mCurFrame = (mCurFrame+1)% mFrameCount;	   		
	}
	else
		mCurDelay++;
}

void Sprite::PreviousFrame()
{
	if(mCurDelay >= mDelayCount)
	{
		mCurDelay = 0;
		mCurFrame = (mCurFrame - 1 + mFrameCount)%mFrameCount; 		
	}
	else
		mCurDelay++;	
}

void Sprite::SetDelay(int Delay)
{
	mDelayCount = Delay;
}

void Sprite::Render(HDC pDC)
{
	int imageX, imageY;
	imageX = 0;
	imageY = 0;
	if(mFrameDirection == 0)
		imageY += (mCurFrame*mFrameHeight);
	else
		imageX += (mCurFrame*mFrameWidth);		
	mImage->DrawTransparent(pDC,mXPos,mYPos,imageX,imageY,mFrameWidth,mFrameHeight,RGB(255,0,255));	
}

void Sprite::RenderBlend(HDC pDC, int alphaBlend)
{
	int imageX, imageY;
	imageX = 0;
	imageY = 0;
	if(mFrameDirection == 0)
		imageY += (mCurFrame*mFrameHeight);
	else
		imageX += (mCurFrame*mFrameWidth);		
	mImage->DrawTransparent(pDC,mXPos,mYPos,imageX,imageY,mFrameWidth,mFrameHeight,RGB(255,0,255), alphaBlend);
}
void Sprite::RenderWithEllipse(HDC pDC, int alphaBlend)
{
	int imageX, imageY;
	imageX = 0;
	imageY = 0;
	if(mFrameDirection == 0)
		imageY += (mCurFrame*mFrameHeight);
	else
		imageX += (mCurFrame*mFrameWidth);		
	mImage->DrawBlendEllipse(pDC, mXPos, mYPos, imageX,imageY,mFrameWidth,mFrameHeight,RGB(255,0,255), alphaBlend);
}
void Sprite::FlipFrame()
{
	mImage->FlipX(mFrameWidth);	
}

void Sprite::SetPos(int x, int y)
{
	mXPos = x;
	mYPos = y;
}
int IMonster::GetBit(int x, int i)
{
	return ((x>>i)&1);
}
void IMonster::NextFrame()
{
	if(mCurDelay >= mDelayCount)
	{
		mCurDelay = 0;
		mCurFrame = (mCurFrame+1)% mFrameCount;
		mAnimation->SetCurrentFrame(mCurFrame/*+mFirstFrame*/);
	}
	else
	{
		mCurDelay++;
		mAnimation->SetDelay(mCurDelay);
	}
}
int IMonster::CheckCollision(IObjectManager* objMan)
{
	int colDirect=0x00;
	int XPos2, YPos2;
	XPos2 = mXPos + mWidth - 1;
	YPos2 = mYPos + mHeight - 1;
	if(mDirection==DIRRIGHT)
	{
		if (objMan->IsBlockedAt(XPos2 + mXMove, mYPos) == 1 || objMan->IsBlockedAt(XPos2 + mXMove, YPos2) == 1)
		{
			colDirect=colDirect|0x01;
		}
	}
	if(mDirection==DIRLEFT)
	{
		if (objMan->IsBlockedAt(mXPos - mXMove, mYPos) == 1 || objMan->IsBlockedAt(mXPos - mXMove, YPos2)==1)
		{
			colDirect=colDirect|0x02;

		}
	}
	if (mJump>0)
	{
		if (mJumpDirect==1)
		{			
			if (objMan->IsBlockedAt(mXPos, mYPos - mYMove) == 1 || objMan->IsBlockedAt(XPos2, mYPos - mYMove) == 1) 
			{
				this->mYPos = objMan->GetMapTileHeight()*((mYPos - mYMove)/objMan->GetMapTileHeight()) + objMan->GetMapTileHeight();
				colDirect=colDirect|0x04;
				if (objMan->IsBlockedAt(mXPos, YPos2 + mYMove) == 1 || objMan->IsBlockedAt(XPos2, YPos2 + mYMove) == 1)
				{
					colDirect=colDirect|0x08;
					this->mYPos = objMan->GetMapTileHeight()*((YPos2 + mYMove)/objMan->GetMapTileHeight()) - mHeight;
				}
				else
					if (objMan->IsBlockedAt(mXPos, YPos2 + mYMove) == -1 || objMan->IsBlockedAt(XPos2, YPos2 + mYMove) == -1)
						colDirect = -1;
			}
		}
		else
		{
			if (objMan->IsBlockedAt(mXPos, YPos2 + mYMove) == 1 || objMan->IsBlockedAt(XPos2, YPos2 + mYMove) == 1)
			{
				colDirect=colDirect|0x08;				
				this->mYPos = objMan->GetMapTileHeight()*((YPos2 + mYMove)/objMan->GetMapTileHeight()) - mHeight;
			}
			else
				if (objMan->IsBlockedAt(mXPos, YPos2 + mYMove) == -1 || objMan->IsBlockedAt(XPos2, YPos2 + mYMove) == -1)
					colDirect = -1;
		}		
	}	
	return colDirect;
}
void IMonster::Present(HDC hDC, RECT view)
{
	if(mXPos - view.left + mWidth >= 0 && mYPos - view.top + mHeight >=0 && mAnimation != NULL)
	{
		mAnimation->mXPos = mXPos - view.left;
		mAnimation->mYPos = mYPos - view.top;
		mAnimation->Render(hDC);
	}
}

POINT IMonster::GetPos()
{
	POINT pos;
	pos.x = mXPos;
	pos.y = mYPos;
	return pos;
}