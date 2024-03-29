#pragma once
#include "AnimateObject.h";
#include "NoAnimateObject.h"

class CCoin : public CMovelessAnimateObject
{
protected:	
	void NextFrame();
public:
	CCoin();
	CCoin(int x, int y, int w, int h, LPCTSTR bmSpriteName);
	~CCoin();
	int DoAction(/*CScreen* scr, */CObjectManager* objMan);
};

class CTrunk : public CMovelessNoAnimateObject
{
protected:
	int mOpened; // Đã được mở hay chưa
	int mInnerObjTileIdx;
public:
	CTrunk(int x, int y, int w, int h, LPCTSTR bmSpriteName, int innerObjTileIdx, int tileIdx = ITRUNK);
	void Open(CObjectManager* objMan);
	~CTrunk(void);	
};

class CMushroom : public CMovableNoAnimateObject
{
protected:		
public:
	CMushroom();
	CMushroom(int x, int y, int w, int h, LPCTSTR bmSpriteName, int tileIdx = IMUSHROOM);
	~CMushroom();	
	int DoAction(/*CScreen* scr, */CObjectManager* objMan);
};

class CFlower : public CMovelessAnimateObject
{
protected:
public:
	CFlower(int x, int y, int w, int h, LPCTSTR bmSpriteName);
	~CFlower()
	{

	}
};

class CStar : public CMovableAnimateObject
{
private:
	int mXpos1;
	int mYpos1;
public:
	CStar(int x, int y, int w, int h, LPCTSTR bmSpriteName);
	int DoAction(/*CScreen* scr, */CObjectManager* objMan);
};