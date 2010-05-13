#include "StdAfx.h"
#include "Monster.h"
#include "ObjectManager.h"
#include "GTimer.h"

CMonster1::CMonster1(int x, int y, int w, int h, LPCTSTR bmSrpiteName,int fd,float sp)
{	
	mDirection = fd;
	mType = TMONSTER;
	mXPos = x;
	mYPos = y;
	mWidth = w;
	mHeight = h;
	mCurFrame = 0;
	mCurDelay = 0;
	mDelayCount = 3;
	mFrameCount = 3;
	mJumpDirect=0;
	mJump=1;
	mAnimation = new Sprite(mXPos, mYPos, mWidth, mHeight, 1, mFrameCount, mDelayCount, bmSrpiteName);	
	mXMove = 1;
	mYMove = 8;
	mSpeed =sp;
	oldmove = CGTimer::Time();
	mHealth = 1;
	mStart = 0;
}

int CMonster1::DoAction(/*CScreen* scr, */IObjectManager* objMan)
//di dung chuong ngai vat thi quay lai , di xuong bac thang,xuong ho.
{		
	if(mHealth<=0)
		return -1;
	int moveX=0;
	if(abs(mXPos - objMan->GetMarioPos().x) < 500 )
		mStart = 1;
	if(mStart == 1)
	{	
		int i = CheckCollision(objMan);
		if(i == -1)
			return -1; // Roi xuong vuc sau
		if (GetBit(i,3)!=1 )
		{	
			mYPos=mYPos+mYMove;
			moveX=0;
		}
		else
		{	
			
			moveX = (CGTimer::Time()-oldmove)*mSpeed;
			oldmove=CGTimer::Time();
			moveX=mXMove;
		}
		if(mDirection==DIRRIGHT)
		{	
			if(GetBit(i,0)==1)
			{	
				mAnimation->FlipFrame();
				mDirection = DIRLEFT;	
				mXPos=mXPos-moveX;
			}
			else
			{
				mXPos=mXPos+moveX;
			}
		}
		if(mDirection==DIRLEFT)
		{	
			if (GetBit(i,1)==1) // bi can ben trai
			{	
				mAnimation->FlipFrame();
				mDirection = DIRRIGHT;	
				mXPos=mXPos+moveX;
			}
			else
			{
				mXPos=mXPos-moveX;
				if(mXPos<0)
				{
					mXPos=0;
					mDirection=DIRRIGHT;
					mAnimation->FlipFrame();
				}
			}
		}
	}
	
	NextFrame();
	/*if(mXPos%80==0 && moveX!=0)
	{
		IMonster* obj = NULL;
		obj = new CMonsterClub(this->mXPos,this->mYPos+5,26,23,_T("axe.bmp"), this->Direction(), 0.1);
		objMan->AddMonster(obj);
	}*/
	return 1;
}

CMonster2::CMonster2(int x, int y, int w, int h, LPCTSTR bmSrpiteName,int fd,float sp)//nhay theo qui dao , di gap  chuong ngao vat quay
{	
	mDirection=fd;
	mType = TMONSTER;
	mXPos = x;
	mYPos = y;
	mWidth = w;
	mHeight = h;
	mCurFrame = 0;
	mCurDelay = 0;
	mDelayCount = 4;
	mFrameCount = 3;
	mJumpDirect=1;
	mJump=1;
	mAnimation = new Sprite(mXPos, mYPos, mWidth, mHeight, 1, mFrameCount, mDelayCount, bmSrpiteName);
	mXMove = 1;
	mYMove = 5;
	mXpos1=mXPos;
	mYpos1=mYPos;
	mSpeed = sp;
	oldmove=CGTimer::Time();
	mHealth = 1;
}



