#include "StdAfx.h"
#include "MyBitmap.h"

MyBitmap::MyBitmap(void)
{
}

MyBitmap::~MyBitmap(void)
{
	if(hBitmap)
		DeleteObject(hBitmap);
}

MyBitmap::MyBitmap(LPCTSTR bmName)
{	
	HINSTANCE hInst = NULL;
	hBitmap = (HBITMAP)LoadImage(hInst, bmName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void MyBitmap::Draw(HDC pDC, int x, int y)
{
	if(!hBitmap)
		return;
	try
	{	
		HDC dcImage;
		dcImage = CreateCompatibleDC(pDC);		
			// Select the image into the appropriate dc
		HBITMAP pOldBitmapImage = (HBITMAP)SelectObject(dcImage,hBitmap);
		BITMAP bm;
		GetObject(hBitmap, sizeof(BITMAP), &bm);
		int nWidth = bm.bmWidth;
		int nHeight = bm.bmHeight;
		BitBlt(pDC, x, y, nWidth, nHeight, dcImage, 0, 0, SRCCOPY);
		// Restore settings
		SelectObject(dcImage, pOldBitmapImage);	
		// Delete DC and Bitmap
		DeleteDC(dcImage);
		DeleteObject(pOldBitmapImage);
	}
	catch(char* str)
	{

	}
}

void MyBitmap::DrawTransparent(HDC pDC, int x, int y, COLORREF crColour)
{
	if(!hBitmap)
		return;
	try
	{		
		COLORREF crOldBack = SetBkColor(pDC,RGB(255,255,255));
		COLORREF crOldText = SetTextColor(pDC,RGB(0,0,0));
		HDC dcImage, dcTrans;
		dcImage = CreateCompatibleDC(pDC);
		dcTrans = CreateCompatibleDC(pDC);
		
		// Select the image into the appropriate dc
		HBITMAP pOldBitmapImage = (HBITMAP)SelectObject(dcImage,hBitmap);
		
		// Create the mask bitmap
		HBITMAP bitmapTrans;
		BITMAP bm;
		
		GetObject(hBitmap, sizeof(BITMAP), &bm);
		int nWidth = bm.bmWidth;
		int nHeight = bm.bmHeight;
		bitmapTrans = CreateBitmap(nWidth,nHeight,1,1,NULL);
		// Select the mask bitmap into the appropriate dc
		HBITMAP pOldBitmapTrans = (HBITMAP)SelectObject(dcTrans,bitmapTrans);
		
		// Build mask based on transparent colour
		SetBkColor(dcImage, crColour);
		BitBlt(dcTrans, 0, 0, nWidth, nHeight, dcImage, 0, 0, SRCCOPY );
		
		// Do the work - True Mask method - cool if not actual display		
		BitBlt(pDC, x, y, nWidth, nHeight, dcImage, 0, 0, SRCINVERT);
		BitBlt(pDC, x, y, nWidth, nHeight, dcTrans, 0, 0, SRCAND);
		BitBlt(pDC, x, y, nWidth, nHeight, dcImage, 0, 0, SRCINVERT);
		// Restore settings
		SelectObject(dcImage, pOldBitmapImage);		
		SelectObject(dcTrans, pOldBitmapTrans);
		SetBkColor(pDC, crOldBack);		
		SetTextColor(pDC, crOldText);
		// Delete DC and Bitmap
		DeleteDC(dcImage);
		DeleteDC(dcTrans);
		DeleteObject(pOldBitmapImage);
		DeleteObject(pOldBitmapTrans);
		DeleteObject(bitmapTrans);
	}
	catch(char* str)
	{
	
	}
}

void MyBitmap::DrawTransparent(HDC pDC, int x, int y,int x1, int y1,int width,int height, COLORREF crColour)
{
	if(!hBitmap)
		return;
	try
	{
		COLORREF crOldBack = SetBkColor(pDC,RGB(255,255,255));
		COLORREF crOldText = SetTextColor(pDC,RGB(0,0,0));
		HDC dcImage, dcTrans;
		dcImage = CreateCompatibleDC(pDC);
		dcTrans = CreateCompatibleDC(pDC);

		// Select the image into the appropriate dc
		HBITMAP pOldBitmapImage = (HBITMAP)SelectObject(dcImage,hBitmap);
		// Create the mask bitmap
		HBITMAP bitmapTrans;
		BITMAP bm;

		GetObject(hBitmap, sizeof(BITMAP), &bm);
		int nWidth = width;
		int nHeight = height;
		bitmapTrans = CreateBitmap(nWidth,nHeight,1,1,NULL);
		// Select the mask bitmap into the appropriate dc
		HBITMAP pOldBitmapTrans = (HBITMAP)SelectObject(dcTrans,bitmapTrans);

		// Build mask based on transparent colour
		SetBkColor(dcImage, crColour);
		BitBlt(dcTrans, 0, 0, nWidth, nHeight, dcImage,  x1, y1, SRCCOPY );

		// Do the work - True Mask method - cool if not actual display		
		BitBlt(pDC, x, y, nWidth, nHeight, dcImage, x1, y1, SRCINVERT);
		BitBlt(pDC, x, y, nWidth, nHeight, dcTrans, 0, 0, SRCAND);
		BitBlt(pDC, x, y, nWidth, nHeight, dcImage, x1, y1, SRCINVERT);

		// Restore settings
		SelectObject(dcImage, pOldBitmapImage);		
		SelectObject(dcTrans, pOldBitmapTrans);
		SetBkColor(pDC, crOldBack);		
		SetTextColor(pDC, crOldText);
		// Delete DC and Bitmap
		DeleteDC(dcImage);
		DeleteDC(dcTrans);
		DeleteObject(pOldBitmapImage);
		DeleteObject(pOldBitmapTrans);
		DeleteObject(bitmapTrans);
	}
	catch(char* str)
	{
	
	}
}