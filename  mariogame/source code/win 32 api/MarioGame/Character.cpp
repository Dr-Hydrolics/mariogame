#include "StdAfx.h"
#include "Character.h"
#include "Club.h"
#include "Text.h"
#include "GTimer.h"
#include "Game.h"

CCharacter::CCharacter()
{
	mType = TCHARACTER;
	mXPos = 0;
	mYPos = 0;
	mWidth = 0;
	mHeight = 0;
	mXMove = 12;
	mYMove = 12;
	mWalkLeft = mWalkRight = mJump = 0;
	mDefWalkStep = 10;
	mDefJumpStep = 15;
	mAnimation = NULL;	
	mDirection = DIRRIGHT;
	mCurFrame = 0;
	mCurDelay = 0;
	mDelayCount = 0;
	mFrameCount = 0;
}

CCharacter::CCharacter(int x, int y, int w, int h, LPCTSTR bmSpriteName, vector<POINT> reBornPos)
{
	mType = TCHARACTER;
	mXPos = x;
	mYPos = y;
	mBornPos.x = x;
	mBornPos.y = y;
	mWidth = w;
	mHeight = h;
	mXMove = XWALKMOVE;
	mYMove = YMOVE;
	mWalkLeft = mWalkRight = mJump = 0;
	mDefWalkStep = 4;
	mDefJumpStep = 20;
	mLife = 3;
	mHealth = 5;
	mFirstFrame = 1;
	mCurFrame = 0;
	mCurDelay = 0;
	mDelayCount = 1;
	mFrameCount = 4;
	mAnimation = new Sprite(mXPos, mYPos, mWidth, mHeight, 1, mFrameCount, mDelayCount, bmSpriteName);
	mDirection = DIRRIGHT;
	mIsSit = 0;
	mDie = 0;
	mLastHurt = mLastFire = mLastJump = CGTimer::Time();
	mXSpeed = 1;
	mYSpeed = 1;
	mHaveFlower = 0;
	mHaveStarTime = 0;
	mCoinCount = 0;
	mFlowerIcon = new MyBitmap(_T("flower.bmp"));  
	mCoinIcon = new MyBitmap(_T("coinicon.bmp"));
	mLifeIcon = new MyBitmap(_T("lifeicon.bmp"));	
	int n = reBornPos.size();
	mReBornPos.clear();
	for(int i=0 ; i<n ; i++)
	{
		POINT temp;
		temp.x = reBornPos[i].x;
		temp.y = reBornPos[i].y;
		mReBornPos.push_back(temp);
	}
}
void CCharacter::Init(int x, int y, int w, int h, LPCTSTR bmSpriteName, vector<POINT> reBornPos)
{
	mType = TCHARACTER;
	mXPos = x;
	mYPos = y;
	mBornPos.x = x;
	mBornPos.y = y;
	mWidth = w;
	mHeight = h;
	mXMove = XWALKMOVE;
	mYMove = YMOVE;
	mWalkLeft = mWalkRight = mJump = 0;
	mDefWalkStep = 4;
	mDefJumpStep = 20;
	mFirstFrame = 1;
	mCurFrame = 0;
	mCurDelay = 0;
	mDelayCount = 1;
	mFrameCount = 4;
	mAnimation = new Sprite(mXPos, mYPos, mWidth, mHeight, 1, mFrameCount, mDelayCount, bmSpriteName);
	mDirection = DIRRIGHT;
	mIsSit = 0;
	mDie = 0;
	mLastHurt = mLastFire = mLastJump = CGTimer::Time();	
	mHaveStarTime = 0;	
	mXSpeed = 1;
	mYSpeed = 1;
	int n = reBornPos.size();
	mReBornPos.clear();
	for(int i=0 ; i<n ; i++)
	{
		POINT temp;
		temp.x = reBornPos[i].x;
		temp.y = reBornPos[i].y;
		mReBornPos.push_back(temp);
	}
}

