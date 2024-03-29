#ifndef CHARACTER_H
#define CHARACTER_H

#include "AnimateObject.h"
#include "ObjectManager.h"	   
#include "GTimer.h"

class CCharacter : public CMovableAnimateObject // Mario
{
protected:	
	static const int XJUMPMOVE = 4;
	static const int XWALKMOVE = 3;
	static const int YMOVE = 8;
	float mXSpeed;
	float mYSpeed;	
	int mLastJump;
	int mLastFire;
		
	int mWalkRight;
	int mWalkLeft;
	int mDie;	
	int mDefJumpStep;
	int mDefWalkStep;

	int mIsSit;
	
	POINT mBornPos;
	vector<POINT> mReBornPos;
	CGameSound *eventSound;

	int mLife;
	int mHealth;
	int mHaveFlower;
	int mHaveStarTime; // in miliseconds
	int mLastHurt;
	int mCoinCount;	
	MyBitmap *mCoinIcon;
	MyBitmap *mLifeIcon;
	MyBitmap *mFlowerIcon;
	int GetBit(int x, int i);
	void DieFrame();
	void JumpUpFrame();
	void JumpDownFrame();
	void SitFrame();
	void StandFrame();
	void StandUpFrame(int iDelay=0);
	void NextFrame();
	void DrawHealth(HDC memDC, int x, int y, int curr, int total)
	{
		COLORREF color = RGB(200,0,0);
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
	CCharacter();
	CCharacter(int x, int y, int w, int h, LPCTSTR bmSpriteName, vector<POINT> reBornPos);
	~CCharacter();
	void Init(int x, int y, int w, int h, LPCTSTR bmSpriteName, vector<POINT> reBornPos);
	void Present(HDC hDC, RECT view);
	void Die();
	int IsDead();
	void Jump(int jumpStep);
	void Fall();
	void StopJump();
	void Sit(); // Squat
	void WalkLeft(int walkStep);
	void WalkRight(int walkStep);
	void FireGun(CObjectManager* objMan);
	void GetCoin()
	{
		mCoinCount++;
		if(mCoinCount>=50)
		{
			mLife++;
			mCoinCount = 0;
			eventSound = new CGameSound("Music\\getbonnus.wav");
			eventSound->Play(0);
		}
		eventSound = new CGameSound("Music\\coin.wav");
		eventSound->Play(0);
	}
	void SpeedUp(float xSpeed, float ySpeed)
	{
		mXSpeed = xSpeed;
		mYSpeed = ySpeed;			
	}
	void GetStar()
	{
		SpeedUp(1.75, 1.25);
		mHaveStarTime = CGTimer::Time();
		eventSound = new CGameSound("Music\\getbonnus.wav");
		eventSound->Play(0);
	}
	void GetFlower()
	{
		if(mHaveFlower == 1)
		{
			mCoinCount += 10;
			if(mCoinCount>=50)
			{
				mLife++;
				mCoinCount = 0;
			}
		}
		mHaveFlower = 1;
		eventSound = new CGameSound("Music\\getbonnus.wav");
		eventSound->Play(0);
	}
	void GetMushroom()
	{
		if(mHealth<5)
			mHealth++;
		else
		{
			mCoinCount+=5;
			if(mCoinCount>=50)
			{
				mLife++;
				mCoinCount = 0;
			}
		}
		eventSound = new CGameSound("Music\\getbonnus.wav");
		eventSound->Play(0);
	}
	void GoToOldPos()
	{
		//mDirection = 1;
		int n = mReBornPos.size();
		for(int i=n-1 ; i>=0 ; i--)
		{
			if(mXPos > mReBornPos[i].x || abs(mXPos - mReBornPos[i].x) < 500)
			{
				mXPos = mReBornPos[i].x;
				mYPos = mReBornPos[i].y;
				return;
			}
		}
		mXPos = mBornPos.x;
		mYPos =	mBornPos.y;
	}
	void GoTo(int x, int y)
	{
		mXPos = x;
		mYPos = y;
	}
	void BeHurt()
	{
		if(CGTimer::Time() - mLastHurt > 2000)
		{
			mLastHurt = CGTimer::Time();
			if(mHealth > 1)
				mHealth--;
			else
				Die();
		}
	}
	int FaceDirection() const { return mDirection; }
	void FaceDirection(int val) { mDirection = val; }
	int DoAction(CScreen* scr, CObjectManager* objMan);
	//void Present(HDC hDC, RECT view);	
	void JumpDirect(int val) { mJumpDirect = val;}
	int JumpDirect() { return mJumpDirect;}
};


class CMarioClub : public CMovableAnimateObject
{	
private:
	int mXPos1;
	int mYPos1;
public:	
	CMarioClub(int x, int y, int w, int h, LPCTSTR bmSpriteName,int fd);
	int DoAction(CObjectManager* objMan);
};
#endif