int CMonster2::DoAction(/*CScreen* scr, */IObjectManager* objMan)
//nhay theo qui dao ,gap chuong ngai vat trai phai de quay lai ,duong chuong ngai vat tren thi co lai//lao xuong ho
{  
	if(mHealth<=0)
		return -1;
	int  moveX = (CGTimer::Time()-oldmove)*mSpeed;
    oldmove=CGTimer::Time();
	mYMove=2*moveX;
	int moveY=0;
	if(abs(mXPos - objMan->GetMarioPos().x) < 500)
	{	
		int i= CheckCollision(objMan);
		if(i == -1)
			return -1; // Roi xuong vuc sau
		if(mJumpDirect==1 ) 
		{
			if(mYpos1-mYPos>=100||GetBit(i,2)==1)
			{
				mJumpDirect=0;
			}
			else
				mYPos=mYPos -mYMove;
		}
		else
		{
			if( GetBit(i,3)==1)
			{	mJumpDirect=1;
			    mYpos1=mYPos;
				mXpos1=mXPos;
			}
			else
				mYPos=mYPos + mYMove;
		}
		if(mDirection==DIRRIGHT)
		{	if(GetBit(i,0)==1)
		{	
			mAnimation->FlipFrame();
			mDirection = DIRLEFT;	
			mXPos=mXPos-moveX;
		}
		else
		{
			mXPos=mXPos+moveX;
		}
		}
		if(mDirection==DIRLEFT)
		{	if (GetBit(i,1)==1) // bi can ben trai
		{	
			mAnimation->FlipFrame();
			mDirection = DIRRIGHT;	
			mXPos=mXPos+moveX;
		}
		else
		{
			mXPos=mXPos-moveX;
			if(mXPos<0)
			{	mXPos=0;
			mDirection=DIRRIGHT;
			mAnimation->FlipFrame();
			}
		}
		}
	}
	NextFrame();
	return 1;
}


CMonster8::CMonster8(int x, int y, int w, int h, LPCTSTR bmSpriteName,int fd,float sp)//nhay theo qui dao , di gap  chuong ngao vat quay
{	
	mDirection=fd;
	mType = TMONSTER;
	mXPos = x;
	mYPos = y;
	mWidth = w;
	mHeight = h;
	mCurFrame = 0;
	mCurDelay = 0;
	mDelayCount = 3;
	mFrameCount = 3;
	mJumpDirect=1;
	mJump=1;
	mAnimation = new Sprite(mXPos, mYPos, mWidth, mHeight, 1, mFrameCount, mDelayCount, bmSpriteName);
	mXMove = 1;
	mYMove = 5;
	mXpos1=mXPos;
	mYpos1=mYPos;
	mSpeed = sp;
	oldmove=CGTimer::Time();
	mHealth = 1;
}



int CMonster8::DoAction(/*CScreen* scr, */IObjectManager* objMan)
//nhay theo qui dao ,gap chuong ngai vat trai phai de quay lai ,duong chuong ngai vat tren thi co lai , chay tren 1 khoang xac dinh
//dat tren cac thanh gach , co khoang di chuyen bang do dai thanh.
{  
	if(mHealth<=0)
		return -1;
	int  moveX = (CGTimer::Time()-oldmove)*mSpeed;
	oldmove=CGTimer::Time();
	mYMove=2*moveX;
	int moveY=0;
	if(abs(mXPos - objMan->GetMarioPos().x) < 500)
	{	
		int i= CheckCollision(objMan);
		if(i == -1)
			return -1; // Roi xuong vuc sau
		if(mJumpDirect==1 ) 
		{
			if(mYpos1-mYPos>=100||GetBit(i,2)==1)
			{
				mJumpDirect=0;
			}
			else
				mYPos=mYPos -mYMove;
		}
		else
		{
			if( GetBit(i,3)==1)
			{	mJumpDirect=1;
			mYpos1=mYPos;
			mXpos1=mXPos;
			}
			else
				mYPos=mYPos + mYMove;
		}
		if(mDirection==DIRRIGHT)
		{	if(GetBit(i,0)==1||abs(mXPos-mXpos1)>=100)
		{	
			mAnimation->FlipFrame();
			mDirection = DIRLEFT;	
			mXPos=mXPos-moveX;
		}
		else
		{
			mXPos=mXPos+moveX;
		}
		}
		if(mDirection==DIRLEFT)
		{	if (GetBit(i,1)==1||abs(mXPos-mXpos1)>=100) // bi can ben trai
		{	
			mAnimation->FlipFrame();
			mDirection = DIRRIGHT;	
			mXPos=mXPos+moveX;
		}
		else
		{
			mXPos=mXPos-moveX;
			if(mXPos<0)
			{	mXPos=0;
			mDirection=DIRRIGHT;
			mAnimation->FlipFrame();
			}
		}
		}
	}
	NextFrame();
	return 1;
}




