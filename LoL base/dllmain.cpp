#include <time.h>
#include "stdafx.h"
#include "Windows.h"
#include "Engine.h"
#include "Hooks.h"
#include "detours.h"
#include "ESpellSlot.h"
#include "CycleManager.h"
#include "ImRender.hpp"
#include <mutex>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Orbwalker.h"
#include "Input.h"
#include "base.h"
#include "charcolor.h"
#include "memory.h"
#include "dllmain.h"
#include "Orbwalker.h"

int recallbarx = Engine::ScreenRes().x / 2 - (70.f * 5) / 2;
int recallbary = Engine::ScreenRes().y - 200;
bool merecall = false;
float endrecall;
HWND GameWnd = NULL;

COrbWalker orb;

void ComboGOd() {
	//if (isKeyPressed(VK_LBUTTON) && Engine::GetUnderMouseObject()->IsHero()) {
	//	orb.target = Engine::GetUnderMouseObject();
	//}
	//
	//if (isKeyPressed(VK_LBUTTON) && !Engine::GetUnderMouseObject()->IsHero()) {
	//	orb.target = NULL;
	//}

	auto EnemyList = CycleManager::HeroList;

	//ORB COMBO
	if (me->IsAlive()) {
		if (isKeyPressed(ORBWALKER_HOTKEY) && !Engine::isChatOpen() && FindWindow(0, ("League of Legends (TM) Client")) == GetForegroundWindow()) { // && !Engine::isChatOpen() || isKeyPressed(LASTHIT_HOTKEY)

			orb.drawEvent();
			

		}
	}


}

