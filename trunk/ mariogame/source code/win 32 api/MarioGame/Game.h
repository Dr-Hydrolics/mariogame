#pragma once

//#include "MyBitmap.h"
#include "Character.h"
#include "Map.h"
#include "Screen.h"
#include "GameMenu.h"
#include "Thread.h"
#include "Sound.h"
#include "Text.h"
#include "GTimer.h"

extern int FRAMES_PER_SEC;
//extern int FRAME_CYCLE;

class CGame
{
private:	
	HWND mainWnd;	
	CScreen* mScreen; // Man hinh
	CGameMenu* mMenu;
	CMap* mMap;	// Ban do
	CGTimer mTimer;
	CObjectManager* mOManager;	
	
	CGameSound *bgrSound;
	CGameSound *bgrSound2;
	int bgSound;
	CGameSound *eventSound;
	int gameState;
	int mPause;
	int iTickCount;
	int mLevel;	
	int mStartLevelTime;
	int mEndLevelTime;
	//HANDLE hThread;
	//MyBitmap *intro;
	LPTSTR mFarBg;
	int mSettings[3]; //0: on, 1: off
	// 0: sound, 1: music, 2: fullscreen
	enum SETTING {Sound= 0, Music= 1, FullScreen= 2};
	//int posIntro;
	int mStartIntroTime;
	int mShowMenu;
	int mFighting;
	enum eGameState{gsMenu=1 ,gsIntro=0, gsPlaying = 2, gsGameOver = -1, gsWin = -2};
	
	void LoadSetting();
	void SaveSetting();
	void UpdateSetting(int *setting);

public:
	static char JUMP;
	static char SIT;
	static char LEFT;
	static char RIGHT;
	static char FIRE;
	CGame(void);	
	~CGame(void);
	int Init(HWND hWnd);
	int LoadRound(int level);
	int StartMenu();
	int Intro();
	int Run();
	int End();	
	int OnKeyDown(WPARAM wParam, LPARAM lParam);
	int OnKeyUp(WPARAM wParam, LPARAM lParam);		
	void OnTimer();
	void Repaint()
	{
		mScreen->Present();
	}
};
