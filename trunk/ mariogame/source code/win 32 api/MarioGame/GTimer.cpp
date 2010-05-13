#include "StdAfx.h"
#include "GTimer.h"

int CGTimer::mStartTime; // in milisecond
LPTSTR CGTimer::strTime;
int CGTimer::mPauseTime;
CGTimer::CGTimer()
{
	mStartTime = 0;
	strTime = new TCHAR[256];
}

CGTimer::~CGTimer()
{
}

int CGTimer::GetSecond()
{
	return (timeGetTime() - mStartTime)/1000;
}
int CGTimer::Time()
{
	return timeGetTime() - mStartTime;
}
int CGTimer::TickCount()
{
	return mStartTime;	
}
void CGTimer::Start()
{
	mStartTime = timeGetTime();
}
void CGTimer::Pause()
{
	mPauseTime = timeGetTime(); 
}
void CGTimer::Resume()
{
	mStartTime = mStartTime + (timeGetTime() - mPauseTime);
}
LPCTSTR& CGTimer::ToString()
{
	int s = Time()/1000;
	int m = s/60;
	s = s%60;
	LPTSTR temp1;// = new TCHAR[32];
	LPTSTR temp2;// = new TCHAR[32];
	temp1 = _T("%d");
	if(m/10 <= 0)
	{
		temp1 = _T("0%d");	
	}
	temp2 = _T(" %d");
	if(s/10 <= 0)
	{
		temp2 = _T(" 0%d");	
	}	
	TCHAR temp[256];
	wcscpy(temp, temp1);
	wcscat(temp, temp2);
	swprintf(strTime, temp, m, s);		
	return (LPCTSTR&)strTime;
}

void CGTimer::Reset()
{
	mStartTime = timeGetTime();
}