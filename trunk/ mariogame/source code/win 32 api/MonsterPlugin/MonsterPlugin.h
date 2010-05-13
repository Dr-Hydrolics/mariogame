// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MONSTERPLUGIN_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MONSTERPLUGIN_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef MONSTERPLUGIN_EXPORTS
#define MONSTERPLUGIN_API __declspec(dllexport)
#else
#define MONSTERPLUGIN_API __declspec(dllimport)
#endif

// This class is exported from the MonsterPlugin.dll
class MONSTERPLUGIN_API CMonsterPlugin : public IMonster {
protected:
	int mXpos1;
	int mYpos1;
	float mSpeed;
	int oldmove;
	int mStart;
public:
	CMonsterPlugin(int x, int y, int w, int h, LPCTSTR bmSrpiteName,int fd,float sp);
	int DoAction(/*CScreen* scr, */IObjectManager* objMan);
	// TODO: add your methods here.
};

MONSTERPLUGIN_API IMonster* CreateMonsterPlugin(int x, int y, int w, int h, LPCTSTR bmSpriteName, int dir, float sp);

extern MONSTERPLUGIN_API int nMonsterPlugin;

MONSTERPLUGIN_API int fnMonsterPlugin(void);

