#include "StdAfx.h"
#include "BonnusObject.h"
#include "ObjectManager.h"

CCoin::CCoin()
{
	mFamily = FANIMATEMOVELESS;
	mType = TCOIN;
	mFrameCount = 0;
	mFirstFrame = 0;
	mCurFrame = 0;
	mDelayCount = 0;
	mCurDelay = 0;
}
CCoin::CCoin(int x, int y, int w, int h, LPCTSTR bmSpriteName)
{
	mFamily = FANIMATEMOVELESS;
	mType = TCOIN;
	mFrameCount = 4;
	mFirstFrame = 0;
	mCurFrame = 0;
	mDelayCount = 15;
	mCurDelay = 0;
	mXPos = x;
	mYPos = y;
	mWidth = w;
	mHeight = h;
	mAnimation = new Sprite(mXPos, mYPos, mWidth, mHeight, 1, mFrameCount, mDelayCount, bmSpriteName);	
	mAnimation->SetCurrentFrame(mFirstFrame);
}
CCoin::~CCoin()
{
	if (mAnimation != NULL)
	{
		delete mAnimation;
		mAnimation = NULL;
	}
}
void CCoin::NextFrame()
{
	if(mCurDelay>=mDelayCount)
	{
		mCurFrame = (mCurFrame + 1)%mFrameCount;
		mAnimation->SetCurrentFrame(mCurFrame + mFirstFrame);
		mCurDelay = 0;
	}
	else
		mCurDelay++;
}
int CCoin::DoAction(/*CScreen* scr, */CObjectManager* objMan)
{
	NextFrame();	
	return 1;
}


CTrunk::CTrunk(int x, int y, int w, int h, LPCTSTR bmSpriteName, int innerObjTileIdx, int tileIdx /*= IFLOWER*/)
{
	mOpened = 0;
	mFamily = FNOANIMATEMOVELESS;
	mType = TTRUNK;	
	mXPos = x;
	mYPos = y;
	mWidth = w;
	mHeight = h;
	mTileIndex = tileIdx;
	bmSprite = new MyBitmap(bmSpriteName);
	mInnerObjTileIdx = innerObjTileIdx;	
}
CTrunk::~CTrunk(void)
{

}

void CTrunk::Open(CObjectManager* objMan)
{	
	if(mOpened == 1)
		return;
	mOpened = 1;
	mTileIndex = 0;
	CGameObject* obj = NULL;
	CMap* map = objMan->GameMap();
	switch(mInnerObjTileIdx)
	{
	case ICOIN:
		obj = new CCoin(mXPos, mYPos - map->TileHeight(), map->TileWidth(), map->TileHeight(), _T("coin.bmp"));
		objMan->AddBonnus(obj);
		break;
	case IFLOWER:
		obj = new CFlower(mXPos, mYPos - 24, 24, 24, _T("flower.bmp"));
		objMan->AddBonnus(obj);
		break;
	case IMUSHROOM:
		obj = new CMushroom(mXPos, mYPos - 24, 24, 24, _T("smallmushroom.bmp"));
		objMan->AddBonnus(obj);
		break;
	case ISTAR:
		obj = new CStar(mXPos, mYPos - map->TileHeight(), map->TileWidth(), map->TileHeight(), _T("star.bmp"));
		objMan->AddBonnus(obj);
		break;
	default:
		obj = new CCoin(mXPos, mYPos - map->TileHeight(), map->TileWidth(), map->TileHeight(), _T("coin.bmp"));
		objMan->AddBonnus(obj);
		break;
	}	
}

CMushroom::CMushroom(void)
{
}
CMushroom::CMushroom(int x, int y, int w, int h, LPCTSTR bmSpriteName, int tileIdx/* = IMUSHROOM*/)
{
	mXMove = 3;
	mYMove = 8;
	mJumpDirect=0;
	mJump=1;
	mFamily = FNOANIMATEMOVABLE;
	mType = TMUSHROOM;	
	mDirection = DIRRIGHT;
	mXPos = x;
	mYPos = y;
	mWidth = w;
	mHeight = h;
	mTileIndex = IMUSHROOM;
	bmSprite = new MyBitmap(bmSpriteName);	
}
CMushroom::~CMushroom(void)
{
}
int CMushroom::DoAction(/*CScreen* scr, */CObjectManager* objMan)
{
	int moveX=0;
	if(abs(mXPos - objMan->GetMarioPos().x) < 500 )
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
			moveX=mXMove;
		if(mDirection==DIRRIGHT)
		{	
			if(GetBit(i,0)==1)
			{					
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
				}
			}
		}
	}	
	return 1;
}
CFlower::CFlower(int x, int y, int w, int h, LPCTSTR bmSpriteName)
{
	mFamily = FANIMATEMOVELESS;
	mType = TFLOWER;	
	mFrameCount = 1;
	mFirstFrame = 0;
	mCurFrame = 0;
	mDelayCount = 0;
	mCurDelay = 0;
	mXPos = x;
	mYPos = y;
	mWidth = w;
	mHeight = h;
	mAnimation = new Sprite(mXPos, mYPos, mWidth, mHeight, 1, mFrameCount, mDelayCount, bmSpriteName);	
	mAnimation->SetCurrentFrame(mFirstFrame);
}
CStar::CStar(int x, int y, int w, int h, LPCTSTR bmSpriteName)
{	
	mType = TSTAR;
	mFamily = FANIMATEMOVABLE;
	mXPos = x;
	mYPos = y;
	mWidth = w;
	mHeight = h;
	mCurFrame = 0;
	mCurDelay = 0;
	mFirstFrame = 0;
	mDelayCount = 0;
	mFrameCount = 1;
	mDirection = DIRRIGHT;
	mAnimation = new Sprite(mXPos, mYPos, mWidth, mHeight, 1, mFrameCount, mDelayCount, bmSpriteName);
	mAnimation->SetCurrentFrame(mCurFrame);
	mXMove = 3;
	mYMove = 3;
	mJumpDirect=1;
	mJump=1;
	mYpos1 = mYPos;
}

int CStar::DoAction(/*CScreen* scr, */CObjectManager* objMan)// di dung chuong ngai vat trai ,phai quay lai , khi gap ho hay bac thang thi quay lai(phai xd chinh xac vi tri dung)//duoi theo mario
{	
	int moveX=mXMove;
	int moveY;
	int flag=0;
	int i= CheckCollision(objMan);
	if(i == -1)
		return -1; // Roi xuong vuc sau
	if(mJumpDirect==1 ) 
	{
		if(mYpos1-mYPos>=150||GetBit(i,2)==1)
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
			mYpos1 = mYPos;
		}
		else
			mYPos=mYPos + mYMove;
	}
	if(mDirection==DIRRIGHT)
	{	
		if(GetBit(i,0)==1)
		{	
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
			}
		}
	}	
	return 1;
}