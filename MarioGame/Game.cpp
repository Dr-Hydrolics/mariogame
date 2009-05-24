#include "StdAfx.h"
#include "Game.h"
CGame::CGame(void)
{
	mainWnd = NULL;
	wndDC = NULL;
	character = NULL;
	iTick = 0;
	pBmOp = NULL;
}

CGame::~CGame(void)
{
}

int CGame::Init(HWND hWnd)
{	
	// Khoi tao HDC cua cua so
	mainWnd = hWnd;	
	///
		InitHDC();
	///	
	//pBmOp = new Bitmap_Operations();
	//pBmOp->Initialize_Buffers(mainWnd,1);
	//pBmOp->Create_Buffer(0);
	//character->Render(pBmOp->Get_DC_Buffer(0));
	// memDC = pBmOp->Get_DC_Buffer(0);
	// Load BG
	LoadBackground(_T("MenuBackground.bmp"));
	// Phat nhac nen
	// PlaySound(TEXT("Music\\victory.mid"),NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);
	
	// Khoi tao cac doi tuong trong game
	MyBitmap* bmMario = new MyBitmap(_T("mario.bmp"));
	character = new Sprite(0,0,18,36,1,5,2,bmMario);
	iTick = GetTickCount();
	
	character->Render(memDC);
	//pBmOp->Copy_to_Screen(0);	
	CopyToScreen();
	return 1;
}

int CGame::Run()
{	
	if(GetTickCount() - iTick >= 1000/FRAMES_PER_SEC )
	{
		if(KEY_DOWN(VK_RIGHT))
		{
			character->mXPos = (character->mXPos + character->mXMove)%622;			
			character->NextFrame();
		}
		iTick = GetTickCount();		
		LoadBackground(_T("MenuBackground.bmp"));		
		//character->Render(pBmOp->Get_DC_Buffer(0));
		character->Render(memDC);
		//pBmOp->Copy_to_Screen(0);	
		CopyToScreen();
	}
	
	return 1;
}

int CGame::End()
{
	//pBmOp->Free_Buffer(0);
	//delete pBmOp;
	//ReleaseDC(mainWnd, wndDC);
	ReleaseHDC();
	return 1;
}

int CGame::LoadBackground(LPCTSTR bgName)
{
	MyBitmap bm(bgName);	
	//bm.DrawTransparent(pBmOp->Get_DC_Buffer(0),0,0,RGB(255,255,255));	
	bm.DrawTransparent(memDC,0,0,RGB(255,255,255));	
	MyBitmap bm1(_T("menus.bmp"));
	//bm1.DrawTransparent(pBmOp->Get_DC_Buffer(0),100,100,RGB(255,255,255));	
	bm1.DrawTransparent(memDC,100,100,RGB(255,255,255));	

	return 0;
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