CCharacter::~CCharacter()
{
	if(mAnimation)
	{
		delete mAnimation;
		mAnimation = NULL;
	}
}
void CCharacter::Present(HDC hDC, RECT view)
{
	//CMovableAnimateObject::Present(hDC, view);	
	mLifeIcon->DrawTransparent(hDC, 10, 8, RGB(255,0,255));
	mCoinIcon->DrawTransparent(hDC, (view.right-view.left)/2 - 25, 10, RGB(255,0,255));
	CText::Draw(mCoinCount, 3, hDC, (view.right-view.left)/2 + 5, 0);
	if(mLife>0)
		CText::Draw(mLife, 3, hDC, 30, 0);
	DrawHealth(hDC, 10, 33, mHealth, 5);
	if(mHaveFlower)
	{			 
		mFlowerIcon->DrawTransparent(hDC, 10, 38, RGB(255,0,255));
	}
	if(mXPos - view.left + mWidth >= 0 && mYPos - view.top + mHeight >=0 && mAnimation != NULL)
	{
		mAnimation->mXPos = mXPos - view.left;
		mAnimation->mYPos = mYPos - view.top;		
		if(CGTimer::Time() - mLastHurt <= 2000)
		{			
			mAnimation->RenderWithEllipse(hDC, 100);
			return;
		}
		if(mDie != 0)
		{											
			mAnimation->RenderWithEllipse(hDC, 100);
			return;
		}		
		if(mHaveStarTime > 0)
		{
			mAnimation->RenderBlend(hDC, 200);
			return;
		}				
		mAnimation->Render(hDC);
	}
}
int CCharacter::DoAction(CScreen* scr, CObjectManager* objMan)
{
	if(mHaveStarTime != 0 && CGTimer::Time() - mHaveStarTime>30000)
	{
		SpeedUp(1,1);
		mHaveStarTime = 0;
	}
	if(KEY_DOWN(CGame::RIGHT))
	{				
		WalkRight(mDefWalkStep);
	}
	if(KEY_DOWN(CGame::LEFT))
	{		
		WalkLeft(mDefWalkStep);
	}
	if(KEY_DOWN(CGame::JUMP))
	{		
		if(CGTimer::Time() - mLastJump >= 300)
		{			
			Jump(mDefJumpStep);
		}
	}

	if(KEY_DOWN(CGame::SIT))
	{
		Sit();
	}
	if(KEY_DOWN(CGame::FIRE) && mHaveFlower == 1)
	{
		if(CGTimer::Time() - mLastFire > 200)
		{
			mLastFire = CGTimer::Time();
			FireGun(objMan);			
		}		
	}
	int coll = 0;
	if(mDie == 0)
	{
		mXMove *= mXSpeed;
		mYMove *= mYSpeed;
		coll = CheckCollision(objMan);		
		mXMove /= mXSpeed;
		mYMove /= mYSpeed;
	}
	if(coll == -1) // Roi xuong vuc sau -> Die
	{
		Die();
	}
	if (GetBit(coll,0)==1) // bi can ben phai
		mWalkRight=0;
	if (GetBit(coll,1)==1) // bi can ben trai
		mWalkLeft=0;
	//if (GetBit(i,2)==1) // bi can phia tren
	//{
	//	mJump=mDefJumpStep;
	//	mJumpDirect=0;
	//}
	if (GetBit(coll,3)==1 && mJumpDirect==0) // bi can phia duoi
	{
		mJump = 0;
		if(mWalkLeft==0 && mWalkRight==0)
			StandFrame();
	}
	if(mDie > 0)
	{
		mDie--;
		mAnimation->mYPos -= mYMove;
		mYPos -= mYMove;
		if(mDie == 0)
		{
			mDie = -mDefJumpStep/2;
		}
		DieFrame();			
		return 1;
	}
	if(mDie < 0)
	{
		mAnimation->mYPos += mYMove;
		mYPos += mYMove;
		if(mYPos >= scr->ViewPort().bottom)
		{
			mDie = 0;
			StandFrame();
			if(mLife <= 0)
				return -1;
			else
				return 0;
		}	
		DieFrame();
		return 1;		
	}
	if(mJump>0)
	{		
		if (mJumpDirect==1)
		{
			if(GetBit(coll,2)==0)
			{
				mJump--;	
				mAnimation->mYPos -= mYSpeed*mYMove;
				mYPos -= mYSpeed*mYMove;			
				if (mJump==0)
				{
					mJump=mDefJumpStep;
					mJumpDirect=0;							
				}			
				JumpUpFrame();
			}
			else
			{
				mJump=mDefJumpStep;
				mJumpDirect = 0;			
			}
		}
		else
		{		
			JumpDownFrame();
			mAnimation->mYPos += mYSpeed*mYMove;
			mYPos += mYSpeed*mYMove;				
		}
		mXMove = XJUMPMOVE;
	}
	else
		mXMove = XWALKMOVE;
	if(mWalkRight>0)
	{	
		// Xu ly truong hop Mario di tu bac thang cao xuong thap
		if(GetBit(coll,3)==0 && mJump==0)
		{
			mJump = 1;
			mJumpDirect=0;
		}
		mWalkRight--;		
		if(mAnimation->mXPos+mXSpeed*mXMove<=scr->Center())
		{
			mXPos += mXSpeed*mXMove;
		}
		else
		{
			if ( scr->MoveViewPortRight(mXSpeed*mXMove)==1)
			{
				mXPos += mXSpeed*mXMove;
			}
			else
			{
				if( mXPos+mXSpeed*mXMove+mWidth<=scr->GetMapSize().x)
				{
					mXPos +=mXSpeed* mXMove;
				}
			}
		}	
		if(mWalkRight==0)
		{
			StandFrame();
		}
		else if(mJump==0)
			NextFrame();
	}	
	if(mWalkLeft>0)
	{	
		// Xu ly truong hop Mario di tu bac thang cao xuong thap
		if(GetBit(coll,3)==0 && mJump==0)
		{
			mJump=1;
			mJumpDirect=0;
		}
		mWalkLeft--;		
		if(mAnimation->mXPos-mXSpeed*mXMove>=scr->Center())
		{
			mXPos -= mXSpeed*mXMove;
		}
		else
		{
			if (scr->MoveViewPortLeft(mXSpeed*mXMove)==1)
			{
				mXPos -= mXSpeed*mXMove;
			}
			else
			{
				if( mXPos-mXMove>=0)
				{
					mXPos -= mXSpeed*mXMove;
				}
			}
		}
		if(mWalkLeft==0)
		{
			StandFrame();
		}
		else if(mJump==0)
			NextFrame();
	}
	if (mIsSit==1)//ngoi
	{		
		StandUpFrame();
		if (mCurDelay == 0)
		{
			mIsSit=0;//ngoi			
		}
	}	
	return 1;
}
int CCharacter::IsDead()
{
	return mDie != 0;
}
void CCharacter::Jump(int jumpStep)
{
	if(mJump==0 && mDie == 0)
	{
		mLastJump = CGTimer::Time();
		mJump = jumpStep;
		mJumpDirect = 1;
		JumpUpFrame();
	}	
}
void CCharacter::Fall()
{
	mJumpDirect = 0;
}
void CCharacter::StopJump()
{
	mJump = 0;
}
void CCharacter::Sit()
{
	if(mJump == 0 && mDie==0)
	{
		mIsSit=1;//ngoi
		SitFrame();
	}
}
void CCharacter::WalkLeft(int walkStep)
{
	if (mIsSit==0 && mDie==0) 
	{
		if(mDirection == DIRRIGHT)
		{
			mAnimation->FlipFrame();
			mDirection = DIRLEFT;				
		}			
		mWalkLeft = walkStep;	
	}
}
void CCharacter::WalkRight(int walkStep)
{
	if (mIsSit==0 && mDie==0) 
	{
		if(mDirection == DIRLEFT)
		{
			mAnimation->FlipFrame();
			mDirection = DIRRIGHT;				
		}						
		mWalkRight = walkStep;			
	}
}
void CCharacter::Die()
{
	if(mDie == 0)
	{
		/*mOldX = mXPos;
		mOldY = mYPos;*/
		mDie = mDefJumpStep/2;
		mJump = 0;
		mJumpDirect = 0;
		mLife--;
		mHealth = 5;
		mHaveStarTime = 0;
		SpeedUp(1,1);
		mHaveFlower = 0;
		if(mLife <= 0)
		{
			//Game over
		}
		else
		{
			// quay ve vi tri dau
		}
		eventSound = new CGameSound("Music\\die.wav");
		eventSound->Play(0);
	}		
}