void Scribble() {

	auto EnemyList = CycleManager::HeroList;
	auto TurretList = CycleManager::TurretList;
	auto ObjectList = CycleManager::ObjectList;
	auto MinionList = CycleManager::MinionList;

	//DRAW ME
	if (me->IsAlive()) {

		//DRAW RANGE
		D3DXVECTOR3 me_pos = me->GetPos();

		auto objSpellBook = me->GetSpellBook();
		auto spellEntry = objSpellBook->GetActiveSpellEntry();
		if (spellEntry != 0) {
			if (!spellEntry->IsBasicAttack()) {
		
				auto startpos = spellEntry->GetStartPos();
				auto endpos = spellEntry->GetEndPos();
				auto spellEntryInfo = spellEntry->GetSpellInfoFromSpellCast();
				//auto spellEntryInfoName = spellEntryInfo->GetName();
				auto spellData = spellEntryInfo->GetSpellData();
				//auto spellName = spellData->GetSpellName();
				float N = spellData->GetSpellWidth() / 20 +me->GetBoundingRadius()/2;
				//cout << "X: " << endpos.X << ", Y: " << endpos.Y << ", Z: " << endpos.Z << endl;
				Vector startpos_w2s;
				Vector endpos_w2s;
				Functions.WorldToScreen(&startpos, &startpos_w2s);
				Functions.WorldToScreen(&endpos, &endpos_w2s);
		
				//render.draw_text(endpos_w2s.X + 100, endpos_w2s.Y, spellEntryInfoName, false, ImColor(255, 255, 255, 255));

				auto L = (endpos - startpos).length();
		
				auto x1p = startpos.X + N * (endpos.Z - startpos.Z) / L;
				auto x2p = endpos.X + N * (endpos.Z - startpos.Z) / L;
				auto y1p = startpos.Z + N * (startpos.X - endpos.X) / L;
				auto y2p = endpos.Z + N * (startpos.X - endpos.X) / L;
				Vector startpos_p = Vector(x1p, startpos.Y, y1p);
				Vector endpos_p = Vector(x2p, endpos.Y, y2p);
				Vector startpos_p_s;
				Vector endpos_p_s;
				Functions.WorldToScreen(&startpos_p, &startpos_p_s);
				Functions.WorldToScreen(&endpos_p, &endpos_p_s);
		
				auto x3p = startpos.X - N * (endpos.Z - startpos.Z) / L;
				auto x4p = endpos.X - N * (endpos.Z - startpos.Z) / L;
				auto y3p = startpos.Z - N * (startpos.X - endpos.X) / L;
				auto y4p = endpos.Z - N * (startpos.X - endpos.X) / L;
				Vector startpos_q = Vector(x3p, startpos.Y, y3p);
				Vector endpos_q = Vector(x4p, endpos.Y, y4p);
				Vector startpos_q_s;
				Vector endpos_q_s;
				Functions.WorldToScreen(&startpos_q, &startpos_q_s);
				Functions.WorldToScreen(&endpos_q, &endpos_q_s);
		
				//TOP
				//render.draw_line(startpos_q_s.X, startpos_q_s.Y, endpos_q_s.X, endpos_q_s.Y, ImColor(255, 255, 255, 255), 1.5);
				////BOTTOm
				//render.draw_line(startpos_p_s.X, startpos_p_s.Y, endpos_p_s.X, endpos_p_s.Y, ImColor(255, 255, 255, 255), 1.5);
				////RIGHT
				//render.draw_line(endpos_q_s.X, endpos_q_s.Y, endpos_p_s.X, endpos_p_s.Y, ImColor(255, 255, 255, 255), 1.5);
				////LEFT
				//render.draw_line(startpos_q_s.X, startpos_q_s.Y, startpos_p_s.X, startpos_p_s.Y, ImColor(255, 255, 255, 255), 1.5);
			} 
		}


		render.DrawCircle3D(me_pos, 80, me->GetAttackRange() + me->GetBoundingRadius(), ImColor(250, 250, 250, 250), 1.0f); //+ pObject->GetBoundingRadius()
		


		auto spellQ = objSpellBook->CSpellBook::GetSpellSlotByID(static_cast<int>(ESpellSlot::Q));
		auto spellW = objSpellBook->CSpellBook::GetSpellSlotByID(static_cast<int>(ESpellSlot::W));
		auto spellE = objSpellBook->CSpellBook::GetSpellSlotByID(static_cast<int>(ESpellSlot::E));
		auto spellR = objSpellBook->CSpellBook::GetSpellSlotByID(static_cast<int>(ESpellSlot::R));
		auto spellD = objSpellBook->CSpellBook::GetSpellSlotByID(static_cast<int>(ESpellSlot::D));
		auto spellF = objSpellBook->CSpellBook::GetSpellSlotByID(static_cast<int>(ESpellSlot::F));

		Vector obj_pos2D = me->GetPos2D();
		Vector objpos2D_w2s;
		Functions.WorldToScreen(&obj_pos2D, &objpos2D_w2s);
		//
		//render.draw_text(objpos2D_w2s.X - 100, objpos2D_w2s.Y + 30, spellQ->SpellSlot::RemainingCD("[Q]"), false, spellQ->SpellSlot::IsReady() ? ImColor(0, 255, 0, 255) : ImColor(255, 0, 0, 255));
		//render.draw_text(objpos2D_w2s.X - 100 + 30, objpos2D_w2s.Y + 30, spellW->SpellSlot::RemainingCD("[W]"), false, spellW->SpellSlot::IsReady() ? ImColor(0, 255, 0, 255) : ImColor(255, 0, 0, 255));
		//render.draw_text(objpos2D_w2s.X - 100 + 60, objpos2D_w2s.Y + 30, spellE->SpellSlot::RemainingCD("[E]"), false, spellE->SpellSlot::IsReady() ? ImColor(0, 255, 0, 255) : ImColor(255, 0, 0, 255));
		//render.draw_text(objpos2D_w2s.X - 100 + 90, objpos2D_w2s.Y + 30, spellR->SpellSlot::RemainingCD("[R]"), false, spellR->SpellSlot::IsReady() ? ImColor(0, 255, 0, 255) : ImColor(255, 0, 0, 255));
		//render.draw_text(objpos2D_w2s.X - 100 + 150, objpos2D_w2s.Y + 30, spellD->SpellSlot::RemainingCD("[D]"), false, spellD->SpellSlot::IsReady() ? ImColor(0, 255, 0, 255) : ImColor(255, 0, 0, 255));
		//render.draw_text(objpos2D_w2s.X - 100 + 190, objpos2D_w2s.Y + 30, spellF->SpellSlot::RemainingCD("[F]"), false, spellF->SpellSlot::IsReady() ? ImColor(0, 255, 0, 255) : ImColor(255, 0, 0, 255));
		
		//render.draw_text(objpos2D_w2s.X + 100, objpos2D_w2s.Y, me->GetChampionName(), false, ImColor(255, 255, 255, 255));

		//AIMANAGER
		auto AIManager = me->GetAIManager();
		auto endPath = AIManager->GetNavEnd();
		Vector endPath_w2s;
		Functions.WorldToScreen(endPath, &endPath_w2s);
		//render.draw_line(objpos2D_w2s.X, objpos2D_w2s.Y, endPath_w2s.X, endPath_w2s.Y, ImColor(255, 255, 255, 255), 2.0f);
	}

	//if (me->RecallState() == 6) {
	//	render.draw_rect(recallbarx, recallbary, 70.f*5, 10.f, ImColor(255, 255, 255, 255), c_renderer::rect_normal);
	//	if (merecall = false) {
	//		merecall = true;
	//		endrecall = Engine::GetGameTime() / 1000 + 8;
	//	}

	//}

#pragma region OTHER

	//DRAW ENEMY
	for (int i = 0; i < EnemyList.size(); i++) {

		Vector obj_pos2D = EnemyList[i]->GetPos2D();
		Vector objpos2D_w2s;
		Functions.WorldToScreen(&obj_pos2D, &objpos2D_w2s);

		auto objSpellBook = EnemyList[i]->GetSpellBook();

		auto spellEntry = objSpellBook->GetActiveSpellEntry();

		if (spellEntry != 0) {
			if (!spellEntry->IsBasicAttack()) {
				auto startpos = spellEntry->GetStartPos();
				auto endpos = spellEntry->GetEndPos();
				auto spellEntryInfo = spellEntry->GetSpellInfoFromSpellCast();
				auto spellData = spellEntryInfo->GetSpellData();
				Vector startpos_w2s;
				Vector endpos_w2s;
				Functions.WorldToScreen(&startpos, &startpos_w2s);
				Functions.WorldToScreen(&endpos, &endpos_w2s);
				auto L = (endpos - startpos).length();

				auto x1p = startpos.X + N * (endpos.Z - startpos.Z) / L;
				auto x2p = endpos.X + N * (endpos.Z - startpos.Z) / L;
				auto y1p = startpos.Z + N * (startpos.X - endpos.X) / L;
				auto y2p = endpos.Z + N * (startpos.X - endpos.X) / L;
				Vector startpos_p = Vector(x1p, startpos.Y, y1p);
				Vector endpos_p = Vector(x2p, endpos.Y, y2p);
				Vector startpos_p_s;
				Vector endpos_p_s;
				Functions.WorldToScreen(&startpos_p, &startpos_p_s);
				Functions.WorldToScreen(&endpos_p, &endpos_p_s);

				auto x3p = startpos.X - N * (endpos.Z - startpos.Z) / L;
				auto x4p = endpos.X - N * (endpos.Z - startpos.Z) / L;
				auto y3p = startpos.Z - N * (startpos.X - endpos.X) / L;
				auto y4p = endpos.Z - N * (startpos.X - endpos.X) / L;
				Vector startpos_q = Vector(x3p, startpos.Y, y3p);
				Vector endpos_q = Vector(x4p, endpos.Y, y4p);
				Vector startpos_q_s;
				Vector endpos_q_s;
				Functions.WorldToScreen(&startpos_q, &startpos_q_s);
				Functions.WorldToScreen(&endpos_q, &endpos_q_s);

				//TOP
				render.draw_line(startpos_q_s.X, startpos_q_s.Y, endpos_q_s.X, endpos_q_s.Y, ImColor(255, 255, 255, 255), 1.5);
				//BOTTOm
				render.draw_line(startpos_p_s.X, startpos_p_s.Y, endpos_p_s.X, endpos_p_s.Y, ImColor(255, 255, 255, 255), 1.5);
				//RIGHT
				render.draw_line(endpos_q_s.X, endpos_q_s.Y, endpos_p_s.X, endpos_p_s.Y, ImColor(255, 255, 255, 255), 1.5);
				//LEFT
				render.draw_line(startpos_q_s.X, startpos_q_s.Y, startpos_p_s.X, startpos_p_s.Y, ImColor(255, 255, 255, 255), 1.5);
			}
		}

		auto spellQ = objSpellBook->CSpellBook::GetSpellSlotByID(static_cast<int>(ESpellSlot::Q));
		auto spellW = objSpellBook->CSpellBook::GetSpellSlotByID(static_cast<int>(ESpellSlot::W));
		auto spellE = objSpellBook->CSpellBook::GetSpellSlotByID(static_cast<int>(ESpellSlot::E));
		auto spellR = objSpellBook->CSpellBook::GetSpellSlotByID(static_cast<int>(ESpellSlot::R));
		auto spellD = objSpellBook->CSpellBook::GetSpellSlotByID(static_cast<int>(ESpellSlot::D));
		auto spellF = objSpellBook->CSpellBook::GetSpellSlotByID(static_cast<int>(ESpellSlot::F));

		//render.draw_text(objpos_w2s.X, objpos_w2s.Y + 15, pObject->GetChampionName(), true, ImColor(255, 0, 0, 255));
		if (EnemyList[i]->IsVisible() && EnemyList[i]->IsAlive()) {
			render.draw_text(objpos2D_w2s.X - 100, objpos2D_w2s.Y + 30, spellQ->SpellSlot::RemainingCD("[Q]"), false, spellQ->SpellSlot::IsReady() ? ImColor(0, 255, 0, 255) : ImColor(255, 0, 0, 255));
			render.draw_text(objpos2D_w2s.X - 100 + 30, objpos2D_w2s.Y + 30, spellW->SpellSlot::RemainingCD("[W]"), false, spellW->SpellSlot::IsReady() ? ImColor(0, 255, 0, 255) : ImColor(255, 0, 0, 255));
			render.draw_text(objpos2D_w2s.X - 100 + 60, objpos2D_w2s.Y + 30, spellE->SpellSlot::RemainingCD("[E]"), false, spellE->SpellSlot::IsReady() ? ImColor(0, 255, 0, 255) : ImColor(255, 0, 0, 255));
			render.draw_text(objpos2D_w2s.X - 100 + 90, objpos2D_w2s.Y + 30, spellR->SpellSlot::RemainingCD("[R]"), false, spellR->SpellSlot::IsReady() ? ImColor(0, 255, 0, 255) : ImColor(255, 0, 0, 255));
			render.draw_text(objpos2D_w2s.X - 100 + 150, objpos2D_w2s.Y + 30, spellD->SpellSlot::RemainingCD("[D]"), false, spellD->SpellSlot::IsReady() ? ImColor(0, 255, 0, 255) : ImColor(255, 0, 0, 255));
			render.draw_text(objpos2D_w2s.X - 100 + 190, objpos2D_w2s.Y + 30, spellF->SpellSlot::RemainingCD("[F]"), false, spellF->SpellSlot::IsReady() ? ImColor(0, 255, 0, 255) : ImColor(255, 0, 0, 255));
		
		
			if (EnemyList[i]->GetDistanceToMe() < 1500.0f) {
				D3DXVECTOR3 obj_pos = EnemyList[i]->GetPos();
				render.DrawCircle3D(obj_pos, 80, EnemyList[i]->GetAttackRange() + EnemyList[i]->GetBoundingRadius(), ImColor(250, 0, 0, 80), 1.0f);			
			}
		}


		//RECALTRACKER
		if (EnemyList[i]->RecallState() == 6) {
			Vector p;
			p.X = Engine::ScreenRes().x / 2 - 100;
			p.Y = Engine::ScreenRes().y - 250 + i * 10;
			render.draw_text(p.X, p.Y, "Recalling: ", false, ImColor(255, 255, 255, 255));
			render.draw_text(p.X + 100, p.Y, EnemyList[i]->GetChampionName(), false, ImColor(255, 255, 255, 255));
		}
	}

	//LASTHIT
	for (int i = 0; i < MinionList.size(); i++) {

		Vector obj_pos2D = MinionList[i]->GetPos2D();
		Vector objpos2D_w2s;
		Functions.WorldToScreen(&obj_pos2D, &objpos2D_w2s);

		if (MinionList[i]->IsAlive()) {

			//if (MinionList[i]->IsWard()) {
			//	render.draw_text(objpos2D_w2s.X - 30, objpos2D_w2s.Y + 10, MinionList[i]->GetName(), false, ImColor(255, 255, 0, 255));
			//}

			if (MinionList[i]->IsLaneMinion() && !MinionList[i]->Isjungle() && MinionList[i]->IsEnemyTo(me) && MinionList[i]->canLastHit() && MinionList[i]->GetDistanceToMe() < 800.f) { //MinionList[i]->IsLaneMinion() &&
				D3DXVECTOR3 pos = MinionList[i]->GetPos();
				render.DrawCircle3D(pos, 20, 80, ImColor(250, 0, 0, 250), 8.0f);
				//render.draw_text(objpos2D_w2s.X , objpos2D_w2s.Y + 10, "X", false, ImColor(255, 0, 0, 255));
			}
		}

	}

	//TURRET
	for (auto tur : TurretList) {
		if (tur->GetDistanceToMe() < 1500.0f && tur->IsAlive()) {
			D3DXVECTOR3 obj_pos = tur->GetPos();
			render.DrawCircle3D(obj_pos, 80,800+me->GetBoundingRadius(), ImColor(250, 0, 0, 80), 1.0f);
		}
	}

	//for (auto obj : CycleManager::GetObjects()) {
	//
	//	Vector obj_pos2D = obj->GetPos2D();
	//	Vector objpos2D_w2s;
	//	Functions.WorldToScreen(&obj_pos2D, &objpos2D_w2s);
	//	//render.draw_text(objpos2D_w2s.X - 30, objpos2D_w2s.Y + 10, obj->GetName(), false, ImColor(255, 255, 0, 255));
	//
	//
	//	if (obj->IsMissile() && obj->GetDistanceToMe()<2000.f && !stristr(obj->GetName(), "basic")) {
	//
	//		if (stristr(obj->GetName(), "Q") || stristr(obj->GetName(), "W") || stristr(obj->GetName(), "E") || stristr(obj->GetName(), "R")) {
	//		
	//			auto startpos = obj->GetMissileStartPos();
	//			auto endpos = obj->GetMissileEndPos();
	//			Vector startPos_w2s, endPos_w2s;
	//			Functions.WorldToScreen(&startpos, &startPos_w2s);
	//			Functions.WorldToScreen(&endpos, &endPos_w2s);
	//			//render.draw_line(startPos_w2s.X, startPos_w2s.Y, endPos_w2s.X, endPos_w2s.Y, ImColor(255, 255, 255, 255), 2.0F);
	//
	//
	//
	//			auto currentpos = obj->GetPos2D();
	//
	//			render.draw_text(startPos_w2s.X, startPos_w2s.Y, obj->GetName(), false, ImColor(255, 255, 0, 255));
	//
	//			auto L = (endpos - startpos).length();
	//			auto Ls = (endpos - currentpos).length();
	//
	//			auto N = me->GetBoundingRadius();
	//
	//			auto x1p = startpos.X + N * (endpos.Z - startpos.Z) / L;
	//			auto x2p = endpos.X + N * (endpos.Z - startpos.Z) / L;
	//			auto y1p = startpos.Z + N * (startpos.X - endpos.X) / L;
	//			auto y2p = endpos.Z + N * (startpos.X - endpos.X) / L;
	//			Vector startpos_p = Vector(x1p, startpos.Y, y1p);
	//			Vector endpos_p = Vector(x2p, endpos.Y, y2p);
	//			Vector startpos_p_s;
	//			Vector endpos_p_s;
	//			Functions.WorldToScreen(&startpos_p, &startpos_p_s);
	//			Functions.WorldToScreen(&endpos_p, &endpos_p_s);
	//
	//			auto x3p = startpos.X - N * (endpos.Z - startpos.Z) / L;
	//			auto x4p = endpos.X - N * (endpos.Z - startpos.Z) / L;
	//			auto y3p = startpos.Z - N * (startpos.X - endpos.X) / L;
	//			auto y4p = endpos.Z - N * (startpos.X - endpos.X) / L;
	//			Vector startpos_q = Vector(x3p, startpos.Y, y3p);
	//			Vector endpos_q = Vector(x4p, endpos.Y, y4p);
	//			Vector startpos_q_s;
	//			Vector endpos_q_s;
	//			Functions.WorldToScreen(&startpos_q, &startpos_q_s);
	//			Functions.WorldToScreen(&endpos_q, &endpos_q_s);
	//
	//			auto x1Q = currentpos.X + N * (endpos.Z - currentpos.Z) / Ls;
	//			auto y1Q = currentpos.Z + N * (currentpos.X - endpos.X) / Ls;
	//			auto x3Q = currentpos.X - N * (endpos.Z - currentpos.Z) / Ls;
	//	//		auto y3Q = currentpos.Z - N * (currentpos.X - endpos.X) / Ls;
	//
	//
	//			////TOP
	//			render.draw_line(startpos_q_s.X, startpos_q_s.Y, endpos_q_s.X, endpos_q_s.Y, ImColor(255, 255, 255, 255), 1.5);
	//			////BOTTOm
	//			render.draw_line(startpos_p_s.X, startpos_p_s.Y, endpos_p_s.X, endpos_p_s.Y, ImColor(255, 255, 255, 255), 1.5);
	//			////RIGHT
	//			render.draw_line(endpos_q_s.X, endpos_q_s.Y, endpos_p_s.X, endpos_p_s.Y, ImColor(255, 255, 255, 255), 1.5);
	//			////LEFT
	//			render.draw_line(startpos_q_s.X, startpos_q_s.Y, startpos_p_s.X, startpos_p_s.Y, ImColor(255, 255, 255, 255), 1.5);
	//
	//		}
	//
	//	}
	//
	//
	//}



#pragma endregion

	//

#pragma region UNDERMOUSE

	auto mouse = Engine::GetUnderMouseObject();
	if (mouse != nullptr && isKeyPressed(VK_LBUTTON)) {
		if (mouse->IsHero() && mouse->IsEnemyTo(me)) {
			orb.target = mouse;
			orb.isManual = true;
		}
	}
	if (orb.isManual && orb.target != nullptr && orb.target->IsVisible()) {
		render.DrawCircle3D(orb.target->GetPos(), 80, orb.target->GetBoundingRadius() + 20, ImColor(255, 0, 255, 255), 5.f);
	}

#pragma endregion


}


