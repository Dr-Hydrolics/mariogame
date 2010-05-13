#include "StdAfx.h"
#include "AnimateObject.h"
#include "ObjectManager.h"

CAnimateObject::CAnimateObject()
{
	mType = TMONSTER;
	mFamily = FANIMATEMOVELESS;
	mXPos = 0;
	mYPos = 0;
	mWidth = 0;
	mHeight = 0;	

	mAnimation = NULL;	
}

CAnimateObject::~CAnimateObject()
{

}

CAnimateObject::CAnimateObject(int x, int y, int w, int h, LPCTSTR bmSpriteName,int fd)
{	
	mDirection = fd;
	mType = TMONSTER;
	mFamily = FANIMATEMOVELESS;
	mXPos = x;
	mYPos = y;
	mWidth = w;
	mHeight = h;
	mAnimation = new Sprite(mXPos, mYPos, mWidth, mHeight, 1, 3, 6, bmSpriteName);
	mCurFrame = 0;
	mCurDelay = 0;
	mDelayCount = 4;
	mFrameCount = 3;	
}

void CAnimateObject::Present(HDC hDC, RECT view)
{
	if(mXPos - view.left + mWidth >= 0 && mYPos - view.top + mHeight >=0 && mAnimation != NULL)
	{
		mAnimation->mXPos = mXPos - view.left;
		mAnimation->mYPos = mYPos - view.top;
		mAnimation->Render(hDC);
	}	
}

int CAnimateObject::DoAction(/*CScreen* scr, */CObjectManager* objMan)
{	
	return 1;
}
int  CAnimateObject::GetBit(int x, int i)
{
	return ((x>>i)&1);
}

void CAnimateObject::NextFrame()
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

CMovableAnimateObject::CMovableAnimateObject()
{
	mFamily = FANIMATEMOVABLE;
	mXMove = 0;
	mYMove = 0;
	mJumpDirect = 1;
	mJump = 0;
}
CMovableAnimateObject::~CMovableAnimateObject()
{

}

int CMovableAnimateObject::CheckCollision(IObjectManager* objMan)
{
	int colDirect=0x00;
	int XPos2, YPos2;
	XPos2 = mXPos + mWidth - 0;
	YPos2 = mYPos + mHeight - 1;	
	if(mDirection==DIRRIGHT)
	{
		if (objMan->IsBlockedAt(XPos2 + mXMove, mYPos) == 1 || objMan->IsBlockedAt(XPos2 + mXMove, YPos2) == 1)
		{
			colDirect=colDirect|0x01;
		}
		if (objMan->IsBlockedAt(XPos2 + mXMove/2, mYPos) == 1 || objMan->IsBlockedAt(XPos2 + mXMove/2, YPos2) == 1)
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
		if (objMan->IsBlockedAt(mXPos - mXMove/2, mYPos) == 1 || objMan->IsBlockedAt(mXPos - mXMove/2, YPos2)==1)
		{
			colDirect=colDirect|0x02;
		}
	}
	if (mJump>0)
	{
		if (mJumpDirect==1)
		{			
			if (objMan->IsBlockedAt(mXPos+1, mYPos - mYMove) == 1 || objMan->IsBlockedAt(XPos2, mYPos - mYMove) == 1) 
			{
				colDirect=colDirect|0x04;
				this->mYPos = objMan->GetMapTileHeight()*((mYPos - mYMove)/objMan->GetMapTileHeight()) + objMan->GetMapTileHeight();
				if (objMan->IsBlockedAt(mXPos+1, YPos2 + mYMove) == 1 || objMan->IsBlockedAt(XPos2, YPos2 + mYMove) == 1)
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
			if (objMan->IsBlockedAt(mXPos+1, YPos2 + mYMove) == 1 || objMan->IsBlockedAt(XPos2, YPos2 + mYMove) == 1)
			{
				colDirect=colDirect|0x08;
				this->mYPos = objMan->GetMapTileHeight()*((YPos2 + mYMove)/objMan->GetMapTileHeight()) - mHeight;
			}
			else
				if (objMan->IsBlockedAt(mXPos+1, YPos2 + mYMove) == -1 || objMan->IsBlockedAt(XPos2, YPos2 + mYMove) == -1)
					colDirect = -1;
		}		
	}	
	return colDirect;
}

int CMovableAnimateObject::DoAction(/*CScreen* scr, */CObjectManager* objMan)
{
	return 1;
}
CMovelessAnimateObject::CMovelessAnimateObject()
{
	mFamily = FANIMATEMOVELESS;
}
CMovelessAnimateObject::~CMovelessAnimateObject()
{

}

int CMovelessAnimateObject::DoAction(/*CScreen* scr, */CObjectManager* objMan)
{
	return 1;
}
