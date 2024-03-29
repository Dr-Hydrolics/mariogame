#include "StdAfx.h"
#include "Screen.h"
#include "Game.h"

int SCREENWIDTH = (640+6);
int SCREENHEIGHT = (480+26);
int VIEWPORTWIDTH = (640+6);
int VIEWPORTHEIGHT = (480+26);

CScreen::CScreen()
{
	mainWnd = NULL;
	wndDC = NULL;
	memDC = NULL;
	memBitmap = NULL;
	bmBackGround = NULL;
	bmFarBackGround = NULL;
	mCurMode = WINDOW;
	memset(&viewPort,0,sizeof(RECT));
}

CScreen::~CScreen()
{
	DeleteDC(memDC);
	ReleaseDC(mainWnd, wndDC);
	if(bmBackGround)
	{
		delete bmBackGround;
		bmBackGround = NULL;
	}
	if (bmFarBackGround)
	{
		delete bmFarBackGround;
		bmFarBackGround = NULL;
	}
}
bool CScreen::GoFullscreen()
{
	if(mCurMode == FULLSCREEN)
		return true;
	FRAMES_PER_SEC = 90;
	SCREENWIDTH = GetSystemMetrics(SM_CXSCREEN);
	SCREENHEIGHT = GetSystemMetrics(SM_CYSCREEN);
	// turn off window region without redraw
	SetWindowRgn(mainWnd, 0, false);

	DEVMODE newSettings;	

	// request current screen settings
	EnumDisplaySettings(0, 0, &newSettings);

	//  set desired screen size/res	
	newSettings.dmPelsWidth  = GetSystemMetrics(SM_CXSCREEN);//GetWidth();		
	newSettings.dmPelsHeight = GetSystemMetrics(SM_CYSCREEN);//GetHeight();		
	newSettings.dmBitsPerPel = 32;		

	//specify which aspects of the screen settings we wish to change 
	newSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

	// attempt to apply the new settings 
	long result = ChangeDisplaySettings(&newSettings, CDS_FULLSCREEN);

	// exit if failure, else set datamember to fullscreen and return true
	if ( result != DISP_CHANGE_SUCCESSFUL )	return false;
	else 
	{

		// switch off the title bar
		DWORD dwstyle = GetWindowLong(mainWnd, GWL_STYLE);
		dwstyle &= ~WS_CAPTION;
		SetWindowLong(mainWnd, GWL_STYLE, dwstyle);

		// move the window to (0,0)
		SetWindowPos(mainWnd, 0, 0, 0, SCREENWIDTH, SCREENHEIGHT, SWP_NOZORDER);
		RECT rt;
		GetClientRect(mainWnd, &rt);
		InvalidateRect(mainWnd, &rt, false);
		mCurMode = FULLSCREEN;
		return true;
	}
}

bool CScreen::GoWindowedMode()
{
	if(mCurMode == WINDOW)
		return true;
	FRAMES_PER_SEC = 60;
	SCREENWIDTH = (640+6);
	SCREENHEIGHT = (480+26);
	// this resets the screen to the registry-stored values
	ChangeDisplaySettings(0, 0);

	// replace the title bar
	DWORD dwstyle = GetWindowLong(mainWnd, GWL_STYLE);
	dwstyle = dwstyle | WS_CAPTION;
	SetWindowLong(mainWnd, GWL_STYLE, dwstyle);

	// move the window back to its old position
	int scrWidth, scrHeight, xPos, yPos;
	scrWidth = GetSystemMetrics(SM_CXSCREEN);
	scrHeight = GetSystemMetrics(SM_CYSCREEN);
	xPos = (scrWidth - SCREENWIDTH)/2;
	yPos = (scrHeight - SCREENHEIGHT)/2;
	SetWindowPos(mainWnd, 0, xPos, yPos, SCREENWIDTH, SCREENHEIGHT, SWP_NOZORDER);
	RECT rt;
	GetClientRect(mainWnd, &rt);
	InvalidateRect(mainWnd, &rt, false);
	mCurMode = WINDOW;
	return true;
}

int CScreen::Init(HWND hWnd, int fullSrceen)
{		
	mainWnd = hWnd;
	if(fullSrceen == 1)
	{	
		GoFullscreen();
	}
	GetClientRect(mainWnd, &viewPort);
	viewPort.left = viewPort.top = 0;
	viewPort.right = VIEWPORTWIDTH;
	viewPort.bottom = VIEWPORTHEIGHT;
	wndDC = GetDC(mainWnd);
	memDC = CreateCompatibleDC(wndDC);
	memBitmap = CreateCompatibleBitmap(wndDC,viewPort.right, viewPort.bottom);
	SelectObject(memDC, memBitmap);	
	return 1;
}

int CScreen::Present()
{
	StretchBlt(wndDC, 0, 0, SCREENWIDTH, SCREENHEIGHT, memDC, 0, 0, viewPort.right-viewPort.left, viewPort.bottom-viewPort.top, SRCCOPY);

	//BitBlt(wndDC, 0, 0, viewPort.right-viewPort.left, viewPort.bottom-viewPort.top, memDC, 0, 0, SRCCOPY);		
	return 1;
}

int CScreen::Release()
{
	DeleteObject(memBitmap);
	DeleteDC(memDC);
	ReleaseDC(mainWnd, wndDC);
	return 1;
}

HDC& CScreen::GetMemDC()
{
	return memDC;
}

// Vẽ farbackground ở xa và background lên dc ảo
int CScreen::DrawBackGround()
{	
	if(bmFarBackGround)
		bmFarBackGround->Draw(memDC,0,0,(viewPort.left/5)%570,viewPort.top,viewPort.right-viewPort.left,viewPort.bottom-viewPort.top);			
	/*else
	{
		RECT rt;
		rt.left = rt.top = 0;
		rt.right = viewPort.right-viewPort.left;
		rt.bottom = viewPort.bottom-viewPort.top;
		HBRUSH brush = CreateSolidBrush(RGB(0,0,0));
		FillRect(memDC,&rt,brush);
	}*/
	if (bmBackGround)
		bmBackGround->DrawTransparent(memDC,0,0,viewPort.left,viewPort.top,viewPort.right-viewPort.left,viewPort.bottom-viewPort.top,RGB(0,0,0));			
	return 1;
}

int CScreen::MoveViewPortLeft(int iX)
{	
	if (viewPort.left-iX<0)
		return 0;
	viewPort.left -= iX;
	viewPort.right -= iX;
	return 1;
}

int CScreen::MoveViewPortRight(int iX)
{
	if ((viewPort.right+iX)>GetMapSize().x)
		return 0;
	viewPort.left += iX;
	viewPort.right += iX;
	return 1;
}

POINT CScreen::GetMapSize()
{
	return mapSize;
}

int CScreen::LoadMap(CMap* pMap)
{	
	pMap->LoadBitmapMap(bmBackGround);
	mapSize = pMap->GetMapSize();
	return 1;
}
// Load background phía sau
int CScreen::LoadFarBackground(LPCTSTR bgr)
{
	if(bmFarBackGround != NULL)
	{
		delete bmFarBackGround;
		bmFarBackGround = NULL;
	}
	bmFarBackGround = new MyBitmap(bgr);
	return 1;
}
int CScreen::Center()
{
	int center = (viewPort.right - viewPort.left)/2;
	return center;
}

RECT CScreen::ViewPort()
{
	return viewPort;
}