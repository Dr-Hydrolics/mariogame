#pragma once
//#include "MyBitmap.h"

#include "Map.h"

//#define SCREENWIDTH GetSystemMetrics(SM_CXSCREEN)
//#define SCREENHEIGHT GetSystemMetrics(SM_CYSCREEN)

//#define SCREENWIDTH (640+6)
//#define SCREENHEIGHT (480+26)
//#define VIEWPORTWIDTH (640+6)
//#define VIEWPORTHEIGHT (480+26)
extern int SCREENWIDTH;
extern int SCREENHEIGHT;
extern int VIEWPORTWIDTH;
extern int VIEWPORTHEIGHT;

class CScreen
{
private:
	HWND mainWnd; // Handle của cửa sổ chương trình
	HDC wndDC;	// HDC của cửa sổ chương trình
	HDC memDC;	// Memory HDC
	HBITMAP memBitmap; // Memory HBitmap
	MyBitmap* bmBackGround; // Hình ảnh của thế giới
	MyBitmap* bmFarBackGround;
	POINT mapSize;
	RECT viewPort;	// Tọa độ của phần thế giới hiển thị lên màn hình	
	enum MODE {WINDOW=0, FULLSCREEN=1};
	int mCurMode;
public:
	CScreen();
	~CScreen();	
	bool GoFullscreen();
	bool GoWindowedMode();
	int Init(HWND hWnd, int fullSrceen);	// Khởi tạo màn hình
	int Present();	// Trình diễn lên màn hình cửa sổ. Chép ảnh từ dc ảo lên dc màn hình cửa sổ
	int Release();	// Giải phóng các đối tượng mà màn hình đang nắm giữ
	int LoadMap(CMap* pMap);
	int LoadFarBackground (LPCTSTR bgrName);
	HDC& GetMemDC();
	//MyBitmap*& GetBMBackGround();
	int DrawBackGround();
	int MoveViewPortLeft(int iX);
	int MoveViewPortRight(int iX);
	int Center();
	
	int GetViewPortWidth()
	{
		return viewPort.right - viewPort.left;
	}
	int GetViewPortHeight()
	{
		return viewPort.bottom - viewPort.top;
	}
	RECT ViewPort();
	POINT GetMapSize();
	void SetViewPortX(int x)
	{
		int w = viewPort.right - viewPort.left;
		if((x - w/2) > 0)
			viewPort.left = x - w/2;
		else
			viewPort.left = 0;
		viewPort.right =  viewPort.left + w;
	}
	void ViewPortXMaxLeft()
	{
		int w = viewPort.right - viewPort.left;
		viewPort.left = 0;
		viewPort.right = w;
	}
	void ViewPortXMaxRight()
	{
		int w = viewPort.right - viewPort.left;
		viewPort.left = mapSize.x - w;
		viewPort.right = mapSize.x;
	}
};
