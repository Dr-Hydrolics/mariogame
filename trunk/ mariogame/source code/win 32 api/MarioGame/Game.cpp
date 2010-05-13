#include "StdAfx.h"
#include "Game.h"

int FRAMES_PER_SEC = 60;
//int FRAME_CYCLE = 1000/FRAMES_PER_SEC;

char CGame::JUMP = VK_SHIFT;
char CGame::SIT = VK_DOWN;
char CGame::LEFT = VK_LEFT;
char CGame::RIGHT = VK_RIGHT;
char CGame::FIRE = 'Z';

CGame::CGame(void)
{		
	mScreen = new CScreen();
	mMenu = new CGameMenu();
	mMap = new CMap();	
	mainWnd = NULL;	
	iTickCount = 0;
	gameState = gsIntro;
	mOManager = NULL;
	mShowMenu = 0;
	mPause = 0;
	mStartLevelTime = 0;
	mEndLevelTime = 0;
	mStartIntroTime = 0;
	mLevel = 3;
	for(int i=0 ; i<3 ; i++)
	{
		mSettings[i] = 0;
	}				
	bgSound = 0;
	mFighting = 0;
}

CGame::~CGame(void)
{
	if(mScreen)
	{
		delete mScreen; // Man hinh
		mScreen = NULL;
	}
	if(mMenu)
	{
		delete mMenu;
		mMenu = NULL;
	}
	if(mMap)
	{
		delete mMap;	// Ban do
		mMap = NULL;
	}
	if(mOManager)
	{
		delete mOManager;
		mOManager = NULL;
	}
	if(bgrSound)
	{
		bgrSound->Stop();		
	}
	if(eventSound)
	{
		//delete eventSound;
		//eventSound = NULL;
	}

}

void SetBit(int &x, int i)
{
	x = x|(1<<i);	
}

void ClearBit(int &x, int i)
{
	int a = 1<<i;
	a = ~a;
	x = x & (~(1<<i));
}
int GetBit(int x, int i)
{
	return ((x>>i)&1);
}
void CGame::LoadSetting()
{								
	ifstream inFile("setting.dat");
	int setting;
	if(inFile.is_open())
	{
		inFile>>setting;
		for(int i=0 ; i<3 ; i++)
		{
			mSettings[i] = GetBit(setting, i);
		}		
	}
	CGameSound::EnableSound(mSettings[Sound]);
	CGameSound::EnableMusic(mSettings[Music]);
	inFile.close();
}

void CGame::UpdateSetting(int *setting)
{
	for(int i=0 ; i<3 ; i++)
	{
		mSettings[i] = setting[i];
	}			
	if(mSettings[FullScreen] == 1)
	{
		mScreen->GoFullscreen(); 		
	}
	else
	{
		mScreen->GoWindowedMode();			
	}
	CGameSound::EnableSound(mSettings[Sound]);
	CGameSound::EnableMusic(mSettings[Music]);

	if(mSettings[Music] == 1 && gameState == gsPlaying)
	{					   		
		bgrSound->Play(1);	
		if(mFighting == 1)
			bgrSound2->Play(1);
	}	
	if(mSettings[Music] == 0 && gameState == gsPlaying && bgrSound != NULL)
	{
		bgrSound->Stop();
		bgrSound2->Stop();
	}

}
void CGame::SaveSetting()
{
	ofstream outFile("setting.dat");
	int setting;
	setting = 0;
	if(outFile.is_open())
	{			
		for(int i=0 ; i<3 ; i++)
		{
			if(mSettings[i] == 1)
			{
				SetBit(setting, i);
			}
			else
			{
				ClearBit(setting, i);
			}
		}
		outFile<<setting;
	}	
	outFile.close();
}

int CGame::Init(HWND hWnd)
{		
	LoadSetting();
	mLevel = 1;
	gameState = gsIntro;
	mOManager = new CObjectManager();		 
	bgrSound = new CGameSound("Music\\background.wav");
	
	// Init the screen
	mainWnd = hWnd;	
	mScreen->Init(hWnd, mSettings[FullScreen]);	
	// End		   
	
	Intro();	  	
	return 1;
}
   
int CGame::Intro()
{	
	mStartIntroTime = GetTickCount();
	mScreen->LoadFarBackground(_T("intro.bmp"));
	mScreen->DrawBackGround();
	mScreen->Present();
	return 1;	
}

