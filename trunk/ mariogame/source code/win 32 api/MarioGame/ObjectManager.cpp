#include "StdAfx.h"
#include "Character.h"
#include "Monster.h"
#include "BonnusObject.h"

int CObjectManager::mBlockObjIndex[] = {0, 1, 2, 3, 4, 5, 6, 10, 15, 16, 17, 24, 25, 26, 27};
int CObjectManager::mNumBlockObj = 15;

int CObjectManager::mInTrunkIdx[] = {ICOIN, IMUSHROOM, IFLOWER, ISTAR};
int CObjectManager::mNumInTrunkIdx = 4;

CObjectManager::CObjectManager()
{
	mMario = NULL;
	hDLL = NULL;
}

CObjectManager::~CObjectManager()
{
	if(hDLL != NULL)
		FreeLibrary(hDLL);
}
POINT CObjectManager::GetMarioPos()
{
	if(mMario != NULL)
		return mMario->GetPos();
	POINT pos;
	pos.x = 0;
	pos.y = 0;
	return pos;
}
// 0: khong bi can, 1: bi can, -1: roi xuong vuc sau
int CObjectManager::IsBlockedAt(int xPos, int yPos)
{
	int tileIndex = mGameMap->GetTileIndexAt(xPos, yPos);	
	if(tileIndex == -5)
		return 0;
	if(tileIndex == -1)
		return -1;
	return IsBlockedTile(tileIndex);
}
int CObjectManager::IsBlockedTile(int tileIndex)
{	
	if(tileIndex == -1)
		return -1;
	if(tileIndex+17 >= 0 && tileIndex+17<mNumInTrunkIdx)
		return 1;
	for(int i=0 ; i<mNumBlockObj ; i++)
		if(tileIndex == mBlockObjIndex[i])
			return 1;	
	return 0;	
}

