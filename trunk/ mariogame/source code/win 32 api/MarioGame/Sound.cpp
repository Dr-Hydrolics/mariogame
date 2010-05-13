#include "stdafx.h"
#include "Sound.h"

/*DWORD WINAPI playBGSound(LPVOID lparam)
{
	PlaySound(TEXT("Music\\step.wav"),NULL, SND_FILENAME|SND_LOOP|SND_ASYNC|SND_NOWAIT);
	//PlaySound((LPCTSTR)IDR_WAVE1,NULL, SND_RESOURCE|SND_LOOP|SND_ASYNC|SND_NOWAIT);
	return 1;
}

DWORD WINAPI playSound(LPVOID lparam)
{
	PlaySound(TEXT("Music\\explosion.wav"),NULL, SND_FILENAME|SND_ASYNC|SND_NOWAIT);	
	return 1;
}
*/
int CGameSound::mEnableSound = 0;
int CGameSound::mEnableMusic = 0;

void CALLBACK WaveOutProc(HWAVEOUT hwo, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
	switch(uMsg)
	{
	case WOM_OPEN:
		break;
	case WOM_DONE:
		{
			WAVEHDR *whdr = (WAVEHDR*)dwParam1;
			if(whdr->dwUser)
				waveOutWrite(hwo, whdr, sizeof(WAVEHDR));
			else
			{
				waveOutUnprepareHeader(hwo, whdr, sizeof(WAVEHDR));				
				delete whdr;		
				whdr = NULL;
			}
		}
		break;
	case WOM_CLOSE:
		break;
	}
}


CGameSound::CGameSound(LPSTR szFileName)
{
	lpfile = NULL;
	whdr = NULL;
	mState = 0;
	FILE *f; // Structure to load the file into memory

	// Open and read the wave file
	f = fopen(szFileName, "rb");
	if(!f)
		// Error, file not found.
		return;

	// Determine the file size
	fseek(f, 0, SEEK_END);
	file_size = ftell(f);
	// Rewind the pointer to the begginning so we can read it
	fseek(f, 0, SEEK_SET);

	// Request enough memory to store the entire file
	lpfile = new char [file_size];
	// 'Copy' the file to memory
	fread(lpfile, 1, file_size, f);
	// Close the file, we won't need it anymore
	fclose(f);

	// Fill WAVEFORMATEX with the data from the file
	wfex.wFormatTag         = *((WORD* )(lpfile + OFFSET_FORMATTAG     ));
	wfex.nChannels          = *((WORD* )(lpfile + OFFSET_CHANNELS      ));
	wfex.nSamplesPerSec     = *((DWORD*)(lpfile + OFFSET_SAMPLESPERSEC ));
	wfex.nAvgBytesPerSec    = *((DWORD*)(lpfile + OFFSET_AVGBYTESPERSEC));
	wfex.nBlockAlign        = *((WORD* )(lpfile + OFFSET_BLOCKALIGN    ));
	wfex.wBitsPerSample     = *((WORD* )(lpfile + OFFSET_BITSPERSAMPLE ));

	return;
}


CGameSound::~CGameSound()
{
	waveOutClose(hwo);
	delete [] lpfile;
	lpfile = NULL;
}


WAVEHDR* CGameSound::Play(bool loop=false)
{
	if(mState == 1)
		return NULL;   	
	if(loop == false && mEnableSound == 0)
	{			
		delete [] lpfile;
		lpfile = NULL;
		return NULL;
	}
	if(loop == true && mEnableMusic == 0)
		return NULL;
	if(loop == true && mState == 0)
		mState = 1;
	whdr = new WAVEHDR;
	ZeroMemory((void*)whdr, sizeof(WAVEHDR));

	if(lpfile == NULL)
		return NULL;
	whdr->lpData = lpfile+HEADER_SIZE;
	whdr->dwBufferLength = file_size-HEADER_SIZE;
	whdr->dwUser = (DWORD)loop;

	// Find a waveOut device and open it
	for(UINT devid = 0; devid < waveOutGetNumDevs(); devid++)
	{
		if(devid == waveOutGetNumDevs())
			// Error, no free devices found
			return NULL;
		
		if(waveOutOpen(&hwo, WAVE_MAPPER, &wfex, (DWORD)WaveOutProc, 0, CALLBACK_FUNCTION) == MMSYSERR_NOERROR)
			// Usable device found, stop searching
			break;
	}

	if(waveOutPrepareHeader(hwo, whdr, sizeof(WAVEHDR)) != MMSYSERR_NOERROR)
		return NULL;
	if(waveOutWrite(hwo, whdr, sizeof(WAVEHDR)) != MMSYSERR_NOERROR)
		return NULL;

	// Return the pointer to the WAVEHDR we used here
	return whdr;
}


void CGameSound::Stop(/*WAVEHDR *whdr*/)
{
	if(mState == 1)
		mState = 0;
	if(whdr)
		whdr->dwUser = (DWORD)false;
}


CMidiSound::CMidiSound()
{
	m_uiMIDIPlayerID = 0;
}

CMidiSound::~CMidiSound()
{

}

void CMidiSound::PlayMIDISong(LPTSTR szMIDIFileName, BOOL bRestart)
{
	// See if the MIDI player needs to be opened
	if (m_uiMIDIPlayerID == 0)
	{
		// Open the MIDI player by specifying the device and filename
		MCI_OPEN_PARMS mciOpenParms;
		mciOpenParms.lpstrDeviceType = _T("sequencer");
		mciOpenParms.lpstrElementName = szMIDIFileName;
		if (mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT,
			(DWORD_PTR)&mciOpenParms) == 0)
			// Get the ID for the MIDI player
			m_uiMIDIPlayerID = mciOpenParms.wDeviceID;
		else
			// There was a problem, so just return
			return;
	}

	// Restart the MIDI song, if necessary
	if (bRestart)
	{
		MCI_SEEK_PARMS mciSeekParms;
		if (mciSendCommand(m_uiMIDIPlayerID, MCI_SEEK, MCI_SEEK_TO_START,
			(DWORD_PTR)&mciSeekParms) != 0)
			// There was a problem, so close the MIDI player
			CloseMIDIPlayer();
	}

	// Play the MIDI song
	MCI_PLAY_PARMS mciPlayParms;
	if (mciSendCommand(m_uiMIDIPlayerID, MCI_PLAY, 0,
		(DWORD_PTR)&mciPlayParms) != 0)
		// There was a problem, so close the MIDI player
		CloseMIDIPlayer();
}

void CMidiSound::PauseMIDISong()
{
	// Pause the currently playing song, if possible
	if (m_uiMIDIPlayerID != 0)
		mciSendCommand(m_uiMIDIPlayerID, MCI_PAUSE, 0, NULL);
}

void CMidiSound::CloseMIDIPlayer()
{
	// Close the MIDI player, if possible
	if (m_uiMIDIPlayerID != 0)
	{
		mciSendCommand(m_uiMIDIPlayerID, MCI_CLOSE, 0, NULL);
		m_uiMIDIPlayerID = 0;
	}
}

