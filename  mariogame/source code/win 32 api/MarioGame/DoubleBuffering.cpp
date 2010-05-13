// DoubleBuffering.cpp : Definiert den Einstiegspunkt für die Anwendung.
//Developed by Markus Koppensteiner

#include "stdafx.h"
#include "DoubleBuffering.h"
#define MAX_LOADSTRING 100

// Globale Variablen:
HINSTANCE hInst;								// Aktuelle Instanz
TCHAR szTitle[MAX_LOADSTRING];					// Titelleistentext
TCHAR szWindowClass[MAX_LOADSTRING];			// Klassenname des Hauptfensters

// USERDEFINED GLOBAL VARIABLES AND FUNCTIONS
Bitmap_Operations *biop;
int growth =0;
int addition =0;
int left,right,bottom,top;
RECT rect;
bool double_buffer = true;
void Draw_With_Buffering();
void Draw_Without_Buffering(HWND handle);

//End of Userdefined section

// Vorwärtsdeklarationen der in diesem Codemodul enthaltenen Funktionen:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Hier Code einfügen.
	MSG msg;
	HACCEL hAccelTable;

	// Globale Zeichenfolgen initialisieren
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DOUBLEBUFFERING, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Anwendungsinitialisierung ausführen:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_DOUBLEBUFFERING);

	// Hauptmeldungsschleife:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNKTION: MyRegisterClass()
//
//  ZWECK: Registriert die Fensterklasse.
//
//  KOMMENTAR:
//
//    Sie müssen die Funktion zu verwenden, wenn Sie möchten, dass der Code
//    mit Win32-Systemen kompatibel ist, bevor die Funktion 'RegisterClassEx'
//    zu Windows 95 hinzugefügt wurde. Der Aufrud der Funktion ist wichtig,
//    damit die kleinen Symbole, die mit der Anwendung verknüpft sind,
//    richtig formatiert werden.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_DOUBLEBUFFERING);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCTSTR)IDC_DOUBLEBUFFERING;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNKTION: InitInstance(HANDLE, int)
//
//   ZWECK: Speichert das Instanzenhandle und erstellt das Hauptfenster.
//
//   KOMMENTAR:
//
//        In dieser Funktion wird das Instanzenhandle in einer globalen Variablen gespeichert, und das
//        Hauptprogrammfenster wird erstellt und angezeigt.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Instanzenhandle in der globalen Variablen speichern

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      200, 200, 260, 260, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNKTION: WndProc(HWND, unsigniert, WORD, LONG)
//
//  ZWECK:  Verarbeitet Meldungen vom Hauptfenster.
//
//  WM_COMMAND	- Verarbeiten des Anwendungsmenüs
//  WM_PAINT	- Zeichnen des Hauptfensters
//  WM_DESTROY	- Beenden-Meldung anzeigen und zurückgeben
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message) 
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		// Menüauswahl bearbeiten:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_BUFFER:
			double_buffer = true;
			break;
		case ID_NO_BUFFER:
			double_buffer = false;
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_CREATE:
		{//Code to create instance of class and initialize buffers
         
		  biop = new Bitmap_Operations();
		   
		  //provides size of inner window (client area) and
		  // stores it in a RECT Structure 
		  GetClientRect(hWnd,&rect);
		  //Settings for the ellipse
		    left = rect.right /2 -100;
		    top = rect.bottom /2 -20;
		    right = left + 200;
		    bottom = top +20;
			addition = 1;

		  biop->Initialize_Buffers(hWnd,1);
		  
		  //SetTimer(Window_handle,identification number,x millieseconds=>
		  //Event shall happen every x millieseconds,TimerProc=> not needed here)
		   SetTimer(hWnd,1,15,0);//(A)
		   biop->Create_Buffer(0);//(B)
		}
		break;
	//will be called periodically, if SetTimer function is invoked.
    //In our case the WM_TIMER event occurs every 15 seconds see (A)
	case WM_TIMER:
		{
		  //controls growth of the ellipse
		  if (growth > 50 || growth < 0)
			  addition *= -1;
		  growth += addition;

		 if(double_buffer == true)
			Draw_With_Buffering();
		/else
            Draw_Without_Buffering(hWnd);
		}
        break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Fügen Sie hier den Zeichnungscode hinzu...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		KillTimer(hWnd,1);
		//Release Memory of Buffer
		 biop->Free_Buffer(0);
		 delete biop;
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Meldungshandler für Infofeld.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}

//EXTRA FUNCTIONS
void Draw_With_Buffering()
{
	      
          HBRUSH brush = CreateSolidBrush(RGB(200,170,20));
		  HBRUSH background_brush = CreateSolidBrush(RGB(255,255,255));
          
		  //brush is applied to the buffer  we created 
		  // with biop->CreateBuffer(0) see (B), we get the buffer devive context (DC)
          // by calling biop->Get_DC_Buffer(0)
		  SelectObject(biop->Get_DC_Buffer(0),brush);
          //SelectObject(biop->Get_DC_Buffer(0),background_brush);

		  //FillRect fills the  buffer DC with the colour white
		  FillRect(biop->Get_DC_Buffer(0),&rect,background_brush);
		  //the drawing function ellipse is applied to the buffer DC
		  // we draw the ellipse onto the surface of the buffer stored in memory
		  Ellipse(biop->Get_DC_Buffer(0),left + growth ,top - growth  
			  ,right - growth,bottom+ growth);
		  //the content of the buffer DC (the ellipse) is copied onto the
		  // screen, strictly speaking onto the device context (hDC) of the
		  // main window
          biop->Copy_to_Screen(0);

		  //realease memory of the brushes
		  DeleteObject(background_brush);
		  DeleteObject(brush);
}
void Draw_Without_Buffering(HWND handle)
{
	      //window is deleted by filling it up with the current
	      // background color (=white)
	      InvalidateRect(handle,NULL,true);
          UpdateWindow(handle);
          
		  //Get the device context for the main window
		  HDC hDC = GetDC(handle);

		  
	      HBRUSH brush = CreateSolidBrush(RGB(200,170,20));
          SelectObject(hDC,brush);
          
		  //Ellipse function is applied to the device context of the
		  // main window
          Ellipse(hDC,left + growth ,top - growth  
			  ,right - growth,bottom+ growth); 
		  
		  //Realease memory
		  DeleteObject(brush);
          ReleaseDC(handle,hDC);
 
}