int CGame::StartMenu()
{	
	mScreen->LoadFarBackground(_T("background.bmp"));	
	mScreen->DrawBackGround();
	//load Menu
	mMenu->Init(_T("menu.bmp"), mSettings);
	mMenu->Draw(mScreen->GetMemDC(),mScreen->ViewPort(), 0);
	mScreen->Present();	 	
	return 1;
}

int CGame::LoadRound(int level)
{	
	// Load far background
	LPTSTR initFile = new TCHAR[256];
	wsprintf(initFile,_T("Map\\level%d.init"), level);	
	ifstream inFile(initFile);	
	if(inFile.is_open() == 0)
		return -1;
	string sTemp;
	inFile>>sTemp;
	mFarBg = stringtowchar(sTemp);
	// End

	// Load map
	mMap->Init(_T("maptiles.bmp"));
	LPTSTR temp = new TCHAR[256];
	wsprintf(temp,_T("Map\\level%d.map"),level);
	mMap->LoadMapData(temp);
	mScreen->LoadMap(mMap);
	// End

	// Start game timer
	CGTimer::Start();
	// End

	// Load game Objects	
	mOManager->Init(level, mMap);	
	// End

	// Draw everthing to screen
	mScreen->ViewPortXMaxLeft();
	mScreen->LoadFarBackground(mFarBg);
	mOManager->Present(mScreen);
	mScreen->DrawBackGround();
	// End

	// Copy from MemDC to Client DC
	mScreen->Present();	
	// End
	
	// Load background music when fighting with boss
	char* temp2 = new char[256];
	if(bgrSound2 != NULL)
	{
		bgrSound2->Stop();
	}
	sprintf(temp2, "Music\\bgBoss%d.wav", level);
	bgrSound2 = new CGameSound(temp2);		  	
	//End

	// Start background music
	if(mSettings[Music] == 1)
	{
		bgrSound->Play(1);
	}
	// End

	// Play begin level music
	eventSound = new CGameSound("Music\\beginlevel.wav");
	eventSound->Play(0);
	// End
	
	// Init variables
	iTickCount = GetTickCount();
	mStartLevelTime = GetTickCount();
	mPause = 0;
	mShowMenu = 0;
	// End
			
	return 1;
}
int CGame::Run()
{  			
	if(gameState == gsGameOver && mPause == 0)
	{
		mScreen->DrawBackGround();
		CText::Draw(_T("Game over"), mScreen->GetMemDC(), (mScreen->GetViewPortWidth() - CText::mCharWidth*9)/2 , mScreen->GetViewPortHeight()/2 - 30);
		mScreen->Present();																														   		
	}
	if(gameState == gsWin && mPause == 0)
	{
		mScreen->DrawBackGround();
		CText::Draw(_T("Game win"), mScreen->GetMemDC(), (mScreen->GetViewPortWidth() - CText::mCharWidth*9)/2 , mScreen->GetViewPortHeight()/2 - 30);
		mScreen->Present();																														   		
	}
	if (gameState==gsIntro)
	{
		if(GetTickCount() - mStartIntroTime >= 3000 )
		{
			gameState=gsMenu;
			StartMenu();
		}
		return 1;
	}
	int res = 0;
	if(GetTickCount() - iTickCount >= 1000/FRAMES_PER_SEC && gameState==gsPlaying && mPause == 0)
	{		
		iTickCount = GetTickCount();			
		res = mOManager->Animate(mScreen);					
		mScreen->DrawBackGround();	
		mOManager->Present(mScreen);			
		CText::Draw(mTimer.ToString(), mScreen->GetMemDC(), mScreen->GetViewPortWidth() - CText::mCharWidth*6 , 0);
		if(mStartLevelTime != 0)
		{
			if(GetTickCount() - mStartLevelTime <= 2000)
			{				
				TCHAR *temp = new TCHAR[256];
				wsprintf(temp,_T("Ready for level %d"),mLevel);
				CText::Draw(temp, mScreen->GetMemDC(), (mScreen->GetViewPortWidth() - CText::mCharWidth*9)/2 , mScreen->GetViewPortHeight()/2 - 30);
				delete temp;
				temp = NULL;
			}
			else
			{
				mStartLevelTime = 0;
			}									
		}
		if(mEndLevelTime != 0)
		{	 
			if(GetTickCount() - mEndLevelTime <= 4000)
			{
				TCHAR *temp = new TCHAR[256];
				wsprintf(temp,_T("Finish level %d"),mLevel);
				CText::Draw(temp, mScreen->GetMemDC(), (mScreen->GetViewPortWidth() - CText::mCharWidth*9)/2 , mScreen->GetViewPortHeight()/2 - 30);
				delete temp;
			}
			else
			{
				mOManager->Release();
				mLevel++;
				mEndLevelTime = 0;
				if(mLevel>3)
				{
					gameState = gsWin; // chien thang					
				}
				LoadRound(mLevel);	
				return 1;
			}
		}
		mScreen->Present();		
		if(res == -1)	  // game over
		{
			gameState = gsGameOver;
		}
		if(res == 1)	  // ket thuc level
		{				
			mFighting = 0;
			mEndLevelTime = GetTickCount();	
			if(mLevel < 3)
			{
				eventSound = new CGameSound("Music\\finishlevel.wav");
			}
			else
			{
				eventSound = new CGameSound("Music\\win.wav");
			}
			eventSound->Play(0);
			if(bgrSound2 != NULL)
				bgrSound2->Stop();
		}
		if(res == 2) // mario gap quai vat
		{
			mFighting = 1;
			if(bgrSound != NULL)
				bgrSound->Stop();
			if(bgrSound2 != NULL)
				bgrSound2->Play(1);
		}
	}
	return 1;
}

