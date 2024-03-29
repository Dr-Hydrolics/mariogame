#pragma once
#include "GameObject.h"

class CNoAnimateObject : public CGameObject
{
protected:
	int mTileIndex;
	MyBitmap* bmSprite;
	int GetBit(int x, int i)
	{
		return ((x>>i)&1);
	}
public:
	CNoAnimateObject();
	CNoAnimateObject(int x, int y, int w, int h, LPCTSTR bmSpriteName, int tileIdx, int type);
	~CNoAnimateObject(void);
	void Present(HDC hDC, RECT view);
	virtual int DoAction(/*CScreen* scr, */CObjectManager* objMan);
};

class CMovableNoAnimateObject: public CNoAnimateObject
{
protected:	
	int mXMove;
	int mYMove;
	int mJumpDirect; // 0: huong xuong, 1: huong len
	int mJump;
	virtual int CheckCollision(CObjectManager* objMan);
public:
	CMovableNoAnimateObject()
	{

	}
	~CMovableNoAnimateObject()
	{

	}
};

class CMovelessNoAnimateObject : public CNoAnimateObject
{
public:
	CMovelessNoAnimateObject()
	{

	}
	~CMovelessNoAnimateObject()
	{

	}
};


