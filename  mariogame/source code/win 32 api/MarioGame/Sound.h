#ifndef SOUND_H
#define SOUND_H

//DWORD WINAPI playBGSound(LPVOID lparam);
//DWORD WINAPI playSound(LPVOID lparam);
#define IDR_WAVE1  134
class CMidiSound
{
	int m_uiMIDIPlayerID;	
public:
	CMidiSound();
	~CMidiSound();
	void PlayMIDISong(LPTSTR szMIDIFileName, BOOL bRestart);
	void PauseMIDISong();
	void CloseMIDIPlayer();	
};
#define OFFSET_FORMATTAG			20
#define OFFSET_CHANNELS				22
#define OFFSET_SAMPLESPERSEC		24
#define OFFSET_AVGBYTESPERSEC		28
#define OFFSET_BLOCKALIGN			32
#define OFFSET_BITSPERSAMPLE		34
#define OFFSET_WAVEDATA				44
#define HEADER_SIZE	                OFFSET_WAVEDATA


class CGameSound
{
	char *lpfile;
	int file_size;
	WAVEHDR* whdr;
	WAVEFORMATEX wfex;
	HWAVEOUT hwo;
	static int mEnableSound;
	static int mEnableMusic;
	
public:
	int mState; // 0: stop, 1: playing
	static void EnableSound(int enable)
	{
		mEnableSound = enable;
	}
	static void EnableMusic(int enable)
	{
		mEnableMusic = enable;
	}
	WAVEHDR* Play(bool loop);
	void Stop(/*WAVEHDR *whdr*/);
	CGameSound()
	{
	}
	CGameSound(LPSTR szFileName);
	~CGameSound();
};
#endif