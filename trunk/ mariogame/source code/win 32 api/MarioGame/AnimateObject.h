#pragma once
#include "GameObject.h"

class CAnimateObject : public CGameObject
{
protected:
	Sprite* mAnimation;
	//MyBitmap* bmSprite; // Anh cua sprite		
	int mFirstFrame;
	int mCurFrame;
	int mCurDelay;
	int mDelayCount;
	int mFrameCount;
	int GetBit(int x, int i);
	void NextFrame();
public:
	int FaceDirection() const { return mDirection; }
	void FaceDirection(int val) { mDirection = val; }
public:
	CAnimateObject();
	CAnimateObject(int x, int y, int w, int h, LPCTSTR bmSpriteName,int fd);
	~CAnimateObject();
	virtual int DoAction(/*CScreen* scr, */CObjectManager* objMan);
	virtual void Present(HDC hDC, RECT view);		
};

class CMovableAnimateObject : public CAnimateObject
{
protected:	
	int mXMove;
	int mYMove;
	int mJumpDirect; // 0: huong xuong, 1: huong len
	int mJump;
	virtual int CheckCollision(IObjectManager* objMan);	
public:	
	CMovableAnimateObject();
	~CMovableAnimateObject();
	int DoAction(/*CScreen* scr, */CObjectManager* objMan);	
};

class CMovelessAnimateObject : public CAnimateObject
{
protected:	
public:
public:
	CMovelessAnimateObject();
	~CMovelessAnimateObject();
	int DoAction(/*CScreen* scr, */CObjectManager* objMan);	
};