CMonster3::CMonster3(int x, int y, int w, int h, LPCTSTR bmSrpiteName,int fd,float sp)
{		
	mDirection=fd;
	mType = TMONSTER;
	mXPos = x;
	mYPos = y;
	mWidth = w;
	mHeight = h;
	mCurFrame = 0;
	mCurDelay = 0;
	mDelayCount = 2;
	mFrameCount = 3;
	mAnimation = new Sprite(mXPos, mYPos, mWidth, mHeight, 1, mFrameCount, mDelayCount, bmSrpiteName);
	
	mXMove = 5;
	mYMove = 1;
	
	mJumpDirect=0;
	mJump=1;
	mSpeed=sp;
	oldmove=CGTimer::Time();
	mHealth = 1;
	mStart = 1;
}

int CMonster3::DoAction(/*CScreen* scr, */IObjectManager* objMan)
// di dung chuong ngai vat trai ,phai quay lai , khi gap ho hay bac thang thi quay lai(phai xd chinh xac vi tri dung)
{		
	if(mHealth<=0)
		return -1;
	 mXMove = (CGTimer::Time()-oldmove)*mSpeed;
	 oldmove=CGTimer::Time();
		
		int i = CheckCollision(objMan);
		if(i == -1)
			return -1; // Roi xuong vuc sau
		
		if(GetBit(i,3)!=1)
		{
			if(mDirection==DIRLEFT)
			{
				mDirection=DIRRIGHT;
				mAnimation->FlipFrame();
				mXPos=mXPos+mXMove + 3;
			}
			else
			{
				mDirection=DIRLEFT;
				mAnimation->FlipFrame();
				mXPos=mXPos-mXMove ;
			}
			int k = CheckCollision(objMan);
			if(GetBit(k,3)!=1)
				return -1;
		

			
		}
		if(mDirection==DIRRIGHT)
		{	
			if(GetBit(i,0)==1)
			{	
				mAnimation->FlipFrame();
				mDirection = DIRLEFT;	
				mXPos=mXPos-mXMove-3 ;
			}
			else
			{
				mXPos=mXPos+mXMove;
			}

		}
		else//(mDirection==DIRLEFT)
		{	
			if (GetBit(i,1)==1) // bi can ben trai
			{
				mAnimation->FlipFrame();
				mDirection = DIRRIGHT;	
				mXPos=mXPos+mXMove +3;
			}
			else
			{
				mXPos=mXPos-mXMove;
				if(mXPos<0)
				{	
					mXPos=0;
					mDirection=DIRRIGHT;
					mAnimation->FlipFrame();
				}
			}
		}
	
	NextFrame();
	return 1;
}


CMonster4::CMonster4(int x, int y, int w, int h, LPCTSTR bmSrpiteName,int fd,float sp)
// di leo chuong ngai vat , xuong doc, dung chuong ngai vat cao thi quay lai
{	
	mType = TMONSTER;
	mFamily = FANIMATEMOVABLE;
	mDirection = fd;	
	mXPos = x;
	mYPos = y;
	mWidth = w;
	mHeight = h;
	mCurFrame = 0;
	mCurDelay = 0;
	mDelayCount = 4;
	mFrameCount = 3;
	mAnimation = new Sprite(mXPos, mYPos, mWidth, mHeight, 1, mFrameCount, mDelayCount, bmSrpiteName);	
	mXMove = 1;
	mYMove = 1;
	
	mJumpDirect=0;
	mJump=1;
	mSpeed=sp;
	oldmove=CGTimer::Time();
	mHealth = 1;
}

