#pragma once
//#include "Sprite.h"



enum ObjectFamily {FANIMATEMOVABLE = 0, FANIMATEMOVELESS = 1, FNOANIMATEMOVABLE = 2, FNOANIMATEMOVELESS = 3};
enum ObjectType {TCHARACTER = 0, TMONSTER = 1, TCOIN = 2, TBRICK = 3, TMONSTERCLUB = 4, TMARIOCLUB = 9,TTRUNK = 5, TFLOWER = 6, TSTAR = 7, TMUSHROOM = 8, TBOSS = 10};
enum ObjectTileIndex {ICOIN = 7, IBRICK = 1, ITRUNK = 10, IFLOWER = 11, ISTAR = 12, IMUSHROOM = 0};

class CObjectManager;
class CGameObject
{
protected:
	enum ObjectDirection {DIRLEFT = 0, DIRRIGHT = 1};
	// Goc tren trai man hinh co toa do: (0, 0)
	int mXPos; // Vi tri theo chieu ngang cua doi tuong tren ban do
	int mYPos;	// Vi tri theo chieu doc cua doi tuong tren ban do
	int mWidth; // Chieu rong cua doi tuong
	int mHeight; // Chieu dai cua doi tuong
	int mType;	// Loai cua doi tuong
	int mFamily;
	int mDirection; // Huong cua doi tuong	
public:
	friend class CObjectManager;
	CGameObject();
	virtual ~CGameObject();	
	int Family() const { return mFamily; }
	void Family(int val) { mFamily = val; }
	int Type() const { return mType; }
	void Type(int val) { mType = val; }
	int Direction() const { return mDirection; }
	void Direction(int val) { mDirection = val; }
	POINT GetPos();	
	virtual void Present(HDC hDC, RECT view);	
};