int CGame::End()
{
	SaveSetting();
	if(mScreen)
	{
		delete mScreen; // Man hinh
		mScreen = NULL;
	}
	if(mMenu)
	{
		delete mMenu;
		mMenu = NULL;
	}
	if(mMap)
	{
		delete mMap;	// Ban do
		mMap = NULL;
	}
	if(mOManager)
	{
		delete mOManager;
		mOManager = NULL;
	}
	if(bgrSound)
	{
		//delete bgrSound;
		//bgrSound = NULL;
	}
	if(eventSound)
	{
		//delete eventSound;
		//eventSound = NULL;
	}
	return 1;
}

int CGame::OnKeyDown(WPARAM wParam, LPARAM lParam)
{	
	if((gameState == gsPlaying || gameState == gsGameOver || gameState == gsWin) && wParam == 'M')
	{
		mShowMenu = 1 - mShowMenu;
		mPause = mShowMenu;
		if(mPause == 1)
		{
			CGTimer::Pause(); 			
			mScreen->DrawBackGround();	
			mOManager->Present(mScreen);
			mMenu->Draw(mScreen->GetMemDC(), mScreen->ViewPort(), 1);  		
			mScreen->Present();
		}														
		else
		{
			CGTimer::Resume();				 		
		}												 
	}
	if (gameState==gsMenu || mShowMenu == 1)
	{
		int i=mMenu->OnKeyDown(wParam, lParam);
		if(i==0)
		{ 
			
			mScreen->DrawBackGround();	
			if(mOManager != NULL)	
			mOManager->Present(mScreen);		
			mMenu->Draw(mScreen->GetMemDC(), mScreen->ViewPort(), mShowMenu);
			mScreen->Present();
		}
		if (i==1)// Nguoi choi chon 1 item
		{
			if (mMenu->GetSelItem()==0)// New game
			{
				gameState=gsPlaying;
				if(mOManager != NULL)
					mOManager->Release();
				LoadRound(mLevel);
			}
			int exitItem = 3;
			int backItem = 4;
			if(gameState == gsPlaying || gameState == gsGameOver || gameState == gsWin)
			{
				exitItem = 4;
				backItem = 3;
			}
			if (mMenu->GetSelItem()==exitItem)// Exit game
			{
				PostQuitMessage(0);
			}
			if (mMenu->GetSelItem()==backItem)// Back to game
			{
				mScreen->LoadFarBackground(mFarBg);	
				mPause = mShowMenu = 0;				
				CGTimer::Resume();					
			}
		}
		if( i == 2)// Cap nhat setting
		{
			int* options = mMenu->GetOptions();
			UpdateSetting(options);
			mScreen->DrawBackGround();	
			if(mOManager != NULL)
				mOManager->Present(mScreen);
			mMenu->Draw(mScreen->GetMemDC(), mScreen->ViewPort(), mShowMenu);
			mScreen->Present();			
		}
	}
	return 1;
}

void CGame::OnTimer()
{

}
TCHAR* stringtowchar(string &str)
{
	int len = str.length();
	TCHAR *res = new TCHAR[len+1];
	int i=0;
	for (i=0 ; i<len ; i++)
	{
		res[i] = str[i];
	}
	res[i] = 0;
	return res;
}
char* stringtochar(string &str)
{
	int len = str.length();
	char *res = new char[len+1];
	int i=0;
	for (i=0 ; i<len ; i++)
	{
		res[i] = str[i];
	}
	res[i] = 0;
	return res;
}