int CMonster4::DoAction(/*CScreen* scr, */IObjectManager* objMan)
{  
	if(mHealth<=0)
		return -1;
	int moveX=0;
	if(abs(mXPos - objMan->GetMarioPos().x) < 500)
	{	
		int i = CheckCollision(objMan);
		if (GetBit(i,3)!=1&& GetBit(i,0)!=1&&GetBit(i,1)!=1)
		{	
			mYPos=mYPos+mYMove;
			moveX=0;
		}
		else
		{
			
			moveX = (CGTimer::Time()-oldmove)*mSpeed;
			
			
		}
		
		if(mDirection==DIRRIGHT)
		{	
			if(GetBit(i,0)==1)
			{	
				mYPos=mYPos - 50;
				if(GetBit(CheckCollision(objMan),0)==1)
				{		
					mAnimation->FlipFrame();
					mDirection = DIRLEFT;	
					mXPos=mXPos-mXMove;
					mYPos=mYPos + 50;
				}
				else
				{
					mYPos=mYPos+50;
					mYPos=mYPos -mYMove;
					mXPos=mXPos+3;
					int k = CheckCollision(objMan);
					if( GetBit(k,1)==1 )
						mXPos=mXPos-3;
				}


			}
			else
			{
				mXPos=mXPos+moveX;
			}
		}
		if(mDirection==DIRLEFT)
		{	if(GetBit(i,1)==1)
		{
			mYPos=mYPos - 50 ;
			if(GetBit(CheckCollision(objMan),1)==1)
			{	
				mAnimation->FlipFrame();
				mDirection = DIRRIGHT;	
				mXPos=mXPos+mXMove;
				mYPos=mYPos + 50;
			}
			else
			{
				mYPos=mYPos+50;
				mYPos=mYPos -mYMove;
				mXPos=mXPos-3;
				int k = CheckCollision(objMan);
				if( GetBit(k,0)==1 )
					mXPos=mXPos+3;
			}
		}

		else
		{
			mXPos=mXPos-moveX;
			if(mXPos<0)
			{
				mXPos=0;
				mDirection=DIRRIGHT;
				mAnimation->FlipFrame();
			}
		}
		}
	}
	  oldmove=CGTimer::Time();
	NextFrame();

	return 1;
}


CMonster5::CMonster5(int x, int y, int w, int h, LPCTSTR bmSrpiteName,int fd,float sp)
{	
	mDirection = fd;
	mType = TMONSTER;
	mFamily = FANIMATEMOVABLE;
	mXPos = x;
	mYPos = y;
	mWidth = w;
	mHeight = h;
	mCurFrame = 0;
	mCurDelay = 0;
	mDelayCount = 4;
	mFrameCount = 3;
	mAnimation = new Sprite(mXPos, mYPos, mWidth, mHeight, 1, mFrameCount, mDelayCount, bmSrpiteName);
	//	mLastMoveTime = timeGetTime();
	//	mSpeed = 24;
	mXMove = 1;
	mYMove = 1;	
	mJumpDirect=1;
	mJump=1;
	mSpeed=sp;
	oldmove=CGTimer::Time();
	mXpos1=x;
	mYpos1=y;
	mHealth = 1;
}


int CMonster5::DoAction(/*CScreen* scr, */IObjectManager* objMan)
// bay lo lung theo qui dao tai vi tri y ban dau , neu dung chuong ngai vat thi quay lai , neu vuot qua khoang 50 thi quay lai
{	
	if(mHealth<=0)
		return -1;
	mXMove = (CGTimer::Time()-oldmove)*mSpeed;
	oldmove=CGTimer::Time();
	mYMove=mXMove;

	int i = CheckCollision(objMan);	
	{	
		if(mJumpDirect==1 ) 
		{
			if(mYpos1-mYPos>=50||GetBit(i,2)==1)
			{
				mJumpDirect=0;
			}
			else
				mYPos=mYPos -mYMove;
		}
		else
		{
			if(mYpos1-mYPos<=3)
			{	mJumpDirect=1;
				
			}
			else
				mYPos=mYPos + mYMove;
		}
		if(mDirection==DIRRIGHT)
		{	
			if(GetBit(i,0)==1||abs(mXPos-mXpos1)>150)
			{	
				mAnimation->FlipFrame();
				mDirection = DIRLEFT;	
				mXPos=mXPos-mXMove -3;
			}
			else
			{
				mXPos=mXPos+mXMove;
			}
		}
		else//(mDirection==DIRLEFT)
		{	
			if (GetBit(i,1)==1||abs(mXPos-mXpos1)>150) // bi can ben trai
			{	
				mAnimation->FlipFrame();
				mDirection = DIRRIGHT;	
				mXPos=mXPos+mXMove+3;
			}
			else
			{
				mXPos=mXPos-mXMove;
				if(mXPos<0)
				{
					mXPos=0;
					mDirection=DIRRIGHT;
					mAnimation->FlipFrame();
				}
			}
		}
	}
	NextFrame();
	return 1;
}


