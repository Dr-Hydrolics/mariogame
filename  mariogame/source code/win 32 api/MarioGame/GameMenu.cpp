#include "StdAfx.h"
#include "GameMenu.h"

CGameMenu::CGameMenu(void)
{
	itemCount = 5;
	mCurItem = 0;
	itemWidth = 150;
	itemHeight = 25;
	nWidth = 300;
	nHeight = 400;
	bmMenu = NULL;
	mHowtoplay = 0;
	bmHowTo = NULL;
}

CGameMenu::~CGameMenu(void)
{
	if(bmMenu)
		delete bmMenu;
}

int CGameMenu::Init(LPCTSTR bmName, int settings[])
{						
	itemCount = 4;						
	bmMenu = new MyBitmap(bmName);	
	bmHowTo = new MyBitmap(_T("howtoplay.bmp"));
	mItemNames.push_back(_T("New Game"));
	mItemNames.push_back(_T("Options"));
	mItemNames.push_back(_T("How to play"));
	mItemNames.push_back(_T("Exit"));
	mMenuName = _T("Main Menu");
	mCurMenu = MainMenu;

	for(int i=0 ; i<3 ; i++)
	{
		mOptions[i] = settings[i];
	}							  	
	return 1;
}

int CGameMenu::Draw(HDC hDC, RECT viewPort, int playing)
{		
	int x=0, y=0;
	x = (viewPort.right - viewPort.left - nWidth)/2 - 3;
	y = (viewPort.bottom - viewPort.top - nHeight)/2;				
	if(mHowtoplay == 1)
	{
		bmHowTo->Draw(hDC, x, y);
		return 0;
	}
	bmMenu->DrawTransparent(hDC, x, y, RGB(255, 0, 255));		

	int oldMode = SetBkMode(hDC, TRANSPARENT);
	LOGFONT lf;
	HFONT font = (HFONT) GetStockObject(SYSTEM_FONT);
	GetObject(font,sizeof(LOGFONT),(LOGFONT*) &lf);
	lf.lfHeight = 23;
	lf.lfWidth = 0;
	lf.lfWeight = FW_NORMAL;
	wcscpy(lf.lfFaceName, _T("Cooper Black"));	
	font = CreateFontIndirect(&lf);
	HFONT oldFont = (HFONT)SelectObject(hDC, font);	   // vang 241 252 0		 do 167 36 8	
	RECT rt;
	if(playing == 1 && mCurMenu == MainMenu)
	{
		// exit 130 300 50 20
		itemCount = 5;
		rt.left = x + 75;
		rt.right = x + 75 + itemWidth + 10;
		rt.top = y + 295;
		rt.bottom = y + 295 + itemHeight + 10;
		SetTextColor(hDC, RGB(167, 36, 8));
		if(mCurItem == itemCount - 1)
			SetTextColor(hDC, RGB(240, 0, 0));
		DrawText(hDC, _T("Exit"), wcslen(_T("Exit")), &rt, DT_CENTER);
		mItemNames[3] = _T("Resume");
		mMenuName = _T("Game Pause");
	}
	else
	{
		itemCount = 4;		
		if(mCurMenu == MainMenu)	 
		{
			mItemNames[3] = _T("Exit");
			mMenuName = _T("Main Menu");
		}
	}
		 	
	for(int i=0 ; i<mItemNames.size() ; i++)
	{
		rt.left = x + 70;
		rt.right = x + 70 + itemWidth + 10;
		rt.top = y + 100 + i*50;
		rt.bottom = y + 100 + i*50 + itemHeight + 10;
		SetTextColor(hDC, RGB(167, 36, 8));
		if(i == mCurItem)
			SetTextColor(hDC, RGB(240, 0, 0));
		DrawText(hDC, mItemNames[i], wcslen(mItemNames[i]), &rt, DT_CENTER);
	}
	
	/*SetTextColor(hDC, RGB(240, 0, 0));
	rt.left = x + 70;
	rt.right = x + 70 + itemWidth + 10;
	rt.top = y + 100 + mCurItem*50;
	rt.bottom = y + 100 + mCurItem*50 + itemHeight + 10;
	DrawText(hDC, mItemNames[mCurItem], wcslen(mItemNames[mCurItem]), &rt, DT_CENTER);*/
	
	// menu name 70 30
	rt.left = x + 70;
	rt.right = x + 70 + itemWidth + 10;
	rt.top = y + 30;
	rt.bottom = y + 30 + itemHeight + 10;
	SetTextColor(hDC, RGB(240, 0, 0));
	DrawText(hDC, mMenuName, wcslen(mMenuName), &rt, DT_CENTER);
	
	SetBkMode(hDC, oldMode);
	SelectObject(hDC, oldFont);
	DeleteObject(font);
	
	return 1;
}
int CGameMenu::DrawSelItem(HDC hDC, int x, int y)
{
	if(mCurItem<4)
		MyBitmap::DrawRect(hDC, x + 70, y + 100 + mCurItem*50, itemWidth + 10, itemHeight + 10, RGB(0,165,255), 90);
	return 1;
}
int CGameMenu::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	if(wParam == VK_ESCAPE && mCurMenu == MainMenu && mCurItem == 2)
	{
		mCurItem = 0;
		mHowtoplay = 0;
		return 0;
	}
	if(mHowtoplay == 1)
		return 0;
	if (wParam==VK_DOWN)
	{
		mCurItem=(mCurItem+1)%itemCount;		
		return 0;
	}
	if (wParam==VK_UP)
	{		
		mCurItem=(mCurItem-1+itemCount)%itemCount;
		return 0;
	}
	if (wParam==VK_RETURN)
	{				
		if(mCurMenu == MainMenu)
		{
			if(mCurItem == 1)
			{
				mCurItem = 0;
				mCurMenu = OptionMenu;
				mMenuName = _T("Options");
				mItemNames.clear();
				if(mOptions[0] == 0)
					mItemNames.push_back(_T("Sound: Off"));
				else
					mItemNames.push_back(_T("Sound: On"));
				if(mOptions[1] == 0)
					mItemNames.push_back(_T("Music: Off"));
				else
					mItemNames.push_back(_T("Music: On"));
				if(mOptions[2] == 0)
					mItemNames.push_back(_T("FullScreen: Off"));
				else
					mItemNames.push_back(_T("FullScreen: On"));
				mItemNames.push_back(_T("Back"));		   			
				return 0;
			}
			if(mCurItem == 2)
			{
				mHowtoplay = 1;
				return 0;
			}
			return 1;			
		}
		if(mCurMenu == OptionMenu && mCurItem == 3)
		{
			mCurItem = 0;
			mCurMenu = MainMenu;
			mMenuName = _T("Main Menu");
			mItemNames.clear();
			mItemNames.push_back(_T("New Game"));
			mItemNames.push_back(_T("Options"));
			mItemNames.push_back(_T("How to play"));
			mItemNames.push_back(_T("Resume"));	   			
			return 2;
		}
	}
	if((wParam == VK_RIGHT || wParam == VK_LEFT) && mCurMenu == OptionMenu)
	{
		if(mCurItem>=0 && mCurItem<3)
		{
			mOptions[mCurItem] = 1 - mOptions[mCurItem];			
			/*mItemNames.clear();
			if(mOptions[0] == 0)
				mItemNames.push_back(_T("Sound: Off"));
			else
				mItemNames.push_back(_T("Sound: On"));
			if(mOptions[1] == 0)
				mItemNames.push_back(_T("Music: Off"));
			else
				mItemNames.push_back(_T("Music: On"));
			if(mOptions[2] == 0)
				mItemNames.push_back(_T("FullScreen: Off"));
			else
				mItemNames.push_back(_T("FullScreen: On"));
			mItemNames.push_back(_T("Back"));*/
			
			switch(mCurItem)
			{
			case 0:
				if(mOptions[0] == 0)
					mItemNames[0] = _T("Sound: Off");
				else
					mItemNames[0] = _T("Sound: On");
				break;
			case 1:
				if(mOptions[1] == 0)
					mItemNames[1] = _T("Music: Off");
				else
					mItemNames[1] = _T("Music: On");
				break;
			case 2:
				if(mOptions[2] == 0)
					mItemNames[2] = _T("FullScreen: Off");
				else
					mItemNames[2] = _T("FullScreen: On");
				break;
			}
			return 0;
		}
	}	
	return -1;
}
int CGameMenu::GetSelItem()
{
	return mCurItem;
}
