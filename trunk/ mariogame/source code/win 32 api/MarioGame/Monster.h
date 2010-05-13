#ifndef MONSTER_H
#define MONSTER_H

#include "AnimateObject.h"
#include "Sound.h"
//#include "IMonster.h"



class CMonster1 : public IMonster
{	
private:
	int mStart;
	long oldmove;
public:
	CMonster1(int x, int y, int w, int h, LPCTSTR bmSpriteName,int fd,float sp);
	int DoAction(/*CScreen* scr, */IObjectManager* objMan);
};

class CMonster2 : public IMonster
{
private:
	int mXpos1;
	int mYpos1;
	
	long oldmove;
public:
	CMonster2(int x, int y, int w, int h, LPCTSTR bmSpriteName,int fd,float sp);
	int DoAction(/*CScreen* scr, */IObjectManager* objMan);
};
class CMonster8 : public IMonster
{
private:
	int mXpos1;
	int mYpos1;

	long oldmove;
public:
	CMonster8(int x, int y, int w, int h, LPCTSTR bmSpriteName,int fd,float sp);
	int DoAction(/*CScreen* scr, */IObjectManager* objMan);
};

class CMonster3 : public IMonster
{
private:
	int mXpos1;
	int mYpos1;	
	int mStart;
		long oldmove;
public:
	CMonster3(int x, int y, int w, int h, LPCTSTR bmSpriteName,int fd,float sp);
	int DoAction(/*CScreen* scr, */IObjectManager* objMan);
};

class CMonster4 : public IMonster
{
private:
	int mXpos1;
	int mYpos1;
		int mStart;
		
		long oldmove;
public:
	CMonster4(int x, int y, int w, int h, LPCTSTR bmSpriteName,int fd,float sp);
	int DoAction(/*CScreen* scr, */IObjectManager* objMan);
};

class CMonster5 : public IMonster
{
private:
	int mXpos1;
	int mYpos1;
		
		long oldmove;
public:
	CMonster5(int x, int y, int w, int h, LPCTSTR bmSpriteName,int fd,float sp);
	int DoAction(/*CScreen* scr, */IObjectManager* objMan);
};

class CMonster6 : public IMonster
{
private:
	int mXpos1;
	int mYpos1;
		
		long oldmove;
public:
	CMonster6(int x, int y, int w, int h, LPCTSTR bmSpriteName,int fd,float sp);
	int DoAction(/*CScreen* scr, */IObjectManager* objMan);
};


class CMonster7 : public IMonster
{
private:
	int mXpos1;
	int mYpos1;

	long oldmove;
public:
	CMonster7(int x, int y, int w, int h, LPCTSTR bmSpriteName,int fd,float sp);
	int DoAction(/*CScreen* scr, */IObjectManager* objMan);
};


class CMonsterClub : public IMonster
{	
private:
	int mXPos1;
	int mYPos1;
	