CMonster6::CMonster6(int x, int y, int w, int h, LPCTSTR bmSrpiteName,int fd,float sp)
{	
	mDirection = fd;
	mType = TMONSTER;
	mFamily = FANIMATEMOVABLE;
	mXPos = x;
	mYPos = y;
	mWidth = w;
	mHeight = h;
	mCurFrame = 0;
	mCurDelay = 0;
	mDelayCount = 4;
	mFrameCount = 3;
	mAnimation = new Sprite(mXPos, mYPos, mWidth, mHeight, 1, mFrameCount, mDelayCount, bmSrpiteName);
	//	mLastMoveTime = timeGetTime();
	//	mSpeed = 24;
	mXMove = 1;
	mYMove = 1;	
	mJumpDirect=1;
	mJump=1;
	mSpeed=sp;
	oldmove=CGTimer::Time();
	mXpos1=x;
	mYpos1=y;
	mHealth = 1;
}

int CMonster6::DoAction(/*CScreen* scr, */IObjectManager* objMan)
// bay lo lung theo qui dao tai vi tri y ban dau , neu dung chuong ngai vat thi quay lai 
{	
	if(mHealth<=0)
		return -1;
	mXMove = (CGTimer::Time()-oldmove)*mSpeed;
	oldmove=CGTimer::Time();
	mYMove=mXMove;				 
	int i = CheckCollision(objMan);
	if(abs(mXPos - objMan->GetMarioPos().x) < 500)
	{	
		if(mJumpDirect==1 ) 
		{
			if(mYpos1-mYPos>=50||GetBit(i,2)==1)
			{
				mJumpDirect=0;
			}
			else
				mYPos=mYPos -mYMove;
		}
		else
		{
			if(mYpos1-mYPos<=3)
			{	mJumpDirect=1;

			}
			else
				mYPos=mYPos + mYMove;
		}
		if(mDirection==DIRRIGHT)
		{	
			if(GetBit(i,0)==1)
			{	
				mAnimation->FlipFrame();
				mDirection = DIRLEFT;	
				mXPos=mXPos-mXMove;
			}
			else
			{
				mXPos=mXPos+mXMove;
			}
		}
		if(mDirection==DIRLEFT)
		{	
			if (GetBit(i,1)==1) // bi can ben trai
			{	
				mAnimation->FlipFrame();
				mDirection = DIRRIGHT;	
				mXPos=mXPos+mXMove;
			}
			else
			{
				mXPos=mXPos-mXMove;
				if(mXPos<0)
				{
					mXPos=0;
					mDirection=DIRRIGHT;
					mAnimation->FlipFrame();
				}
			}
		}
	}
	NextFrame();
	return 1;
}
			   			   
CMonster7::CMonster7(int x, int y, int w, int h, LPCTSTR bmSrpiteName,int fd,float sp)
{	
	mDirection = fd;
	mType = TMONSTER;
	mFamily = FANIMATEMOVABLE;
	mXPos = x;
	mYPos = y;
	mWidth = w;
	mHeight = h;
	mCurFrame = 0;
	mCurDelay = 0;
	mDelayCount = 4;
	mFrameCount = 3;
	mAnimation = new Sprite(mXPos, mYPos, mWidth, mHeight, 1, mFrameCount, mDelayCount, bmSrpiteName);
	//	mLastMoveTime = timeGetTime();
	//	mSpeed = 24;
	mXMove = 1;
	mYMove = 1;	
	mJumpDirect=1;
	mJump=1;
	mSpeed=sp;
	oldmove=CGTimer::Time();
	mXpos1=x;
	mYpos1=y;
	mHealth = 1;

}

