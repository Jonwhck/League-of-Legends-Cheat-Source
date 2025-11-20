#pragma once

#include "CObject.h"
#include "Input.h"
//#include "ESpellSlot.h"
#include <chrono>

class COrbWalker {
private:
	int m_nLastAttackCmdTick;
	int m_nLastMoveCmdTick;
	std::chrono::milliseconds m_lastMoveClickTime; //std::chrono::milliseconds
	float m_lastAttackClickTime;
	bool lastHitOnly;
	bool autoMove;
	bool preferHarassOverFarm;
	bool useAutokey;

private:
	CObject* GetNearestToMouseMinion();

public:
	COrbWalker::COrbWalker() : m_pTarget(nullptr), m_nLastAttackCmdTick(0), m_nLastMoveCmdTick(0), m_lastMoveClickTime(0), m_lastAttackClickTime(0),
		lastHitOnly(false), autoMove(true), preferHarassOverFarm(true), useAutokey(true)
	{
	}

public: 	
	bool isManual;
	CObject* m_pTarget;
	CObject* target;
	//ESpellSlot AAResetSlot;

public:
	void Orbwalk();
	void CastSpell(Vector pos, HKey key);
	void tryFindTarget();
	CObject* FindTargetInRange(float range);
	void drawEvent();
	//ESpellSlot getAAResetSlot();
};
