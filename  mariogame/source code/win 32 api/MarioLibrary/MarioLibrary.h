/*
This file contains classes, interfaces for implementing mario game, includes following classes and interface:
MyBitmap
Sprite
IMonster
IObjectManager
*/
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MARIOLIBRARY_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MARIOLIBRARY_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#pragma once
#ifdef MARIOLIBRARY_EXPORTS
#define MARIOLIBRARY_API __declspec(dllexport)
#else
#define MARIOLIBRARY_API __declspec(dllimport)
#endif

// This class is exported from the MarioLibrary.dll
class MARIOLIBRARY_API CMarioLibrary {
public:
	CMarioLibrary(void);
	// TODO: add your methods here.
};

class MARIOLIBRARY_API MyBitmap
{
public:
	MyBitmap(void)
	{
	}
	~MyBitmap(void)
	{
		if(hBitmap)
			DeleteObject(hBitmap);
	}
	MyBitmap(LPCTSTR str);
	HBITMAP hBitmap;
	void Draw(HDC pDC, int x, int y);
	void Draw(HDC pDC, int x, int y,int x1, int y1,int nWidth,int nHeight);
	void DrawTransparent(HDC pDC, int desX, int desY, COLORREF crColour);
	void DrawTransparent(HDC pDC, int desX, int desY, int srcX, int srcY, int width, int height, COLORREF crColour);
	static void DrawTransparent(HDC pDesDC, int x, int y, int nWidth, int nHeight, HDC pSrcDC, int x1, int y1, COLORREF crColour);
	static void DrawRect(HDC pDesDC, int x, int y, int nWidth, int nHeight, COLORREF color, int alphaBlend); // Ve hinh chu nhat voi che do alpha blending
	int FlipX();
	int FlipX(int len);
	int FlipY();
	void DrawTransparent(HDC pDC, int desX, int desY, int srcX, int srcY, int width, int height, COLORREF crColour, int alphaBlend);
	void DrawBlendEllipse(HDC pDesDC, int desX, int desY, int srcX, int srcY, int nWidth, int nHeight, COLORREF crColour, int alphaBlend);
};

class MARIOLIBRARY_API Sprite
{
	int mFrameDirection; //0 vertical, 1 horizontal
	int mLoopType; //0 loop back to begining, 1 bounce between begin and end
	int mLoopDirection;	
	int mFrameCount;	// So frame trong 1 sprite
	int mCurFrame;	// Frame se duoc hien thi len man hinh
	int mDelayCount;	// So lan lap lai toi da cua 1 frame trong qua trinh chuyen frame
	int mCurDelay;	// Frame hien tai da lap lai duoc bao nhieu lan
	MyBitmap *mImage;	//	Anh cua sprite
	int mFrameWidth;	// Chieu rong cua 1 frame
	int mFrameHeight;	// Chieu cao cua 1 frame	

public:
	int mXPos;	// Vi tri X cua Sprite tren man hinh
	int mYPos;	// Vi tri Y cua Sprite tren man hinh
	Sprite(int srcX, int srcY, int Width, int Height, int frameDirection, int frameCount, int frameDelay, MyBitmap *image);
	Sprite(int srcX, int srcY, int Width, int Height, int frameDirection, int frameCount, int frameDelay, LPCTSTR bmSrpiteName);
	void SetLoopType(int loopType);
	void SetCurrentFrame(int iFrame);
	void NextFrame();
	void PreviousFrame();
	void SetDelay(int Delay);
	void Render(HDC pDC);		// Hien thi frame len man hinh
	void RenderBlend(HDC pDC, int alphaBlend);
	void RenderWithEllipse(HDC pDC, int alphaBlend);
	void FlipFrame();
	void SetPos(int x, int y);
	int GetCurDelay();
	void SetCurDelay(int curDelay);
	int GetFrameDelay()
	{
		return mDelayCount;
	}
	Sprite(void)
	{
	}
	~Sprite(void)
	{
	}

};

class IObjectManager;
class CObjectManager;
class MARIOLIBRARY_API IMonster
{
protected:	
	enum MonsterType {TMONSTER = 1, TMONSTERCLUB = 4, TMARIOCLUB = 9};
	enum MonsterDirection {DIRLEFT = 0, DIRRIGHT = 1};
	// Goc tren trai man hinh co toa do: (0, 0)
	int mXPos; // Vi tri theo chieu ngang cua doi tuong tren ban do
	int mYPos;	// Vi tri theo chieu doc cua doi tuong tren ban do
	int mWidth; // Chieu rong cua doi tuong
	int mHeight; // Chieu dai cua doi tuong
	int mType;	// Loai cua doi tuong
	int mFamily;
	int mDirection; // Huong cua doi tuong	
	int mXMove;
	int mYMove;
	int mJumpDirect; // 0: huong xuong, 1: huong len
	int mJump;
	Sprite* mAnimation;
	int mFirstFrame;
	int mCurFrame;
	int mCurDelay;
	int mDelayCount;
	int mFrameCount;
	float mSpeed;
	int mLastHurt;
	int mHealth;
	int GetBit(int x, int i);
	void NextFrame();
	int CheckCollision(IObjectManager* objMan);
	void DrawHealth(HDC memDC, int x, int y, int curr, int total)
	{
		COLORREF color = RGB(200,0,200);
		int w = 50;		
		RECT rect;		
		rect.left = x+1;
		rect.top = y+1;
		rect.right = x + (w*curr)/total - 1;
		rect.bottom = y+7;
		HBRUSH brush = CreateSolidBrush(RGB(192,192,192));
		HBRUSH oldBrush = (HBRUSH)SelectObject(memDC, brush);
		HPEN pen = CreatePen(0,1,RGB(192,192,192));
		HPEN oldPen = (HPEN)SelectObject(memDC, pen);
		Rectangle(memDC, x, y, x+w, y+8);		
		HBRUSH colorBrush = CreateSolidBrush(color);
		FillRect(memDC, &rect, colorBrush);	
		int d = w/total;
		for(int i=1 ; i<total ; i++)
		{
			POINT p;
			MoveToEx(memDC, x+i*d, y, &p);
			LineTo(memDC, x+i*d, y+8);
		}
		SelectObject(memDC, oldBrush);
		DeleteObject(brush);		
		SelectObject(memDC, oldPen);
		DeleteObject(pen);
		DeleteObject(colorBrush);
	}
public:
	friend class CObjectManager;
	virtual ~IMonster()
	{
	}
	virtual void BeHurt()
	{
		if((GetTickCount() - mLastHurt)>=1000)
		{
			mHealth--;
			mLastHurt = GetTickCount();
		}
	}
	virtual void Present(HDC hDC, RECT view);
	int Family() const { return mFamily; }
	void Family(int val) { mFamily = val; }
	int Type() const { return mType; }
	void Type(int val) { mType = val; }
	int Direction() const { return mDirection; }
	void Direction(int val) { mDirection = val; }	

	POINT GetPos();

	virtual int DoAction(IObjectManager* objMan) = 0;
};

class MARIOLIBRARY_API IObjectManager
{
public:
	virtual ~IObjectManager(){}
	virtual POINT GetMarioPos() = 0;
	virtual int IsBlockedAt(int xPos, int yPos) = 0;
	virtual void AddMonster(IMonster* obj) = 0;
	virtual int GetMapTileWidth() = 0;
	virtual int GetMapTileHeight() = 0;
};
//
//extern MARIOLIBRARY_API int nMarioLibrary;
//
//MARIOLIBRARY_API int fnMarioLibrary(void);
