#include "CycleManager.h"
#include "memory.h"
#include "CObject.h"
#include <vector>
#include <map>
#include "Engine.h"

std::vector<CObject*> CycleManager::m_pObjects = *new std::vector<CObject*>();
std::vector<CObject*> CycleManager::HeroList = *new std::vector<CObject*>();
std::vector<CObject*> CycleManager::MinionList = *new std::vector<CObject*>();
std::vector<CObject*> CycleManager::TurretList = *new std::vector<CObject*>();
std::vector<CObject*> CycleManager::ObjectList = *new std::vector<CObject*>();

void CycleManager::NewCycle() {
	m_pObjects.clear();

	CObject object;
	CObject* pObject = object.GetFirstObject();

	while (pObject)
	{
		m_pObjects.push_back(pObject);
		pObject = object.GetNextObject(pObject);
	}
}

std::vector<CObject*> CycleManager::GetObjects() {
	return m_pObjects;
}

//int heroList_pretPtr = Utils.ReadInt(Offsets.Base + Offsets.StaticLists.OHeroList);
//
//int heroList = Utils.ReadInt(heroList_pretPtr + 0x4);
//
//int heroList_size = Utils.ReadInt(heroList_pretPtr + 0x8);
//for (int i = 0; i < heroList_size; i++)
//{
//	int obj = Utils.ReadInt(heroList + i * 0x4);
//
//	if (obj.IsEnemy())
//		enemyList.Add(obj);
//	else if (obj != Engine.GetLocalObject())
//		allyList.Add(obj);
//}

std::vector<CObject*> CycleManager::GetHeroList() {

	//std::vector<CObject*> globalEnt = GetObjects();
	//
	//std::vector<CObject*> tempList;
	//for (CObject* i : globalEnt) {
	//	if (i->IsHero() && i->IsEnemyTo(me) && i->IsAlive()) {
	//		tempList.push_back(i);
	//	}
	//}
	//return tempList;

	std::vector<CObject*> tempList;
	DWORD heroList_prePtr = *(DWORD*)(baseAddr + oHeroList);
	DWORD heroList = *(DWORD*)(heroList_prePtr + 0x4);
	DWORD heroList_size = *(DWORD*)(heroList_prePtr + 0x8);
	for (int i = 0; i < heroList_size; i++) {
		CObject* obj = *(CObject**)(heroList + i * 0x4);
		//CObject* obj_t = &obj;
		if (obj->IsEnemyTo(me)) {
			tempList.push_back(obj);
		}
	}
	CycleManager::HeroList = tempList;
	return tempList;
}

std::vector<CObject*> CycleManager::GetTurretList() {

	//std::vector<CObject*> globalEnt = GetObjects();
	//
	//std::vector<CObject*> tempList;
	//for (CObject* i : globalEnt) {
	//	if (i->IsHero() && i->IsEnemyTo(me) && i->IsAlive()) {
	//		tempList.push_back(i);
	//	}
	//}
	//return tempList;

	std::vector<CObject*> tempList;
	DWORD turretList_prePtr = *(DWORD*)(baseAddr + oTurretList);
	DWORD turretList = *(DWORD*)(turretList_prePtr + 0x4);
	DWORD turretList_size = *(DWORD*)(turretList_prePtr + 0x8);
	for (int i = 0; i < turretList_size; i++) {
		CObject* obj = *(CObject**)(turretList + i * 0x4);
		//CObject* obj_t = &obj;
		if (obj->IsEnemyTo(me)) {
			tempList.push_back(obj);
		}
	}
	CycleManager::TurretList = tempList;
	return tempList;
}

std::vector<CObject*> CycleManager::GetObjectList() {
	std::vector<CObject*> tempList;
	DWORD objectList_prePtr = *(DWORD*)(baseAddr + oObjManager);
	DWORD objectList = *(DWORD*)(objectList_prePtr + 0x14);
	DWORD objectList_size = *(DWORD*)(objectList_prePtr + 0x8);
	for (int i = 0; i < objectList_size; i++) {
		CObject* obj = *(CObject**)(objectList + i * 0x4);
		//CObject* obj_t = &obj;
		if (obj->IsEnemyTo(me)) {
			tempList.push_back(obj);
		}
	}
	CycleManager::ObjectList = tempList;
	return tempList;
}

std::vector<CObject*> CycleManager::GetMinionList() {
	std::vector<CObject*> tempList;
	DWORD minionList_prePtr = *(DWORD*)(baseAddr + oMinionList);
	DWORD minionList = *(DWORD*)(minionList_prePtr + 0x4);
	DWORD minionList_size = *(DWORD*)(minionList_prePtr + 0x8);
	for (int i = 0; i < minionList_size; i++) {
		CObject* obj = *(CObject**)(minionList + i * 0x4);
		//CObject* obj_t = &obj;
		if (obj->IsEnemyTo(me)) {
			tempList.push_back(obj);
		}
	}
	CycleManager::MinionList = tempList;
	return tempList;
}