int CObjectManager::InitFromFile(int level)
{
	LPTSTR initFile = new TCHAR[256];
	wsprintf(initFile,_T("Map\\level%d.init"), level);
	ifstream inFile(initFile);	
	if(inFile.is_open() == 0)
		return -1;
	int x, y, w, h, type, dir;
	float tocdo;
	TCHAR *bitmap = NULL;
	string bm;
	inFile>>bm;
	inFile>>x;
	inFile>>y;
	inFile>>w;
	inFile>>h;	
	inFile>>bm;		
	bitmap = stringtowchar(bm);	
	vector<POINT> reBornPos;
	int n = 0;
	inFile>>n;
	if(n>0)
	{
		reBornPos.clear();		
		for(int i=0 ; i<n ; i++)
		{
			POINT temp;
			inFile>>temp.x;
			inFile>>temp.y;
			reBornPos.push_back(temp);
		}
	}
	if(mMario == NULL)
		mMario = new CCharacter(x, y, w, h, (LPCTSTR)bitmap, reBornPos);
	else
		mMario->Init(x, y, w, h, (LPCTSTR)bitmap, reBornPos);
	IMonster* mobj = NULL;
	while(!inFile.eof())
	{
		inFile>>type;
		inFile>>x;
		inFile>>y;
		inFile>>w;
		inFile>>h;	 		
		inFile>>bm;
		inFile>>dir;
		inFile>>tocdo;						
		bitmap = stringtowchar(bm);			
		switch(type)
		{
		case 1:
			mobj = new CMonster1(x, y, w, h, (LPCTSTR)bitmap, dir, tocdo);
			break;
		case 2:
			mobj = new CMonster2(x, y, w, h, (LPCTSTR)bitmap, dir, tocdo);
			break;
		case 3:
			mobj = new CMonster3(x, y, w, h, (LPCTSTR)bitmap, dir, tocdo);
			break;
		case 4:
			mobj = new CMonster4(x, y, w, h, (LPCTSTR)bitmap, dir, tocdo);
			break;
		case 5:
			mobj = new CMonster5(x, y, w, h, (LPCTSTR)bitmap, dir, tocdo);
			break;
		case 6:
			mobj = new CMonster6(x, y, w, h, (LPCTSTR)bitmap, dir, tocdo);
			break;
		case 7:
			mobj = new CMonster7(x, y, w, h, (LPCTSTR)bitmap, dir, tocdo);
			break;
		case 8:
			mobj = new CMonster8(x, y, w, h, (LPCTSTR)bitmap, dir, tocdo);
			break;
		case 21:
			mobj = new CMonsterB1(x, y, w, h, (LPCTSTR)bitmap, dir, tocdo);
			break;
		case 22:
			mobj = new CMonsterB2(x, y, w, h, (LPCTSTR)bitmap, dir, tocdo);
			break;
		case 23:
			mobj = new CMonsterB3(x, y, w, h, (LPCTSTR)bitmap, dir, tocdo);
			break;
		}
		pMonster.push_back(mobj);
	}
	inFile.close();
	return 1;
}
int CObjectManager::InitPlugin(int level)
{
	LPTSTR initFile = new TCHAR[256];
	wsprintf(initFile,_T("Plugin\\level%d.plug"), level);
	ifstream inFile(initFile);	
	if(inFile.is_open() == 0)
		return -1;
	TCHAR *wTemp = NULL;
	char *cTemp = NULL;
	string sTemp;	
	inFile>>sTemp;		
	string temp("Plugin\\");
	sTemp = temp + sTemp;
	wTemp = stringtowchar(sTemp);	
	hDLL = ::LoadLibrary(wTemp);	
	if(hDLL != NULL)
	{
		int x, y, w, h, type, dir;
		float tocdo;
		while(inFile.eof() == false)
		{
			inFile>>sTemp;	
			if(inFile.eof() == true)
				return 1;
			cTemp = stringtochar(sTemp);	
			inFile>>x;
			inFile>>y;
			inFile>>w;
			inFile>>h;
			inFile>>sTemp;
			wTemp = stringtowchar(sTemp);
			inFile>>dir;
			inFile>>tocdo;
			CreateMonster pFunc = (CreateMonster)GetProcAddress(hDLL, (LPCSTR)cTemp);
			if(pFunc != NULL)
			{			  				
				IMonster* mobj = pFunc(x, y, w, h, wTemp, dir, tocdo);
				if(mobj != NULL)
					pMonster.push_back(mobj);
			}	
		}	  		
	}
	inFile.close();
	return 1;
}
int CObjectManager::Init(int level, CMap* map)
{	
	mGameMap = map;
	InitFromFile(level);	
	InitPlugin(level);
	IMonster* mobj = NULL;
		
	CGameObject* obj = NULL;
	// Tao cac dong tien va cac vat thuong
	int i=0, j=0;
	POINT pos;	
	for(i=0 ; i<map->MapRow() ; i++)
	{
		for(j=0 ; j<map->MapCol() ; j++)
		{
			if(map->GetTileIndex(i,j) == ICOIN)
			{
				pos = map->GetPos(i, j);
				obj = new CCoin(pos.x, pos.y, map->TileWidth(), map->TileHeight(), _T("coin.bmp"));
				pBonnus.push_back(obj);
			}
			if(map->GetTileIndex(i,j) == IBRICK)
			{
				pos = map->GetPos(i, j);
				obj = new CNoAnimateObject(pos.x, pos.y, map->TileWidth(), map->TileHeight(), _T("maptiles.bmp"), IBRICK, TBRICK);
				pStaticObjects.push_back(obj);
			}
			if(map->GetTileIndex(i,j)+17>=0 && map->GetTileIndex(i,j)+17<mNumInTrunkIdx)
			{
				pos = map->GetPos(i, j);
				obj = new CTrunk(pos.x, pos.y, map->TileWidth(), map->TileHeight(), _T("maptiles.bmp"), mInTrunkIdx[map->GetTileIndex(i,j)+17]);
				pStaticObjects.push_back(obj);
			}
		}
	}

	return 1;
}
void CObjectManager::Release()
{
	if(hDLL != NULL)
		FreeLibrary(hDLL);
	pStaticObjects.clear();
	pMarioClubs.clear();
	pMonster.clear();
	pBonnus.clear();		
	return;
}