int CMonster7::DoAction(/*CScreen* scr, */IObjectManager* objMan)
// bay lo lung theo hinh quat quanh vi tri y ban dau , neu dung chuong ngai vat thi quay lai , chieu dai quat co dinh 
{	
	if(mHealth<=0)
		return -1;
	mXMove = (CGTimer::Time()-oldmove)*mSpeed;
	oldmove=CGTimer::Time();
	mYMove=mXMove*mXMove/8;;
	
	int i = CheckCollision(objMan);
		
		if(mDirection==DIRRIGHT)
		{	
			if(GetBit(i,0)==1||abs(mXPos -mXpos1) >=250)
			{	
				mAnimation->FlipFrame();
				mDirection = DIRLEFT;	
				mXPos=mXPos-mXMove-3;
			}
			else
			{	mXPos=mXPos + mXMove;
				if(mXPos -mXpos1 >=0)
				{
				
					mYPos =mYPos - mYMove ;

				}
				else
				{
					
					mYPos =mYPos +mYMove  ;
				}


			}
		}
		if(mDirection==DIRLEFT)
		{	
			if (GetBit(i,1)==1||abs(mXPos-mXpos1)>=250) // bi can ben trai
			{	
				mAnimation->FlipFrame();
				mDirection = DIRRIGHT;	
				mXPos=mXPos+mXMove+3;
			}
			else
			{   mXPos=mXPos -mXMove;
				if(mXPos -mXpos1 >=0)
				{
					
					mYPos =mYPos + mYMove  ;

				}
				else
				{
					
					mYPos =mYPos - mYMove  ;
				}
				
				if(mXPos<0)
				{
					mXPos=0;
					mDirection=DIRRIGHT;
					mAnimation->FlipFrame();
				}
			}
		}
	
	NextFrame();
	return 1;
}


CMonsterClubB1::CMonsterClubB1(int x, int y, int w, int h, LPCTSTR bmSrpiteName,int fd,int jd,float sp)
{	
	mSpeed=sp;
	oldmove=CGTimer::Time();
	mDirection = fd;
	mType = TMONSTERCLUB;
	mFamily = FANIMATEMOVABLE;
	mXPos = x;
	mYPos = y;
	mWidth = w;
	mHeight = h;
	mXMove = 1;
	mYMove = 1;
	mCurFrame = 0;
	mCurDelay = 0;
	mDelayCount = 4;
	mFrameCount = 3;
	mAnimation = new Sprite(mXPos, mYPos, mWidth, mHeight, 1, mFrameCount, mDelayCount, bmSrpiteName);
	//	mLastMoveTime = timeGetTime();
	//	mSpeed = 24;
	
	mJumpDirect=jd;
	mJump=1;
}

int CMonsterClubB1::DoAction(/*CScreen* scr, */IObjectManager* objMan)
{
	mYMove= (CGTimer::Time()-oldmove)*mSpeed;
    oldmove=CGTimer::Time();
	int i = CheckCollision(objMan);
	if(mJumpDirect==1)
	{	if (GetBit(i,2)==1)
		{
			mJumpDirect=0;
		}
		else
			mYPos=mYPos-mYMove;

	}
	if(mJumpDirect==0)
	{	if (GetBit(i,3)==1)
		{
			return -1;
		}
		else
			mYPos=mYPos+mYMove;

	}

	NextFrame();
	return 1;
}



CMonsterB1::CMonsterB1(int x, int y, int w, int h, LPCTSTR bmSrpiteName, int fd,float sp)
{	
	mDirection = fd;
	mType = TMONSTER;
	mFamily = FANIMATEMOVABLE;
	mXPos = x;
	mYPos = y;
	mWidth = w;
	mHeight = h;
	mXMove = 1;
	mYMove = 1;
	mCurFrame = 0;
	mCurDelay = 0;
	mDelayCount = 4;
	mFrameCount = 3;
	mAnimation = new Sprite(mXPos, mYPos, mWidth, mHeight, 1, mFrameCount, mDelayCount, bmSrpiteName);
	//	mLastMoveTime = timeGetTime();
	//	mSpeed = 24;
	
	mJumpDirect=0;
	mJump=1;
	mSpeed=sp;
	oldmove=CGTimer::Time();
	mHealth = 10;
}

