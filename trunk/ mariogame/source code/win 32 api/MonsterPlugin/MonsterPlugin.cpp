// MonsterPlugin.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "MonsterPlugin.h"


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

// This is an example of an exported variable
MONSTERPLUGIN_API int nMonsterPlugin=0;

// This is an example of an exported function.
MONSTERPLUGIN_API int fnMonsterPlugin(void)
{
	return 42;
}

MONSTERPLUGIN_API IMonster* CreateMonsterPlugin(int x, int y, int w, int h, LPCTSTR bmSpriteName, int dir, float sp)
{
	IMonster* pMonster = NULL;
	pMonster = new CMonsterPlugin(x, y, w, h, bmSpriteName, dir, sp);
	return pMonster;
}

// This is the constructor of a class that has been exported.
// see MonsterPlugin.h for the class definition

CMonsterPlugin::CMonsterPlugin(int x, int y, int w, int h, LPCTSTR bmSrpiteName,int fd,float sp)
{	
	mDirection = fd;
	mType = TMONSTER;
	mXPos = x;
	mYPos = y;
	mWidth = w;
	mHeight = h;
	mCurFrame = 0;
	mCurDelay = 0;
	mDelayCount = 1;
	mFrameCount = 3;
	mJumpDirect=0;
	mJump=1;
	mAnimation = new Sprite(mXPos, mYPos, mWidth, mHeight, 1, mFrameCount, mDelayCount, bmSrpiteName);	
	mXMove = 1;
	mYMove = 1;
	mXpos1=mXPos;
	mYpos1=mYPos;
	mSpeed =sp;
	oldmove =GetTickCount();
	mLastHurt = 0;
	mHealth = 1;
	mStart = 0;
}

int CMonsterPlugin::DoAction(IObjectManager* objMan)
{		
	if(mHealth<=0)
		return -1;
	mXMove = 3;	
	mYMove = 1.5*mXMove;
	int flag=0;		
	if(mStart == 1)
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
			{  
				flag=1; 
				mJumpDirect=1;
				mYpos1=mYPos;
				mXpos1=mXPos;
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

		NextFrame();
	}
	if(abs(mXPos - objMan->GetMarioPos().x) < 500 && mStart == 0)
	{
		mStart = 1;		   		
		return 2; // Mario gap quai vat
	}
	return 1;
}