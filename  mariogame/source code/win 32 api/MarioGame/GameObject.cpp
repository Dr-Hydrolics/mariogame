#include "StdAfx.h"
#include "GameObject.h"


CGameObject::CGameObject()
{
	mXPos = 0;
	mYPos = 0;
	mWidth = 0;
	mHeight = 0;
	mFamily = FNOANIMATEMOVELESS;
}

CGameObject::~CGameObject()
{

}
POINT CGameObject::GetPos()
{
	POINT pos;
	pos.x = mXPos;
	pos.y = mYPos;
	return pos;
}

void CGameObject::Present(HDC hDC, RECT view)
{
	return;
}