int CMonsterB1::DoAction(/*CScreen* scr, */IObjectManager* objMan)
{	
	if(mHealth<=0)
		return -1;
	mXMove = (CGTimer::Time()-oldmove)*mSpeed;
	oldmove=CGTimer::Time();

	if(abs(mXPos - objMan->GetMarioPos().x) < 500 )
	{	
		int i = CheckCollision(objMan);
		if(GetBit(i,3)!=1)
		{
			if(mDirection==DIRLEFT)
			{
				mDirection=DIRRIGHT;
				mAnimation->FlipFrame();
				mXPos=mXPos+mXMove +5;
			}
			else
			{
				mDirection=DIRLEFT;
				mAnimation->FlipFrame();
				mXPos=mXPos-mXMove-5;
			}
		}
		if(mDirection==DIRRIGHT)
		{	
			if(GetBit(i,0)==1)
			{	
				mAnimation->FlipFrame();
				mDirection = DIRLEFT;	
				mXPos=mXPos-mXMove;
			}
			else


				mXPos=mXPos+mXMove;


		}
		if(mDirection==DIRLEFT)
		{	
			if (GetBit(i,1)==1) // bi can ben trai
			{
				mAnimation->FlipFrame();
				mDirection = DIRRIGHT;	
				mXPos=mXPos+mXMove;
			}
			else
			{
				mXPos=mXPos-mXMove;
				if(mXPos<0)
				{	
					mXPos=0;
					mDirection=DIRRIGHT;
					mAnimation->FlipFrame();
				}
			}
		}
		if(mXPos%50==0)
		{	IMonster* obj = NULL;
			obj = new CMonsterClub(mXPos,mYPos,24,32,_T("Monster04.bmp"),mDirection,1);
			 objMan->AddMonster(obj);   	
		}
		if( mXPos%50==0)
		{	IMonster* obj = NULL;
		    obj = new CMonsterClubB1(mXPos,mYPos +3 ,24,32,_T("Monster04.bmp"),1,1,1);	
		     objMan->AddMonster(obj);     
		}
			
	}
	NextFrame();
	return 1;
}


CMonsterB2::CMonsterB2(int x, int y, int w, int h, LPCTSTR bmSrpiteName,int fd,float sp)
{	
	mSpeed=sp;
	oldmove=CGTimer::Time();
	mDirection = fd;
	mType = TMONSTER;
	mFamily = FANIMATEMOVABLE;
	mXPos = x;
	mYPos = y;
	mWidth = w;
	mHeight = h;
	mXMove = 1;
	mYMove = 1;
	mCurFrame = 0;
	mCurDelay = 0;
	mDelayCount = 4;
	mFrameCount = 3;
	mAnimation = new Sprite(mXPos, mYPos, mWidth, mHeight, 1, mFrameCount, mDelayCount, bmSrpiteName);
	
	mJumpDirect=0;
	mJump=1;
	mHealth = 10;
}


int CMonsterB2::DoAction(IObjectManager* objMan)
{	
	if(mHealth<=0)
		return -1;
	mXMove = (CGTimer::Time()-oldmove)*mSpeed;
    oldmove=CGTimer::Time();
	if(abs(mXPos - objMan->GetMarioPos().x) < 500)
	{	
		int i = CheckCollision(objMan);
		if(mDirection==DIRRIGHT)
		{	
			if(GetBit(i,0)==1)
			{	
				mAnimation->FlipFrame();
				mDirection = DIRLEFT;	
				mXPos=mXPos-mXMove;
			}
			else
				mXPos=mXPos+mXMove;
		}
		if(mDirection==DIRLEFT)
		{	
			if (GetBit(i,1)==1) // bi can ben trai
			{
				mAnimation->FlipFrame();
				mDirection = DIRRIGHT;	
				mXPos=mXPos+mXMove;
			}
			else
			{
				mXPos=mXPos-mXMove;
				if(mXPos<0)
				{	
					mXPos=0;
					mDirection=DIRRIGHT;
					mAnimation->FlipFrame();
				}
			}
		}
		if( mXPos % 30 ==0 )
		{ 
			IMonster* obj = NULL;
			obj = new CMonsterClubB1(mXPos,mYPos +3 ,25,25,_T("club.bmp"),1,0,0.5);
			objMan->AddMonster(obj);
		}
	}
	NextFrame();
	return 1;
}

CMonsterB3::CMonsterB3(int x, int y, int w, int h, LPCTSTR bmSrpiteName,int fd,float sp)//nhay theo qui dao , di gap  chuong ngao vat quay
{	
	mSpeed=sp;
	oldmove=CGTimer::Time();
	mDirection=fd;
	mType = TMONSTER;
	mXPos = x;
	mYPos = y;
	mWidth = w;
	mHeight = h;
	mCurFrame = 0;
	mCurDelay = 0;
	mDelayCount = 4;
	mFrameCount = 3;
	mAnimation = new Sprite(mXPos, mYPos, mWidth, mHeight, 1, mFrameCount, mDelayCount, bmSrpiteName);
	mXMove = 1;
	mYMove = 5;	
	mJumpDirect=1;
	mJump=1;
	mXpos1=mXPos;
	mYpos1=mYPos;
	mHealth = 20;
}