void CCharacter::DieFrame()
{
	if(mCurDelay>=mDelayCount)
	{
		mCurFrame = 6;
		mCurDelay = 0;
		mAnimation->SetCurrentFrame(mCurFrame);
	}
	else
		mCurDelay++;
}
void CCharacter::JumpUpFrame()
{
	if(mCurDelay>=mDelayCount)
	{
		mCurFrame = 3;
		mCurDelay = 0;
		mAnimation->SetCurrentFrame(mCurFrame);
	}
	else
		mCurDelay++;
}
void CCharacter::JumpDownFrame()
{
	if(mCurDelay>=mDelayCount)
	{
		mCurFrame = 4;
		mCurDelay = 0;
		mAnimation->SetCurrentFrame(mCurFrame);
	}
	else
		mCurDelay++;
}
void CCharacter::StandFrame()
{	
	mCurFrame = 0;
	mCurDelay = 0;
	mAnimation->SetCurrentFrame(mCurFrame);	
}
void CCharacter::SitFrame()
{
	mCurFrame = 5;
	mCurDelay = 0;
	mAnimation->SetCurrentFrame(mCurFrame);	
	mAnimation->SetDelay(mCurDelay);	
}
void CCharacter::StandUpFrame(int iDelay /*=1*/)
{
	if(mCurDelay >= mDelayCount || iDelay == 1)
	{
		mCurDelay=0;
		mCurFrame=0;
		mAnimation->SetCurrentFrame(mCurFrame);
	}
	else
	{
		mCurDelay++;
		mAnimation->SetDelay(mCurDelay);

	}
}
void CCharacter::NextFrame()
{
	if(mCurDelay >= mDelayCount)
	{
		mCurDelay = 0;
		mCurFrame = (mCurFrame+1)% mFrameCount;
		mAnimation->SetCurrentFrame(mCurFrame+1);
	}
	else
	{
		mCurDelay++;	
		mAnimation->SetDelay(mCurDelay);
	}
}
void CCharacter::FireGun(CObjectManager* objMan)
{
	CGameObject* obj = new CMarioClub(mXPos, mYPos + mHeight/2 - 11, 26, 23, _T("goldaxe.bmp"), mDirection);
	objMan->AddMarioClub(obj);
}

