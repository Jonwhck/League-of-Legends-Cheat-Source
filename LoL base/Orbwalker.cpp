#include "Orbwalker.h"
#include "Engine.h"
#include "CycleManager.h"
#include "ImRender.hpp"
#include "Vector.h"
#include <iostream>
#include <WinUser.h>
#include "Input.h"
#include "Utils.h"

#include <vector>
#include <algorithm>
#include <chrono>

static int getLatencyTicks(int extraTicks = 20) {
	return (extraTicks + 50 / 2);
}


float m_nLastAttackCmdTick;
float m_nLastMoveCmdTick;
bool back = true;
Vector2 lastMouse;
Vector enemy_pos;
point mouse = point(0,0);
bool canCast = true;
bool canKite = true;

// AttackCastDelay = time until u can move without canceling attack
// AttackDelay = time until u can attack again
float flTimeTilAttack() { return me->GetAttackDelay(); }
int nTicksTilAttack() {
	return static_cast<int>(flTimeTilAttack()*1000); //ATTACKDELAY
}
float flTimeToMove() { return me->GetAttackCastDelay(); }
int nTicksToMove() {
	if (me->GetChampionName() == "Kalista") { return 0; }
	return (int)(flTimeToMove() * 100); //WINDUP
}

static bool CanAttack() {
	return ((int)(Engine::GetGameTime() * 1000)) > (m_nLastAttackCmdTick + nTicksTilAttack());
}

static bool CanMove() {
		return m_nLastMoveCmdTick < ((int)(Engine::GetGameTime() * 1000));

}

void moveBack() {
	this_thread::sleep_for(10ms);
	Input::MoveCursorTo(lastMouse.x, lastMouse.y);
	canCast = true;
	canKite = true;
}


void COrbWalker::CastSpell(Vector pos, HKey key){

	if (canCast) {
		Vector pos_w2s;
		Functions.WorldToScreen(&pos, &pos_w2s);

		std::chrono::milliseconds now = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch());
		if (now >= m_lastMoveClickTime + std::chrono::milliseconds(100)) {

			lastMouse = Input::GetCursorPosition();
			BlockInput(true);
			canKite = false;
			Input::MoveCursorTo(pos_w2s.X, pos_w2s.Y);
			Input::PressKey(K);
			Input::PressKey(key);
			Input::ReleaseKey(key);
			thread(moveBack).detach();
			Input::ReleaseKey(K);
			//Engine::AttackTarget(m_pTarget);
			BlockInput(false);

			//lastMouse = Input::GetCursorPosition();
			m_lastMoveClickTime = now;
		}
	}
}

void COrbWalker::Orbwalk()
{
	CObject* pLocal = me;
	//Autokey::PressKey(37); //K SELECT CHAMP ONLY 
	float flTimeToMove = pLocal->GetAttackCastDelay();
	float flTimeTilAttack = pLocal->GetAttackDelay();
	int nTicksTilAttack = static_cast<int>(flTimeTilAttack * 1000);

	// can we attack?

	if (((Engine::GetGameTime() * 1000) + getLatencyTicks()) >= (m_nLastAttackCmdTick + nTicksTilAttack) && m_pTarget != nullptr)
	{

		Functions.WorldToScreen(&m_pTarget->GetPos2D(), &enemy_pos);


		lastMouse = Input::GetCursorPosition();
		// issue an attackunit order 
		canCast = false;
		BlockInput(true);
		Input::MoveCursorTo(enemy_pos.X, enemy_pos.Y);
		Input::PressKey(K);
		Input::PressKey(U);
		Input::ReleaseKey(U);
		thread(moveBack).detach();
		Input::ReleaseKey(K);
		//Engine::AttackTarget(m_pTarget);
		BlockInput(false);

		// appropriately set the last attack tick
		m_nLastAttackCmdTick = (Engine::GetGameTime() * 1000) + getLatencyTicks();
		m_nLastMoveCmdTick = Engine::GetGameTime() * 1000 + getLatencyTicks() + nTicksToMove();
	}
	else
	{
		float flTimeToMove = pLocal->GetAttackCastDelay();
		int nTicksToMove = static_cast<int>(flTimeToMove * 1000) + getLatencyTicks(50);
		// can we move without canceling the attack we've waited for?
		if ((Engine::GetGameTime() * 1000) >= (m_nLastAttackCmdTick + nTicksToMove))
		{
			// issue a move order

			std::chrono::milliseconds now = std::chrono::duration_cast<std::chrono::milliseconds>(
				std::chrono::system_clock::now().time_since_epoch());
			if (now >= m_lastMoveClickTime + std::chrono::milliseconds(30)) {
				//Autokey::PressKey(22);
				//Autokey::ReleaseKey(22); //U MOVE
				//Engine::MoveTo(&Engine::GetMouseWorldPosition());


				Input::PressKey(K);
				Input::PressKey(I);
				Input::ReleaseKey(I);
				Input::ReleaseKey(K);

				//lastMouse = Input::GetCursorPosition();
				m_lastMoveClickTime = now;
			}

			// the last tickcount that we moved following an attack
			m_nLastMoveCmdTick = (Engine::GetGameTime() * 1000) + getLatencyTicks(30);
		}
	}

	//Autokey::ReleaseKey(37);
}

