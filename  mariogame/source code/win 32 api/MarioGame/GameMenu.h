#pragma once

#include "Sound.h"
#include "vector"
#include "string"
using namespace std;

class IGameMenu
{
public:
	virtual ~IGameMenu(){};
	virtual int  Init(LPCTSTR bmName, int settings[]) = 0;
	virtual int  Draw(HDC hDC, RECT viewPort) = 0;
	virtual int  OnKeyDown (WPARAM wParam, LPARAM lParam) = 0;
	virtual int  GetSelItem() = 0;
};
class CGameMenu/* : public IGameMenu*/
{
private:
	// how to play: walk left, walk right, jump, sit, fire,
	// 75 100 50
	// exit 130 300 50 20
	// menu name 70 30
	int itemCount;	
	int itemWidth;
	int itemHeight;
	int nWidth;
	int nHeight;
	MyBitmap* bmMenu;
	MyBitmap* bmHowTo;
	int mHowtoplay;
	vector<MyBitmap*> bmMenus;
	vector<LPTSTR> mItemNames;
	int DrawSelItem(HDC hDC, int x, int y);
	LPTSTR mMenuName;
	int mCurMenu;
	enum CURMENU {MainMenu = 0, OptionMenu = 1};
	// option: sound, music, fullscreen
	int mOptions[3];	
public:
	int mCurItem;
	CGameMenu();
	~CGameMenu();
	int* GetOptions()
	{
		return mOptions;
	}
	int Init(LPCTSTR bmName, int settings[]);
	int Draw(HDC hDC, RECT viewPort, int playing);
	int OnKeyDown (WPARAM wParam, LPARAM lParam);
	int GetSelItem();
};