int CCharacter::GetBit(int x, int i)
{
	return ((x>>i)&1);
}


CMarioClub::CMarioClub(int x, int y, int w, int h, LPCTSTR bmSpriteName,int fd)
{	
	mFamily = FANIMATEMOVABLE;
	mType = TMARIOCLUB;
	mDirection = fd;	
	mXPos = x;
	mYPos = y;
	mWidth = w;
	mHeight = h;
	mCurFrame = 0;
	mCurDelay = 0;
	mDelayCount = 1;
	mFrameCount = 9;
	mAnimation = new Sprite(mXPos, mYPos, mWidth, mHeight, 1, mFrameCount, mDelayCount, bmSpriteName);
	mXMove = 8;
	mYMove = 3;
	mXPos1=x;
	mYPos1=0;
}

int CMarioClub::DoAction(/*CScreen* scr, */CObjectManager* objMan)
{		
	int moveX;
	int i = CheckCollision(objMan);
	if(mDirection==DIRRIGHT)
	{
		if(GetBit(i,0)==1)
		{	
			return -1;
		}
		else
			if(abs(mXPos-mXPos1)>=300 )
			{
				return -1;			
			}
			else
			{	
				mXPos = mXPos + mXMove;
				mYPos1 = (mYPos1 + 1)%6;
				if(mYPos1-3 < 0)
				{
					mYPos = mYPos + mYMove;
				}
				else
				{
					mYPos = mYPos - mYMove;
				}
			}
	}
	if(mDirection==DIRLEFT)
	{	
		if (GetBit(i,1)==1) // bi can ben trai
		{
			return -1;
		}
		else
		{	
			if(abs(mXPos-mXPos1)>=300 )
			{
				return -1;			
			}
			else
			{
				mXPos = mXPos - mXMove;
				mYPos1 = (mYPos1 + 1)%6;
				if(mYPos1-3 < 0)
				{
					mYPos = mYPos + mYMove;
				}
				else
				{
					mYPos = mYPos - mYMove;
				}
			}
		}
	}
	NextFrame();
	return 1;
}