void InitializeCore() {
	ObjManager = (CObjectManager*)(*(DWORD*)(baseAddr + oObjManager));
	Engine::SetZoomAmount();
	Engine::ChangeName();


	Functions.PrintChat = (Typedefs::fnPrintChat)(baseAddr + oPrintChat);
	Functions.SendChat = (Typedefs::fnPrintChat)(baseAddr + oSendChat);
	Functions.IsTargetable = (Typedefs::fnIsTargetable)(baseAddr + oIsTargetable);
	Functions.IsAlive = (Typedefs::fnIsAlive)(baseAddr + oIsAlive);
	Functions.IsMinion = (Typedefs::fnIsMinion)(baseAddr + oIsMinion);
	Functions.IsDrake = (Typedefs::fnIsDrake)(baseAddr + oIsDragon);
	Functions.IsBaron = (Typedefs::fnIsBaron)(baseAddr + oIsBaron);
	Functions.IsTurret = (Typedefs::fnIsTurret)(baseAddr + oIsTurret);
	Functions.IsHero = (Typedefs::fnIsHero)(baseAddr + oIsHero);
	Functions.IsMissile = (Typedefs::fnIsMissile)(baseAddr + oIsMissile);
	//Functions.IsNexus = (Typedefs::fnIsNexus)(baseAddr + oIsNexus);
	Functions.IsInhibitor = (Typedefs::fnIsInhibitor)(baseAddr + oIsInhib);
	//Functions.IsTroyEnt = (Typedefs::fnIsTroyEnt)(baseAddr + oIsTroy);
	Functions.CastSpell = (Typedefs::fnCastSpell)((DWORD)GetModuleHandle(NULL) + oCastSpell);
	Functions.IssueOrder = (Typedefs::fnIssueOrder)((DWORD)GetModuleHandle(NULL) + oIssueOrder);
	Functions.DrawCircle = (Typedefs::fnDrawCircle)((DWORD)GetModuleHandle(NULL) + oDrawCircle);
	Functions.WorldToScreen = (Typedefs::WorldToScreen)(baseAddr + (DWORD)oWorldToScreen);
	Functions.GetAttackCastDelay = (Typedefs::fnGetAttackCastDelay)((DWORD)GetModuleHandle(NULL) + oGetAttackCastDelay);
	Functions.GetAttackDelay = (Typedefs::fnGetAttackDelay)((DWORD)GetModuleHandle(NULL) + oGetAttackDelay);


	Engine::PrintChat("[ LEAGUESHARP ] - Core Loaded", IM_COL32(221, 162, 255, 255));

	//while (true) {
	//	this_thread::sleep_for(1000ms);
	//
	//	std::vector<CObject*> tempList;
	//	DWORD heroList_prePtr = readMem< DWORD>(baseAddr + oHeroList);
	//	DWORD heroList = readMem< DWORD>(heroList_prePtr + 0x4);
	//	cout << "heroList: " << heroList << endl;
	//	DWORD heroList_size = readMem< DWORD>(heroList_prePtr + 0x0c);
	//	cout << "heroList_size: " << heroList_size << endl;
	//	for (int i = 0; i < heroList_size; i++) {
	//		DWORD obj = readMem< DWORD>(heroList + i * 0x4);
	//		//CObject* obj_t = &obj; 
	//		float obj_health = readMem<float>(obj + oObjHealth);
	//		cout << "health: " << obj_health << endl;
	//	}
	//	CycleManager::HeroList = tempList;

	//}
}

DWORD WINAPI MainThread(LPVOID lpThreadParameter)
{
#ifdef DEBUG
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
#endif	

	while (Engine::GetGameTime() < 1.0f || !me) {
		Sleep(1);
	}
		

	Base::Data::hModule = (HMODULE)lpThreadParameter;
	//Engine::PrintChat("Init starting.", CHAT_FLAG_WHITE);
	thread(InitializeCore).detach();
	Base::Init();
	return TRUE;
}

DWORD WINAPI ExitThread(LPVOID lpThreadParameter)
{
	if (!Base::Data::Detached)
	{
		Base::Data::Detached = true;
		FreeLibraryAndExitThread(Base::Data::hModule, TRUE);
	}
	return TRUE;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(nullptr, 0, MainThread, hModule, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		if (!Base::Data::Detached)
			CreateThread(nullptr, 0, ExitThread, hModule, 0, nullptr);
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	default:
		break;
	}
	return TRUE;
}