int CMonsterB3::DoAction(/*CScreen* scr, */IObjectManager* objMan)//nhay theo qui dao ,gap chuong ngai vat trai phai de quay lai ,duong chuong ngai vat tren thi co lai
{    
	if(mHealth<=0)
		return -1;
	mXMove = (CGTimer::Time()-oldmove)*mSpeed;
	oldmove=CGTimer::Time();
	int moveX=mXMove;
	mYMove = 1.5*mXMove;
	int flag=0;
	
	if(abs(mXPos - objMan->GetMarioPos().x) < 500)
	{	
		int i= CheckCollision(objMan);
		if(i == -1)
			return -1; // Roi xuong vuc sau
		if(mJumpDirect==1 ) 
		{
			if(mYpos1-mYPos>=200||GetBit(i,2)==1)
			{
				mJumpDirect=0;
			}
			else
				mYPos=mYPos -mYMove;
		}
		else
		{
			if( GetBit(i,3)==1)
			{   flag=1; 
				mJumpDirect=1;
				mYpos1=mYPos;
				mXpos1=mXPos;
			}
			else
				mYPos=mYPos + mYMove;
		}
		if(mDirection==DIRRIGHT)
		{	if(GetBit(i,0)==1)
		{	
			mAnimation->FlipFrame();
			mDirection = DIRLEFT;	
			mXPos=mXPos-moveX;
		}
		else
		{
			mXPos=mXPos+moveX;
		}
		}
		if(mDirection==DIRLEFT)
		{	if (GetBit(i,1)==1) // bi can ben trai
		{	
			mAnimation->FlipFrame();
			mDirection = DIRRIGHT;	
			mXPos=mXPos+moveX;
		}
		else
		{
			mXPos=mXPos-moveX;
			if(mXPos<0)
			{	mXPos=0;
			mDirection=DIRRIGHT;
			mAnimation->FlipFrame();
			}
		}
		}
	}
	NextFrame();
	if(flag==1 )
	{	
		IMonster* obj = NULL;
		obj = new CMonsterClub(mXPos,mYPos,25,25,_T("club.bmp"),mDirection,0.1);
		objMan->AddMonster(obj);   	
	}
	if(flag==0&&mXPos%30==0)
	{
		IMonster* obj = NULL;
		obj = new CMonsterClubB1(mXPos,mYPos +3 ,25,25,_T("club.bmp"),1,0,0.1);	
		objMan->AddMonster(obj);    
	}
	return 1;
}


CMonsterClub::CMonsterClub(int x, int y, int w, int h, LPCTSTR bmSrpiteName,int fd, float sp)
{	
	mFamily = FANIMATEMOVABLE;
	mType = TMONSTERCLUB;
	mDirection = fd;	
	mXPos = x;
	mYPos = y;
	mWidth = w;
	mHeight = h;
	mAnimation = new Sprite(mXPos, mYPos, mWidth, mHeight, 1, 3, 6, bmSrpiteName);
	if(fd == DIRLEFT)
		mAnimation->FlipFrame();
	mXMove = 5;
	mYMove = 1;

	mCurFrame = 0;
	mCurDelay = 0;
	mDelayCount = 3;
	mFrameCount = 3;

	mXPos1=x;
	mYPos1=y;
	mSpeed = sp;
	oldmove=CGTimer::Time();
}

int CMonsterClub::DoAction(/*CScreen* scr, */IObjectManager* objMan)
{		
	mXMove = (CGTimer::Time()-oldmove)*mSpeed;
	oldmove=CGTimer::Time();
	int i = CheckCollision(objMan);
	if(mDirection==DIRRIGHT)
	{
		if(GetBit(i,0)==1)
		{	
			return -1;
		}
		else
			if(abs(mXPos-mXPos1)>=400 )
			{
				return -1;			
			}
			else
			{
				mXPos=mXPos+mXMove;
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
			if(abs(mXPos-mXPos1)>=400 )
			{
				return -1;			
			}
			else
				mXPos=mXPos-mXMove;
		}
		
	}
	NextFrame();
	return 1;
}