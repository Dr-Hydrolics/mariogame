#include "StdAfx.h"
#include "NoAnimateObject.h"
#include "ObjectManager.h"

CNoAnimateObject::CNoAnimateObject()
{
	mFamily = FNOANIMATEMOVELESS;
}
CNoAnimateObject::CNoAnimateObject(int x, int y, int w, int h, LPCTSTR bmSpriteName, int tileIdx, int type)
{
	mFamily = FNOANIMATEMOVELESS;
	mType = type;
	mXPos = x;
	mYPos = y;
	mWidth = w;
	mHeight = h;
	mTileIndex = tileIdx;
	bmSprite = new MyBitmap(bmSpriteName);	
}

CNoAnimateObject::~CNoAnimateObject(void)
{
}

int CNoAnimateObject::DoAction(/*CScreen* scr, */CObjectManager* objMan)
{
	return 1;
}
void CNoAnimateObject::Present(HDC hDC, RECT view)
{
	if(mXPos - view.left + mWidth >= 0 && mYPos - view.top + mHeight >=0 && mTileIndex>=0)
	{
		bmSprite->DrawTransparent(hDC, mXPos - view.left, mYPos - view.top, mTileIndex*mWidth, 0, mWidth, mHeight,RGB(255,0,255));
	}		
}

int CMovableNoAnimateObject::CheckCollision(CObjectManager* objMan)
{
	int colDirect=0x00;
	int XPos2, YPos2;
	XPos2 = mXPos + mWidth - 1;
	YPos2 = mYPos + mHeight - 1;
	if(mDirection==DIRRIGHT)
	{
		if (objMan->IsBlockedAt(XPos2 + mXMove, mYPos) == 1 || objMan->IsBlockedAt(XPos2 + mXMove, YPos2) == 1)
		{
			colDirect=colDirect|0x01;
			CMap* gMap = objMan->GameMap();
			mXPos = gMap->TileWidth()*((XPos2 + mXMove)/gMap->TileWidth()) - mWidth;			
		}
	}
	if(mDirection==DIRLEFT)
	{
		if (objMan->IsBlockedAt(mXPos - mXMove, mYPos) == 1 || objMan->IsBlockedAt(mXPos - mXMove, YPos2)==1)
		{
			colDirect=colDirect|0x02;
			CMap* gMap = objMan->GameMap();
			mXPos = gMap->TileWidth()*((mXPos - mXMove)/gMap->TileWidth()) + gMap->TileWidth();

		}
	}
	if (mJump>0)
	{
		if (mJumpDirect==1)
		{			
			if (objMan->IsBlockedAt(mXPos, mYPos - mYMove) == 1 || objMan->IsBlockedAt(XPos2, mYPos - mYMove) == 1) 
			{
				colDirect=colDirect|0x04;
				CMap* gMap = objMan->GameMap();
				this->mYPos = gMap->TileHeight()*((mYPos - mYMove)/gMap->TileHeight()) + gMap->TileHeight();
				if (objMan->IsBlockedAt(mXPos, YPos2 + mYMove) == 1 || objMan->IsBlockedAt(XPos2, YPos2 + mYMove) == 1)
				{
					colDirect=colDirect|0x08;
					this->mYPos = gMap->TileHeight()*((YPos2 + mYMove)/gMap->TileHeight()) - mHeight;
				}
				else
					if (objMan->IsBlockedAt(mXPos, YPos2 + mYMove) == -1 || objMan->IsBlockedAt(XPos2, YPos2 + mYMove) == -1)
						colDirect = -1;
			}
		}
		else
		{
			if (objMan->IsBlockedAt(mXPos, YPos2 + mYMove) == 1 || objMan->IsBlockedAt(XPos2, YPos2 + mYMove) == 1)
			{
				colDirect=colDirect|0x08;
				CMap* gMap = objMan->GameMap();
				this->mYPos = gMap->TileHeight()*((YPos2 + mYMove)/gMap->TileHeight()) - mHeight;
			}
			else
				if (objMan->IsBlockedAt(mXPos, YPos2 + mYMove) == -1 || objMan->IsBlockedAt(XPos2, YPos2 + mYMove) == -1)
					colDirect = -1;
		}		
	}	
	return colDirect;
}