int CObjectManager::ProcessConllision()
{
	if(mMario == NULL)
		return 0;
	// Xu ly dung do giua Mario va cac doi tuong trong game
	for(int i=0 ; i<GetMonsterCount() ; i++)
	{
		int coll = CheckConllision(mMario, pMonster[i]);
		if(coll == 1 && mMario->JumpDirect() == 0 && !mMario->IsDead() && (pMonster[i]->Type() == TMONSTER || pMonster[i]->Type() == TBOSS))
		{
			mMario->StopJump();
			mMario->Jump(10);
			pMonster[i]->BeHurt();
			return 1;	
		}
		if(coll >= 3 && coll<=5 )
		{
			mMario->BeHurt();
			return 1;
		}
	}
	for(int i=0 ; i<GetStaticObjectCount() ; i++)
	{
		int coll = CheckConllision(mMario, pStaticObjects[i]);
		if(coll == 2 && !mMario->IsDead() && pStaticObjects[i]->Type() == TBRICK)
		{
			mMario->Fall();
			mGameMap->SetValueAt(pStaticObjects[i]->mXPos, pStaticObjects[i]->mYPos, -5);
			RemoveStaticObject(i);
			i--;	
			return 1;
		}		
		if(coll == 2 && !mMario->IsDead() && pStaticObjects[i]->Type() == TTRUNK)
		{
			mMario->Fall();
			((CTrunk*)pStaticObjects[i])->Open(this);
			return 1;
		}
	}
	
	for(int i=0 ; i<GetBonnusCount() ; i++)
	{
		int coll = CheckConllision(mMario, pBonnus[i]);
		if(coll >= 1 && pBonnus[i]->Type() == TCOIN)
		{
			RemoveBonnus(i);
			mMario->GetCoin();
			i--;			
			return 1;
		}
		if(coll >= 1 && pBonnus[i]->Type() == TMUSHROOM)
		{
			mMario->GetMushroom();
			RemoveBonnus(i);
			i--;			
			return 1;
		}
		if(coll >= 1 && pBonnus[i]->Type() == TFLOWER)
		{
			mMario->GetFlower();
			RemoveBonnus(i);
			i--;			
			return 1;
		}
		if(coll >= 1 && pBonnus[i]->Type() == TSTAR)
		{
			mMario->GetStar();
			
			RemoveBonnus(i);
			i--;			
			return 1;
		}
	}	
	// Xu ly dong do giua quai vat va dan cua mario
	for(int i=0 ; i<GetMarioClubsCount() ; i++)
	{
		for(int j=0 ; j<GetMonsterCount() ; j++)
		{
			if(pMonster[j]->Type() == TMONSTER || pMonster[j]->Type() == TBOSS) 
			{
				int coll = CheckConllision(pMarioClubs[i], pMonster[j]);
				if(coll >= 3 && coll<=5 )
				{
					pMonster[j]->BeHurt();
					RemoveMarioClub(i);
					i--;
					return 1;
				}
			}
		}
	}
	return 1;
}
int CObjectManager::Animate(CScreen* scr)
{
	if(mMario != NULL)
	{
		int nodie = mMario->DoAction(scr, this);
		if(nodie == -1)
		{
			delete mMario;
			mMario = NULL;
			return -1;
		}
		if(nodie == 0)
		{
			mMario->GoToOldPos();
			scr->SetViewPortX(mMario->GetPos().x);
		}
	}
	ProcessConllision();
	int i=0;
	for(i=0 ; i<GetMarioClubsCount() ; i++)
	{
		if(pMarioClubs[i] != NULL)
		{
			int res = ((CAnimateObject*)pMarioClubs[i])->DoAction(this);
			if(res == -1)
			{
				RemoveMarioClub(i);
					i--;
			}
		}
	}
	int result = 0;
	for(i=0 ; i<GetMonsterCount() ; i++)
	{
		if(pMonster[i] != NULL)
		{
			int res = ((IMonster*)pMonster[i])->DoAction(this);
			if(res == 2 && pMonster[i]->Type() == TBOSS)
			{
				result = 2;
			}
			if(res == -1)
			{			
				if(pMonster[i]->Type() == TBOSS)		
				{
					RemoveMonster(i);
					i--;		
					return 1;
				}
				else
				{
					RemoveMonster(i);
					i--;
				}
				
			}
		}
	}
	for(i=0 ; i<GetBonnusCount() ; i++)
	{
		if((pBonnus[i] != NULL) && (pBonnus[i]->Family() == FANIMATEMOVELESS || pBonnus[i]->Family() == FANIMATEMOVABLE || pBonnus[i]->Family() == FNOANIMATEMOVABLE))
		{
			int res = 
			((CAnimateObject*)pBonnus[i])->DoAction(this);
			if(res == -1)
			{
				RemoveBonnus(i);
					i--;
			}
		}
	}
	return result;
}

int CObjectManager::Present(CScreen* scr)
{	
	int i=0;
	int objCount = GetStaticObjectCount();
	for(i=0 ; i<objCount ; i++)
	{
		pStaticObjects[i]->Present(scr->GetMemDC(), scr->ViewPort());
	}
	objCount = GetBonnusCount();
	for(i=0 ; i<objCount ; i++)
	{
		pBonnus[i]->Present(scr->GetMemDC(), scr->ViewPort());
	}
	objCount = GetMarioClubsCount();
	for(i=0 ; i<objCount ; i++)
	{
		pMarioClubs[i]->Present(scr->GetMemDC(), scr->ViewPort());
	}
	objCount = GetMonsterCount();
	for(i=0 ; i<objCount ; i++)
	{
		pMonster[i]->Present(scr->GetMemDC(), scr->ViewPort());
	}	
	//mons->Present(scr->GetMemDC(), scr->ViewPort());
	if(mMario != NULL)
		mMario->Present(scr->GetMemDC(), scr->ViewPort());
	return 1;
}


