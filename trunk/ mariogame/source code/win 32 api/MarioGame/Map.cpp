#include "StdAfx.h"
#include "Map.h"
#include "GameObject.h"
#include "atlimage.h"

CMap::CMap()
{
	mMapRow = 20;
	mMapCol = 300;
	pMapData = new char*[mMapRow];
	for(int i=0 ; i<mMapRow ; i++)
		pMapData[i] = new char[mMapCol];
	mTileWidth = 24;
	mTileHeight = 24;
	bmTiles = NULL;
}

CMap::CMap(LPCTSTR bmTileName)
{
	mMapRow = 20;
	mMapCol = 300;
	pMapData = new char*[mMapRow];
	for(int i=0 ; i<mMapRow ; i++)
		pMapData[i] = new char[mMapCol];
	mTileWidth = 24;
	mTileHeight = 24;
	bmTiles = NULL;
	Init(bmTileName);
}

CMap::~CMap()
{
	if(bmTiles)
	{
		delete bmTiles;
		bmTiles = NULL;
	}
	if(pMapData)
	{
		for(int i=0 ; i<mMapRow ; i++)
		{
			delete []pMapData[i];
			pMapData[i] = NULL;
		}
		delete []pMapData;
		pMapData = NULL;
	}	
}

int CMap::Init(LPCTSTR bmTileName)
{
	if(!bmTiles)
	{
		bmTiles = new MyBitmap(bmTileName);
		return 1;
	}
	return 0;
}

int CMap::LoadMapData(LPCTSTR filename)
{
	if(!pMapData)
		return 0;
	FILE* reader = _wfopen(filename,_T("rb"));
	if(!reader)
		return 0;
	int i=0,j=0;
	const int MAX_BUFFER_SIZE = 300;
	int nByteRead=0;
	char buff[MAX_BUFFER_SIZE];
	i=0;
	while(1)
	{
			nByteRead = fread(buff,1,MAX_BUFFER_SIZE,reader);
			fseek(reader,2,SEEK_CUR);
			if(nByteRead<=0)
				break;
			for(int k=0 ; k<nByteRead ; k++)
			{
				pMapData[i/mMapCol][i%mMapCol] = buff[k] - 'A';			
				i++;				
			}		
	}
	fclose(reader);
	return 1;
}

int CMap::LoadBitmapMap(MyBitmap* &bmMap)
{
	if(!bmTiles)
		return 0;
	int i=0,j=0;	
	HDC desktopDC = GetDC(GetDesktopWindow());
	HDC dcMap = CreateCompatibleDC(desktopDC);
	HBITMAP hBM = CreateCompatibleBitmap(desktopDC,mMapCol*mTileWidth,mMapRow*mTileHeight);
	HBITMAP dcMapOld = (HBITMAP)SelectObject(dcMap, hBM);
	HDC dcMapTiles = CreateCompatibleDC(desktopDC);
	HBITMAP dcMapTilesOld = (HBITMAP)SelectObject(dcMapTiles, bmTiles->hBitmap);	
	for(i=0 ; i<mMapRow ; i++)
		for(j=0 ; j<mMapCol ; j++)
		{		
			//MyBitmap::DrawTransparent(dcMap,j*iTileWidth,i*iTileHeight,iTileWidth,iTileHeight,
			//	dcMapTiles,6*iTileWidth,0,RGB(255,255,255));	
			if(pMapData[i][j]>=0 && pMapData[i][j]<=30 && pMapData[i][j] != ICOIN && pMapData[i][j] != ITRUNK && pMapData[i][j] != IBRICK)
				MyBitmap::DrawTransparent(dcMap,j*mTileWidth,i*mTileHeight,mTileWidth,mTileHeight,
				dcMapTiles,pMapData[i][j]*mTileWidth,0,RGB(255,0,255));			
		}
	if(!bmMap)
		bmMap = new MyBitmap();
	/*CImage img;
	img.Attach(hBM);	
	img.Save(_T("map.jpg"));
	img.Detach();	*/
	bmMap->hBitmap = hBM;		
	SelectObject(dcMap,dcMapOld);
	SelectObject(dcMapTiles,dcMapTilesOld);
	DeleteObject(dcMap);
	DeleteObject(dcMapTiles);
	ReleaseDC(GetDesktopWindow(),desktopDC);	
	return 1;
}

POINT CMap::GetMapSize()
{
	POINT size;
	size.x = mMapCol*mTileWidth;
	size.y = mMapRow*mTileHeight;
	return size;
}
int CMap::GetObject(int xPos, int yPos)
{
	int row = yPos/mTileHeight;
	int col = xPos/mTileWidth;
	if(row<0 || col<0)
		return 1;
	if(row >= mMapRow || col >= mMapCol)
		return -1;
	if (pMapData[row][col]>0 && pMapData[row][col]<7)
		return 1;
	return 0;
}
char CMap::GetData(int iRow, int iCol)
{
	return pMapData[iRow][iCol];
}
int CMap::GetTileIndex(int iRow, int iCol)
{
	if(iRow >= mMapRow  || iCol >= mMapCol)
		return -1;
	if(iRow < 0 || iCol < 0)
		return 1;
	return (int)pMapData[iRow][iCol];
}
int CMap::GetTileIndexAt(int xPos, int yPos)
{
	int row = yPos/mTileHeight;
	int col = xPos/mTileWidth;	
	return GetTileIndex(row, col);
}

POINT CMap::GetPos(int iRow, int iCol)
{
	POINT pos;
	pos.x = iCol*mTileWidth;
	pos.y = iRow*mTileHeight;
	return pos;
}

POINT CMap::GetPos(POINT idx)
{
	POINT pos;
	pos.x = idx.y*mTileWidth;
	pos.y = idx.x*mTileHeight;
	return pos;
}
POINT CMap::GetIndex(int xPos, int yPos)
{
	POINT idx;
	idx.x = yPos/mTileHeight;
	idx.y = xPos/mTileWidth;	
	return idx;
}