#include "StdAfx.h"
#include "Game.h"
CGame::CGame(void)
{
	mainWnd = NULL;
	wndDC = NULL;
	character = NULL;
	iTickCount = 0;
	pBmOp = NULL;
}

CGame::~CGame(void)
{
}

int CGame::Init(HWND hWnd)
{	
	numStep = 10;
	walkRight = numStep+1;
	mainWnd = hWnd;	
	// Khoi tao HDC cua cua so	
	InitHDC();	
	
	// Khoi tao, load Background
	bmBackGround = new MyBitmap(_T("background.bmp"));
	DrawBackground();
	
	// Khoi tao, load Menu
	bmMenu = new MyBitmap(_T("menus.bmp"));
	DrawMenu();
	
	// Phat nhac nen
	// PlaySound(TEXT("Music\\victory.mid"),NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);
	
	// Khoi tao cac doi tuong trong game
	bmMario = new MyBitmap(_T("mario.bmp"));
	character = new Sprite(0,320,18,36,1,5,2,bmMario);
	iTickCount = GetTickCount();
	
	character->Render(memDC);	
	CopyToScreen();
	return 1;
}

int CGame::Run()
{	
	if(GetTickCount() - iTickCount >= 1000/FRAMES_PER_SEC )
	{
		if(KEY_DOWN(VK_RIGHT))
		{
			//character->mXPos = (character->mXPos + character->mXMove)%622;			
			//character->NextFrame();
			walkRight = 0;
		}
		if(walkRight<numStep)
		{
			walkRight++;
			character->mXPos = (character->mXPos + character->mXMove)%622;			
			character->NextFrame();
		}		
		if(KEY_DOWN(VK_LEFT))
		{
			character->mXPos = (character->mXPos - character->mXMove + 622)%622;			
			character->NextFrame();
		}
		if(KEY_DOWN(VK_DOWN))
		{
			character->mYPos = (character->mYPos + character->mYMove)%460;			
			character->NextFrame();
		}
		if(KEY_DOWN(VK_UP))
		{
			character->mYPos = (character->mYPos - character->mYMove + 460)%460;
			character->NextFrame();
		}
		iTickCount = GetTickCount();		
		DrawBackground();		
		DrawMenu();		
		character->Render(memDC);		
		CopyToScreen();
	}
	
	return 1;
}

int CGame::End()
{
	ReleaseHDC();
	if(bmBackGround)
		delete bmBackGround;
	if(bmMenu)
		delete bmMenu;
	if(bmMario)
		delete bmMario;
	return 1;
}

int CGame::DrawBackground()
{	
	if(!bmBackGround)
		return 0;
	//bmBackGround->DrawTransparent(memDC,0,0,RGB(255,255,255));
	bmBackGround->Draw(memDC,0,0);			
	return 1;
}

int CGame::DrawMenu()
{
	if(!bmMenu)
		return 0;	
	bmMenu->DrawTransparent(memDC,100,100,RGB(255,255,255));
	return 1;
}

int CGame::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	/*switch(wParam)
	{
		case VK_RIGHT:
			character->mXPos = (character->mXPos + character->mXMove)%622;			
			character->NextFrame();
		break;
		case VK_LEFT:
			character->mXPos = (character->mXPos - character->mXMove+622)%622;			
			character->PreviousFrame();
		break;
		case VK_UP:
			character->mYPos = (character->mYPos - character->mYMove+460)%460;
			character->PreviousFrame();
		break;
		case VK_DOWN:			
			character->mYPos = (character->mYPos + character->mYMove)%460;
			character->NextFrame();
		break;
	}*/
	return 1;
}

void CGame::CopyToScreen()
{
	RECT rt;
	GetClientRect(mainWnd, &rt);
	BitBlt(wndDC, 0, 0, rt.right, rt.bottom, memDC, 0, 0,SRCCOPY);
}

void CGame::InitHDC()
{
	RECT rt;
	GetClientRect(mainWnd, &rt);
	wndDC = GetDC(mainWnd);
	memDC = CreateCompatibleDC(wndDC);
	memBitmap = CreateCompatibleBitmap(wndDC,rt.right, rt.bottom);
	oldBitmap = (HBITMAP)SelectObject(memDC, memBitmap);
}

void CGame::ReleaseHDC()
{
	SelectObject(memDC, oldBitmap);
	DeleteDC(memDC);
	DeleteObject(memBitmap);
	DeleteObject(oldBitmap);
	ReleaseDC(mainWnd, wndDC);
}