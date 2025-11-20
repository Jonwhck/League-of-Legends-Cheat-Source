#pragma once

#include "CObject.h"

#include <vector>
#include <map>
#include <Windows.h>

class CycleManager {
	static std::vector<CObject*> m_pObjects;

public: 
	static std::vector<CObject*> HeroList;
	static std::vector<CObject*> MinionList;
	static std::vector<CObject*> TurretList;
	static std::vector<CObject*> ObjectList;
public:
	static void NewCycle();
	static std::vector<CObject*> GetObjects();
	static std::vector<CObject*> GetHeroList();
	static std::vector<CObject*> GetMinionList();
	static std::vector<CObject*> GetTurretList();
	static std::vector<CObject*> GetObjectList();

};