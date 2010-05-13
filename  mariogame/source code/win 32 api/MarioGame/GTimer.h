#pragma once

class CGTimer
{
	static int mStartTime; // in milisecond
	static LPTSTR strTime;
	static int mPauseTime;
public:
	CGTimer();
	~CGTimer();
	static int GetSecond();
	static void Pause();
	static void Resume();
	static int Time(); // lay thoi gian milisecond
	static void Start();
	static int TickCount();
	static LPCTSTR& ToString(); //
	static void Reset();
};
