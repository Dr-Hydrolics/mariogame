#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "GameObject.h"
#include "Screen.h"
#include "Sound.h"
#include "vector"
//#include "IMonster.h"
//#include "IObjectManager.h"

using namespace std;

typedef IMonster* (*CreateMonster)(int, int, int, int, LPCTSTR, int, float);

class CCharacter;
class CObjectManager : public IObjectManager
{
protected:	
	static int mBlockObjIndex[]; // Vị trí của vật cản trong maptiles
	static int mNumBlockObj;

	static int mInTrunkIdx[]; // Vị trí của vật cản trong maptiles
	static int mNumInTrunkIdx;
	HMODULE hDLL;
	vector<CGameObject*> pStaticObjects;
	vector<CGameObject*> pMarioClubs;
	vector<IMonster*> pMonster;
	vector<CGameObject*> pBonnus;
	//IMonster* mons;
	CCharacter* mMario;	
	CMap* mGameMap;
	CGameSound* eventSound;	
		
	int CheckConllision(CGameObject* obj1, CGameObject* obj2); // Kiem tra 2 doi tuong co dung do voi nhau khong
	int CheckConllision(CGameObject* obj1, IMonster* obj2);
public:

	CObjectManager();
	~CObjectManager();
	
	POINT GetMarioPos();
	CMap* GameMap() const { return mGameMap; }
	void GameMap(CMap* val) { mGameMap = val; }
	int Init(int iLevel, CMap* map);
	int InitFromFile(int level);
	int InitPlugin(int level);
	int IsBlockedTile(int tileIndex);
	// 0: khong bi can, 1: bi can, 2: roi xuong vuc sau
	int IsBlockedAt(int xPos, int yPos);
	int ProcessConllision(); // Kiem tra su dung do giua cac doi tuong trong game
	int Animate(CScreen* scr);	
	void Release();
	int Present(CScreen* scr); // Hien thi tat ca object ra man hinh

	// Methods
	int GetMapTileWidth()
	{
		return mGameMap->TileWidth();
	}
	int GetMapTileHeight()
	{
		return mGameMap->TileHeight();
	}		
	int GetObjectCount()
	{
		return pBonnus.size() + pMarioClubs.size() + pMonster.size() + pStaticObjects.size();
	}
	int GetStaticObjectCount()
	{
		return pStaticObjects.size();
	}	
	int GetBonnusCount()
	{
		return pBonnus.size();
	}
	int GetMarioClubsCount()
	{
		return pMarioClubs.size();
	}

	int GetMonsterCount()
	{
		return pMonster.size();
	}
	void AddStaticObject(CGameObject* obj) 
	{
		pStaticObjects.push_back(obj);
	}
	void AddBonnus(CGameObject* obj) 
	{
		pBonnus.push_back(obj);
	}
	void AddMonster(IMonster* obj) 
	{
		pMonster.push_back(obj);
	}

	void AddMarioClub(CGameObject* obj) 
	{
		pMarioClubs.push_back(obj);
	}
	int RemoveStaticObject(int i)
	{
		CGameObject* pObj = pStaticObjects[i];
		pStaticObjects.erase(pStaticObjects.begin()+i);					
		delete pObj;
		pObj = NULL;
		return pStaticObjects.size();
	}
	int RemoveBonnus(int i)
	{
		CGameObject* pObj = pBonnus[i];
		pBonnus.erase(pBonnus.begin()+i);					
		delete pObj;
		pObj = NULL;
		return pBonnus.size();
	}
	int RemoveMonster(int i)
	{
		IMonster* pObj = pMonster[i];
		pMonster.erase(pMonster.begin()+i);					
		delete pObj;
		pObj = NULL;
		return pMonster.size();
	}
	int RemoveMarioClub(int i)
	{
		CGameObject* pObj = pMarioClubs[i];
		pMarioClubs.erase(pMarioClubs.begin()+i);					
		delete pObj;
		pObj = NULL;
		return pMarioClubs.size();
	}
};

#endif // _DEBUG