int CObjectManager::CheckConllision(CGameObject* obj1, IMonster* obj2)
{
	RECT rect1, rect2;
	rect1.left = obj1->mXPos;
	rect1.top = obj1->mYPos;
	rect1.right = obj1->mXPos + obj1->mWidth;
	rect1.bottom = obj1->mYPos + obj1->mHeight;

	rect2.left = obj2->mXPos;
	rect2.top = obj2->mYPos;
	rect2.right = obj2->mXPos + obj2->mWidth;
	rect2.bottom = obj2->mYPos + obj2->mHeight;
	int rectX1[] = {rect1.left, rect1.right, rect1.right, rect1.left};
	int rectY1[] = {rect1.top, rect1.top, rect1.bottom, rect1.bottom};

	int midY1 = (rect1.top + rect1.bottom)/2;
	int midX1 = (rect1.left + rect1.right)/2;
	int thirdX1 = (rect1.left + rect1.right)/3;
	int midY2 = (rect2.top + rect2.bottom)/2;
	int midX2 = (rect2.left + rect2.right)/2;
	int res = 0;
	if(midX1>=rect2.left && midX1<=rect2.right && rect1.bottom>=rect2.top && rect1.bottom<=midY2)
	{
		return 1;// Rect1 cham Rect2 tu phia tren
	}
	if(midX1>=rect2.left && midX1<=rect2.right && rect1.top>=midY2 && rect1.top<=rect2.bottom)
	{
		return 2;// Rect1 cham Rect2 tu phia duoi
	}
	if(rect2.left>2*thirdX1 && rect2.left<rect1.right && rect1.bottom>rect2.top && rect1.top<rect2.bottom)
	{
		return 3; // Rect1 cham Rect2 tu ben trai
	}	
	if(rect2.right>rect1.left && rect2.right<thirdX1 && rect1.bottom>rect2.top && rect1.top<rect2.bottom)
	{
		return 4; // Rect1 cham Rect2 tu ben phai
	}
	if(midX1>=rect2.left && midX1<=rect2.right && rect1.bottom>midY2 && rect1.top<midY2)
	{
		return 5; // Rect1 giao voi Rect2
	}	
	return 0;	
}
int CObjectManager::CheckConllision(CGameObject* obj1, CGameObject* obj2)
{
	RECT rect1, rect2;
	rect1.left = obj1->mXPos;
	rect1.top = obj1->mYPos;
	rect1.right = obj1->mXPos + obj1->mWidth;
	rect1.bottom = obj1->mYPos + obj1->mHeight;

	rect2.left = obj2->mXPos;
	rect2.top = obj2->mYPos;
	rect2.right = obj2->mXPos + obj2->mWidth;
	rect2.bottom = obj2->mYPos + obj2->mHeight;
	int rectX1[] = {rect1.left, rect1.right, rect1.right, rect1.left};
	int rectY1[] = {rect1.top, rect1.top, rect1.bottom, rect1.bottom};

	int midY1 = (rect1.top + rect1.bottom)/2;
	int midX1 = (rect1.left + rect1.right)/2;
	int thirdX1 = (rect1.left + rect1.right)/3;
	int midY2 = (rect2.top + rect2.bottom)/2;
	int midX2 = (rect2.left + rect2.right)/2;
	int res = 0;
	if(midX1>=rect2.left && midX1<=rect2.right && rect1.bottom>=rect2.top && rect1.bottom<=midY2)
	{
		return 1;// Rect1 cham Rect2 tu phia tren
	}
	if(midX1>=rect2.left && midX1<=rect2.right && rect1.top>=midY2 && rect1.top<=rect2.bottom)
	{
		return 2;// Rect1 cham Rect2 tu phia duoi
	}
	if(rect2.left>2*thirdX1 && rect2.left<rect1.right && rect1.bottom>rect2.top && rect1.top<rect2.bottom)
	{
		return 3; // Rect1 cham Rect2 tu ben trai
	}	
	if(rect2.right>rect1.left && rect2.right<thirdX1 && rect1.bottom>rect2.top && rect1.top<rect2.bottom)
	{
		return 4; // Rect1 cham Rect2 tu ben phai
	}
	if(midX1>=rect2.left && midX1<=rect2.right && rect1.bottom>midY2 && rect1.top<midY2)
	{
		return 5; // Rect1 giao voi Rect2
	}	
	return 0;	
}