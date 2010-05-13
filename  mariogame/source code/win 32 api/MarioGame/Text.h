#pragma once

//#include "MyBitmap.h"

class CText
{
	static MyBitmap* mTextBitmap;
	class TextBitmap
	{
	public:
		TextBitmap()
		{
			if(mTextBitmap != NULL)
			{
				delete mTextBitmap;
				mTextBitmap = NULL;
			}
			mTextBitmap = new MyBitmap(_T("text.bmp"));
		}
		~TextBitmap()
		{
			delete mTextBitmap;
			mTextBitmap = NULL;
		}
	};		
	static void GetPos(TCHAR ch, int& iRow, int& iCol);
	static TextBitmap initTextBitmap;	
public:	
	static const int mCharWidth = 13;
	static const int mCharHeight = 20;	
	static void Draw(LPCTSTR strText, HDC hDC, int x, int y);
	static void Draw(int num, int numDigit, HDC hDC, int x, int y);
	~CText();
};
