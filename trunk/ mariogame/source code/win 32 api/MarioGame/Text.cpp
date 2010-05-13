#include "StdAfx.h"
#include "Text.h"

MyBitmap* CText::mTextBitmap;
CText::TextBitmap CText::initTextBitmap;

CText::~CText()
{

}
//39330362

void CText::GetPos(TCHAR ch, int& iRow, int& iCol)
{
	ch = toupper(ch);
	if((ch>=_T('0') && ch<=_T('9')))
	{
		iRow = 0;
		iCol = ch - _T('0');
	}
	if((ch>=_T('A') && ch<=_T('Z')))
	{
		iRow = 1;
		iCol = ch - _T('A');
	}
}

void CText::Draw(LPCTSTR strText, HDC hDC, int x, int y)
{
	/*int n = wcslen(strText);
	int i=0;
	TCHAR ch;
	int iRow, iCol;
	for(i=0 ; i<n ; i++)
	{
		ch = strText[i];
		if(ch != _T(' '))
		{
			GetPos(ch, iRow, iCol);
			mTextBitmap->DrawTransparent(hDC,x,y,iCol*mCharWidth,iRow*mCharHeight,mCharWidth,mCharHeight,RGB(255,0,255));			
			x = x + mCharWidth;
		}				
		else
			x = x + mCharWidth/2;
		
	}	*/			 
	int oldMode = SetBkMode(hDC, TRANSPARENT);
	LOGFONT lf;
	HFONT font = (HFONT) GetStockObject(SYSTEM_FONT);
	GetObject(font,sizeof(LOGFONT),(LOGFONT*) &lf);
	lf.lfHeight = 30;
	lf.lfWidth = 0;
	lf.lfWeight = FW_NORMAL;
	wcscpy(lf.lfFaceName, _T("Cooper Black"));	
	font = CreateFontIndirect(&lf);
	HFONT oldFont = (HFONT)SelectObject(hDC, font);	   // vang 241 252 0		 do 167 36 8
	SetTextColor(hDC, RGB(255, 255, 255));
	TextOut(hDC, x, y, strText, wcslen(strText));
	SetBkMode(hDC, oldMode);
	SelectObject(hDC, oldFont);
	DeleteObject(font);
}

void CText::Draw(int num, int numDigit, HDC hDC, int x, int y)
{
	TCHAR strText[15];
	_itow(num, strText, 10);
	Draw(strText, hDC, x, y);
	/*int n = wcslen(strText);
	int i=0;
	TCHAR ch;
	int iRow, iCol;
	for(i=0 ; i<n ; i++)
	{
		ch = strText[i];
		if(ch != _T(' '))
		{
			GetPos(ch, iRow, iCol);
			mTextBitmap->DrawTransparent(hDC,x,y,iCol*mCharWidth,iRow*mCharHeight,mCharWidth,mCharHeight,RGB(255,0,255));			
			x = x + mCharWidth;
		}				
		else
			x = x + mCharWidth/2;	 
	}*/
}