void COrbWalker::tryFindTarget()
{
	CObject* pLocal = me;


	// Don't find one if we already have one
	//
	if (isManual) {
		if (target != nullptr) {
			if (target->IsAlive() && target->IsVisible() && target->isTargetableValue()) {
				if (target->GetDistanceToMe() <= pLocal->GetAttackRange() + pLocal->GetBoundingRadius()) {
					m_pTarget = target;
					return;
				}
			}
		}
	}

	if (m_pTarget != nullptr)
	{
		if (m_pTarget->IsAlive())
		{
			if (m_pTarget->GetDistanceToMe() <= pLocal->GetAttackRange() + pLocal->GetBoundingRadius())
			{
				return;
			}
		}

		m_pTarget = nullptr;
	}

	bool heroesInRange = false;
	std::vector<CObject*> vecPossibleTargets;
	for (auto pObject : CycleManager::HeroList)
	{
		if (pObject != nullptr)
		{ // && pObject->IsTargetable() NON FUNZIONA!
			if (pObject->IsAlive() && pObject->IsVisible() && pObject->isTargetableValue() &&
				pObject->GetDistanceToMe() <= pLocal->GetAttackRange() + pLocal->GetBoundingRadius())//pObject->IsVisible() && !pObject->IsInvalidObject() &&
			{
				vecPossibleTargets.push_back(pObject);
			}
		}
	}
	m_pTarget = nullptr;

	if (vecPossibleTargets.empty())
		return;

	if (vecPossibleTargets.size() > 1)
	{

		std::sort(vecPossibleTargets.begin(), vecPossibleTargets.end(),
			[this](CObject* pFirst, CObject* pSecond)
			{
				return (pFirst->GetHealth() < pSecond->GetHealth());
			});
	}

	// Set the target based on priority.
	m_pTarget = vecPossibleTargets.front();
	vecPossibleTargets.clear();
}

CObject* COrbWalker::FindTargetInRange(float range) {
	CObject* pLocal = me;

	// Don't find one if we already have one
	//


	if (target != nullptr)
	{
		if (target->IsAlive())
		{
			if (target->GetDistanceToMe() <= range)
			{
				return target;
			}
		}

		target = nullptr;
	}

	bool heroesInRange = false;
	std::vector<CObject*> vecPossibleTargets;
	for (auto pObject : CycleManager::HeroList)
	{
		if (pObject != nullptr)
		{ // && pObject->IsTargetable() NON FUNZIONA!
			if (pObject->IsAlive() && pObject->IsVisible() &&
				pObject->GetDistanceToMe() <= range)//pObject->IsVisible() && !pObject->IsInvalidObject() &&
			{
				vecPossibleTargets.push_back(pObject);
			}
		}
	}

	target = nullptr;

	if (vecPossibleTargets.empty())
		return nullptr;

	if (vecPossibleTargets.size() > 1)
	{

		std::sort(vecPossibleTargets.begin(), vecPossibleTargets.end(),
			[this](CObject* pFirst, CObject* pSecond)
			{
				return (pFirst->GetHealth() < pSecond->GetHealth());
			});
	}

	// Set the target based on priority.
	target = vecPossibleTargets.front();
	vecPossibleTargets.clear();
	return target;
}

void COrbWalker::drawEvent()
{
	//cout << "findingtarget" << endl;
	// try to find a target.. if we don't have one
	tryFindTarget();
	// begin orbwalk

	Orbwalk();

	if (m_pTarget != nullptr)
	{
		// main code 
		
		D3DXVECTOR3 obj_pos = m_pTarget->GetPos();
		Vector objpos2d = m_pTarget->GetPos2D();
		Vector objpos2d_w2s;
		Functions.WorldToScreen(&objpos2d, &objpos2d_w2s);
		//cout << flTimeTilAttack() << endl;
		//cout << flTimeToMove() << endl;

		render.DrawCircle3D(obj_pos, 80, m_pTarget->GetBoundingRadius(), ImColor(255, 0, 0, 255), 5.0f);

	}
	else
	{
		//m_nLastAttackCmdTick = m_nLastMoveCmdTick = 0;
	}
}

//ESpellSlot getAAResetSlot() {
//	switch()
//}