	long oldmove;
public:	
	CMonsterClub(int x, int y, int w, int h, LPCTSTR bmSpriteName,int fd,float sp);
	int DoAction(/*CScreen* scr, */IObjectManager* objMan);
};
class CMonsterClubB1: public IMonster
{
private:
	int mXpos1;
	int mYpos1;
	long oldmove;
public:
	CMonsterClubB1(int x, int y, int w, int h, LPCTSTR bmSpriteName,int fd,int jd,float sp);
	int DoAction(/*CScreen* scr, */IObjectManager* objMan);
};
class CMonsterB1: public IMonster
{
private:
	int mXpos1;
	int mYpos1;
	long oldmove;
	int mChildCount;
	int mStart;
	CGameSound* actionSound;
public:
	~CMonsterB1()
	{
	}
	CMonsterB1(int x, int y, int w, int h, LPCTSTR bmSpriteName,int fd,float sp);
	int DoAction(/*CScreen* scr, */IObjectManager* objMan);
	void Present(HDC hDC, RECT view)
	{
		if(mXPos - view.left + mWidth >= 0 && mYPos - view.top + mHeight >=0 && mAnimation != NULL)
		{
			mAnimation->mXPos = mXPos - view.left;
			mAnimation->mYPos = mYPos - view.top;
			if((GetTickCount() - mLastHurt)<3000)
			{
				mAnimation->RenderWithEllipse(hDC, 100);
			}
			else
			{
				mAnimation->Render(hDC);
			}
		}
		if(mXPos - view.left + mWidth >= 0 && mYPos - view.top + mHeight >=0 && mAnimation != NULL)
		{
			if(mHealth>=0 && mHealth<=10)
				DrawHealth(hDC, mXPos - view.left + (mWidth - 50)/2, mYPos - view.top - 10, mHealth, 5);
		}		
	}
	void BeHurt()
	{
		if((GetTickCount() - mLastHurt)>=1500)
		{
			mHealth--;
			mLastHurt = GetTickCount();
		}
	}
};
class CMonsterB2: public IMonster
{	
private:
	int mXpos1;
	int mYpos1;
	long oldmove;
	int mStart;
	int mChildCount;
	CGameSound* actionSound;
public:
	~CMonsterB2()
	{
	}
	CMonsterB2(int x, int y, int w, int h, LPCTSTR bmSpriteName, int fd, float sp);
	int DoAction(/*CScreen* scr, */IObjectManager* objMan);
	void Present(HDC hDC, RECT view)
	{
		if(mXPos - view.left + mWidth >= 0 && mYPos - view.top + mHeight >=0 && mAnimation != NULL)
		{
			mAnimation->mXPos = mXPos - view.left;
			mAnimation->mYPos = mYPos - view.top;
			if((GetTickCount() - mLastHurt)<3000)
			{
				mAnimation->RenderWithEllipse(hDC, 100);
			}
			else
			{
				mAnimation->Render(hDC);
			}
		}
		if(mXPos - view.left + mWidth >= 0 && mYPos - view.top + mHeight >=0 && mAnimation != NULL)
		{
			if(mHealth>=0 && mHealth<=10)
				DrawHealth(hDC, mXPos - view.left + (mWidth - 50)/2, mYPos - view.top - 10, mHealth, 5);
		}		
	}
	void BeHurt()
	{
		if((GetTickCount() - mLastHurt)>=2000)
		{
			mHealth--;
			mLastHurt = GetTickCount();
		}
	}
};
class CMonsterB3: public IMonster
{
private:
	int mXpos1;
	int mYpos1;
	int mChildCount;	
	int mStart;
	long oldmove;
	long mLastSound;
	CGameSound* actionSound;
public:
	~CMonsterB3()
	{

	}
	CMonsterB3(int x, int y, int w, int h, LPCTSTR bmSpriteName, int fd, float sp);
	int DoAction(/*CScreen* scr, */IObjectManager* objMan);
	void Present(HDC hDC, RECT view)
	{
		if(mXPos - view.left + mWidth >= 0 && mYPos - view.top + mHeight >=0 && mAnimation != NULL)
		{
			mAnimation->mXPos = mXPos - view.left;
			mAnimation->mYPos = mYPos - view.top;
			if((GetTickCount() - mLastHurt)<3000)
			{
				mAnimation->RenderWithEllipse(hDC, 100);
			}
			else
			{
				mAnimation->Render(hDC);
			}
		}
		if(mXPos - view.left + mWidth >= 0 && mYPos - view.top + mHeight >=0 && mAnimation != NULL)
		{
			if(mHealth>=0 && mHealth<=10)
				DrawHealth(hDC, mXPos - view.left + (mWidth - 50)/2, mYPos - view.top - 10, mHealth, 10);
		}		
	}
	void BeHurt()
	{
		if((GetTickCount() - mLastHurt)>=3000)
		{
			mHealth--;
			mLastHurt = GetTickCount();
		}
	}
};


#endif
