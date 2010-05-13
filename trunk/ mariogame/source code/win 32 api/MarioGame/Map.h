#pragma once
//#include "MyBitmap.h"


class CMap
{
	int mMapRow;
	int	mMapCol;
	
	char** pMapData;
	int mTileWidth;
	int mTileHeight;
	
	MyBitmap* bmTiles;	
public:
	CMap();
	CMap(LPCTSTR bmTileName);
	~CMap();
	// Properties
	int TileWidth() const { return mTileWidth; }
	void TileWidth(int val) { mTileWidth = val; }
	int TileHeight() const { return mTileHeight; }
	void TileHeight(int val) { mTileHeight = val; }
	int MapRow() const { return mMapRow; }
	void MapRow(int val) { mMapRow = val; }
	int MapCol() const { return mMapCol; }
	void MapCol(int val) { mMapCol = val; }
	void SetValueAt(int XPos, int YPos, int val)
	{
		int iCol = XPos/mTileWidth;
		int iRow = YPos/mTileHeight;
		if(iRow < 0 || iRow >= mMapRow || iCol < 0 || iCol >= mMapCol)
			return;
		pMapData[iRow][iCol] = val;
	}
	char GetData(int iRow, int iCol);
	// End Properties

	// Methods
	int Init(LPCTSTR bmTileName);
	int LoadMapData(LPCTSTR filename);
	int LoadBitmapMap(MyBitmap* &bmMap);
	POINT GetMapSize();
	//void Redraw(MyBitmap* &bmMap, int row, int col, int iTile);
	int GetObject (int xPos, int yPos);
	int GetTileIndex(int iRow, int iCol);
	int GetTileIndexAt(int xPos, int yPos);
	POINT GetPos(int iRow, int iCol);
	POINT GetPos(POINT idx);
	POINT GetIndex(int xPos, int yPos);

	// End Methods
};