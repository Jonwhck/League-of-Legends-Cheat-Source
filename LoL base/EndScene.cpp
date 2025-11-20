#include "pch.h"
#include "base.h"
#include "ImRender.hpp"
#include "Engine.h"
#include "ESpellSlot.h"
#include "CycleManager.h"
#include "Orbwalker.h"
#include "Input.h"
#include "base.h"
#include "charcolor.h"
#include "Utils.h"
#include "dllmain.h"

CObjectManager* ObjManager;
COrbWalker orbWalker;
CFunctions Functions;


HMODULE g_module = nullptr;
HWND g_hwnd = nullptr;
WNDPROC g_wndproc = nullptr;
bool g_menu_opened = false;
bool g_myrange = true;
bool g_myQrange = false;
bool g_myWrange = false;
bool g_myErange = false;
bool g_myRrange = false;
bool g_lasthit = false;
bool g_unload = false;
bool g_awareness = false;
bool g_drawevade = false;
bool g_enemyrange = false;
bool g_orbcombo = false;
bool g_orblasthit = false;
bool g_autosmite = false;
bool g_debug = false;
bool OnStartMessage = true;
bool cansend = true;
float sent = 0;
using namespace std;
float LastAA;
float LastMove;
int getLatencyTicks = 100;

int xoffset=-46;
int yoffset = -106;

int minionxoffset = -32;
int minionyoffset = -55;

bool g_interface = false;



HRESULT __stdcall Base::Hooks::EndScene(LPDIRECT3DDEVICE9 pDevice)
{
	Data::pDxDevice9 = pDevice;
	if (!Data::InitImGui)
	{
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
		ImGui_ImplWin32_Init(Data::hWindow);
		ImGui_ImplDX9_Init(pDevice);



		Data::InitImGui = true;
	}

	if (!Data::InitImGui) return Data::oEndScene(pDevice);

	render.begin_draw();
	render.draw_text(Engine::ScreenRes().x / 2 - 40, 20, "Tranquillity", false, ImColor(255, 255, 255, 255));

	if (Data::ShowMenu)
	{
		ImGui::Begin("LeagueSharp", &Data::ShowMenu, ImGuiWindowFlags_NoSavedSettings);
		{
			ImGui::BeginChild("##child", ImVec2(200.0f, 170.0f), false, ImGuiWindowFlags_NoSavedSettings);
			{
				ImGui::Text("LocalPlayer");

				ImGui::SliderInt("xoffset", &xoffset, -80, 80);
				ImGui::SliderInt("yoffset", &yoffset, 0, -180);
				//ImGui::Checkbox("Autoattack Range", &g_myrange);
				////ImGui::Checkbox("Q Range", &g_myQrange);
				////ImGui::Checkbox("W Range", &g_myWrange);
				////ImGui::Checkbox("E Range", &g_myErange);
				////ImGui::Checkbox("R Range", &g_myRrange);
				//ImGui::Separator();
				//ImGui::Text("Orbwalker");
				//ImGui::Checkbox("Combo", &g_orbcombo);
				//ImGui::Checkbox("IssueMove TEST", &g_orblasthit);
				//ImGui::Separator();
				//ImGui::Text("Drawings");
				//ImGui::Checkbox("Enemy Range", &g_enemyrange);
				//ImGui::Checkbox("Awareness", &g_awareness);
				//ImGui::Checkbox("Draw Evade", &g_drawevade);
				//ImGui::Checkbox("LastHit Helper", &g_lasthit);
				//ImGui::Checkbox("AutoSmite", &g_autosmite);
				//ImGui::Separator();
				//ImGui::Checkbox("Debug", &g_debug);
				//ImGui::Checkbox("Unload", &Data::ToDetach);
				//ImGui::Checkbox("W2S/Line demostration", &g_w2s_line);
				//ImGui::Checkbox("Text champ info demostration", &g_champ_info);
			}
			ImGui::EndChild();
		}
		ImGui::End();
	}


	//CycleManager::GetObjectList();
	//CycleManager::NewCycle();
	CycleManager::GetHeroList();
	CycleManager::GetTurretList();
	CycleManager::GetMinionList();
	//CycleManager::HeroList = CycleManager::GetHeroList();
	

	//if (Engine::GetUnderMouseObject()!=nullptr) {
	//	Vector me2D = Engine::GetUnderMouseObject()->GetPos2D();
	//	Vector me2D_w2s;
	//	Functions.WorldToScreen(&me2D, &me2D_w2s);
	//	render.draw_line(me2D_w2s.X, me2D_w2s.Y, me2D_w2s.X + xoffset, me2D_w2s.Y + yoffset, ImColor(255, 255, 255, 255), 2.f);
	//}

	//char* zoomtext = new char[100];
	//int zoomvalue = GetCooldownExpire() - GetGameTime();
	//sprintf(zoomtext, "%i", zoomvalue); //f

	//render.draw_text(me2D_w2s.X, me2D_w2s.Y,  ,false, ImColor(255, 255, 255, 255));

	ComboGOd();
	Scribble();


	render.end_draw();
	if (Data::ToDetach)
		Base::Detach();
	return Data::oEndScene(pDevice);
}

////CycleManager::NewCycle();
//
////ORB COMBO
//if (g_orbcombo == true) {
//	if (me->IsAlive()) {
//		if (isKeyPressed(ORBWALKER_HOTKEY)) { // && !Engine::isChatOpen() || isKeyPressed(LASTHIT_HOTKEY)
//			orbWalker.drawEvent();
//		}
//	}
//}
//if (g_orblasthit == true) {
//	if (me->IsAlive()) {
//		if (isKeyPressed(ORBWALKER_HOTKEY)) {
//			//Engine::MoveTo(&Engine::GetMouseWorldPosition());
//		}
//	}
//}
//
//for (auto pObject : CycleManager::GetObjects()) {
//
//	//DRAW SELF
//	if (g_myrange == true) {
//		if (pObject == me) {
//			if (pObject->IsAlive()) {
//
//				//DRAW RANGE
//				D3DXVECTOR3 me_pos = pObject->GetPos();
//
//				render.DrawCircle3D(me_pos, 80, pObject->GetAttackRange() + pObject->GetBoundingRadius(), ImColor(250, 250, 250, 250), 1.0f); //+ pObject->GetBoundingRadius()
//				Vector obj_pos = pObject->GetPos2D();
//				Vector objpos_w2s;
//				Functions.WorldToScreen(&obj_pos, &objpos_w2s);
//				//auto color = createRGB(255, 0, 255);
//				//Functions.DrawCircle(&pObject->GetPos2D(), pObject->GetAttackRange() + pObject->GetBoundingRadius(), &color, 0, 0.0f, 0, 0.1f);
//
//
//				//AIMANAGER
//				auto AIManager = pObject->GetAIManager();
//				auto endPath = AIManager->GetNavEnd();
//				Vector endPath_w2s;
//				Functions.WorldToScreen(endPath, &endPath_w2s);
//				//auto serverPos = AIManager->GetServerPos();
//				//Vector serverPos_w2s;
//				//Functions.WorldToScreen(serverPos, &serverPos_w2s);
//				//render.draw_line(objpos_w2s.X, objpos_w2s.Y, endPath_w2s.X, endPath_w2s.Y, ImColor(255, 255, 255, 255), 2.0f);
//				//render.draw_text(serverPos_w2s.X, serverPos_w2s.Y, "POS!", true, AIManager->IsDashing() ? ImColor(0, 255, 0, 255) : ImColor(255, 0, 0, 255));
//
//
//
//				//SPELL
//				auto objSpellBook = pObject->GetSpellBook();
//				auto spellQ = objSpellBook->CSpellBook::GetSpellSlotByID(static_cast<int>(ESpellSlot::Q));
//
//				//Engine::PrintChat(spellQName, CHAT_FLAG_TURQUOISE);
//				//auto spellQInfo = spellQ->getSpellInfo();
//				//auto spellQName = spellQInfo->GetName();
//				auto spellW = objSpellBook->CSpellBook::GetSpellSlotByID(static_cast<int>(ESpellSlot::W));
//				auto spellE = objSpellBook->CSpellBook::GetSpellSlotByID(static_cast<int>(ESpellSlot::E));
//				auto spellR = objSpellBook->CSpellBook::GetSpellSlotByID(static_cast<int>(ESpellSlot::R));
//
//				//Engine::PrintChat(spellQName, CHAT_FLAG_TURQUOISE);
//				//char remainq[20];		
//				//int remaint = spellQ->SpellSlot::GetCooldownExpire() - Engine::GetGameTime();
//				//sprintf(remainq, "%d", remaint); //f
//				//render.draw_text(objpos_w2s.X, objpos_w2s.Y + 30, spellQ->SpellSlot::RemainingCD("[Q]"), true, spellQ->SpellSlot::IsReady() ? ImColor(0, 255, 0, 255) : ImColor(255, 0, 0, 255));
//				//render.draw_text(objpos_w2s.X + 30, objpos_w2s.Y + 30, spellW->SpellSlot::RemainingCD("[W]"), true, spellW->SpellSlot::IsReady() ? ImColor(0, 255, 0, 255) : ImColor(255, 0, 0, 255));
//				//render.draw_text(objpos_w2s.X + 60, objpos_w2s.Y + 30, spellE->SpellSlot::RemainingCD("[E]"), true, spellE->SpellSlot::IsReady() ? ImColor(0, 255, 0, 255) : ImColor(255, 0, 0, 255));
//				//render.draw_text(objpos_w2s.X + 90, objpos_w2s.Y + 30, spellR->SpellSlot::RemainingCD("[R]"), true, spellR->SpellSlot::IsReady() ? ImColor(0, 255, 0, 255) : ImColor(255, 0, 0, 255));
//
//			}
//		}
//	}
//
//	//DRAW ENEMY
//	if (g_enemyrange == true) {
//		if (pObject->IsHero() && pObject->IsAlive() && pObject->IsVisible() && pObject->IsTargetable() && pObject->IsEnemyTo(me))
//		{
//			Vector obj_pos2D = pObject->GetPos2D();
//			Vector objpos2D_w2s;
//			Functions.WorldToScreen(&obj_pos2D, &objpos2D_w2s);
//
//			auto objSpellBook = pObject->GetSpellBook();
//
//			auto spellQ = objSpellBook->CSpellBook::GetSpellSlotByID(static_cast<int>(ESpellSlot::Q));
//			auto spellW = objSpellBook->CSpellBook::GetSpellSlotByID(static_cast<int>(ESpellSlot::W));
//			auto spellE = objSpellBook->CSpellBook::GetSpellSlotByID(static_cast<int>(ESpellSlot::E));
//			auto spellR = objSpellBook->CSpellBook::GetSpellSlotByID(static_cast<int>(ESpellSlot::R));
//			auto spellD = objSpellBook->CSpellBook::GetSpellSlotByID(static_cast<int>(ESpellSlot::D));
//			auto spellF = objSpellBook->CSpellBook::GetSpellSlotByID(static_cast<int>(ESpellSlot::F));
//
//			//render.draw_text(objpos_w2s.X, objpos_w2s.Y + 15, pObject->GetChampionName(), true, ImColor(255, 0, 0, 255));
//			render.draw_text(objpos2D_w2s.X, objpos2D_w2s.Y + 30, spellQ->SpellSlot::RemainingCD("[Q]"), true, spellQ->SpellSlot::IsReady() ? ImColor(0, 255, 0, 255) : ImColor(255, 0, 0, 255));
//			render.draw_text(objpos2D_w2s.X + 30, objpos2D_w2s.Y + 30, spellW->SpellSlot::RemainingCD("[W]"), true, spellW->SpellSlot::IsReady() ? ImColor(0, 255, 0, 255) : ImColor(255, 0, 0, 255));
//			render.draw_text(objpos2D_w2s.X + 60, objpos2D_w2s.Y + 30, spellE->SpellSlot::RemainingCD("[E]"), true, spellE->SpellSlot::IsReady() ? ImColor(0, 255, 0, 255) : ImColor(255, 0, 0, 255));
//			render.draw_text(objpos2D_w2s.X + 90, objpos2D_w2s.Y + 30, spellR->SpellSlot::RemainingCD("[R]"), true, spellR->SpellSlot::IsReady() ? ImColor(0, 255, 0, 255) : ImColor(255, 0, 0, 255));
//			render.draw_text(objpos2D_w2s.X + 150, objpos2D_w2s.Y + 30, spellD->SpellSlot::RemainingCD("[D]"), true, spellD->SpellSlot::IsReady() ? ImColor(0, 255, 0, 255) : ImColor(255, 0, 0, 255));
//			render.draw_text(objpos2D_w2s.X + 190, objpos2D_w2s.Y + 30, spellF->SpellSlot::RemainingCD("[F]"), true, spellF->SpellSlot::IsReady() ? ImColor(0, 255, 0, 255) : ImColor(255, 0, 0, 255));
//
//			if (pObject->GetDistanceToMe() < 1500.0f) {
//				D3DXVECTOR3 obj_pos = pObject->GetPos();
//				render.DrawCircle3D(obj_pos, 80, pObject->GetAttackRange() + pObject->GetBoundingRadius(), ImColor(250, 0, 0, 100), 1.0f);
//				//Vector obj_pos = pObject->GetPos2D();
//				//Vector objpos_w2s;
//				//Functions.WorldToScreen(&obj_pos, &objpos_w2s);
//				//auto color = createRGB(255, 0, 0);
//				//Functions.DrawCircle(&pObject->GetPos2D(), pObject->GetAttackRange() + pObject->GetBoundingRadius(), &color, 0, 0.0f, 0, 1.0f);
//			}
//		}
//	}
//
//	//AWARENESS WARD CLONES TRAPS && RECALL TRACKER
//	if (g_awareness == true) {
//		if (pObject->IsMinion() && pObject->IsEnemyTo(me)) {
//			Vector obj_pos2D = pObject->GetPos2D();
//			Vector objpos2D_w2s;
//			Functions.WorldToScreen(&obj_pos2D, &objpos2D_w2s); //|| pObject->is("ShacoBox")
//			//render.draw_text(objpos2D_w2s.X, objpos2D_w2s.Y + 30, pObject->GetName(), true, ImColor(255, 0, 0, 255));
//
//			if (pObject->is("Shaco")) {
//				render.draw_text(objpos2D_w2s.X, objpos2D_w2s.Y + 30, "CLONE", true, ImColor(255, 0, 0, 255));
//			}
//
//			if (pObject->is("Leblanc")) {
//				render.draw_text(objpos2D_w2s.X, objpos2D_w2s.Y + 30, "CLONE", true, ImColor(255, 0, 255, 255));
//			}
//
//			if (pObject->is("Neeko")) {
//				render.draw_text(objpos2D_w2s.X, objpos2D_w2s.Y + 30, "CLONE", true, ImColor(255, 255, 0, 255)); //TEST
//			}
//
//			if (pObject->is("Wukong")) {
//				render.draw_text(objpos2D_w2s.X, objpos2D_w2s.Y + 30, "CLONE", true, ImColor(255, 255, 0, 255)); //TEST
//			}
//
//			if (pObject->is("ShacoBox")) {
//				render.draw_text(objpos2D_w2s.X, objpos2D_w2s.Y + 30, pObject->GetName(), true, ImColor(255, 0, 0, 255));
//			}
//			if (pObject->is("TeemoMushroom")) {
//				render.draw_text(objpos2D_w2s.X, objpos2D_w2s.Y + 30, pObject->GetName(), true, ImColor(0, 255, 0, 255));
//			}
//
//			if (pObject->IsWard()) {
//				render.draw_text(objpos2D_w2s.X, objpos2D_w2s.Y + 30, pObject->GetName(), true, ImColor(255, 255, 0, 255));
//			}
//			/*else {
//				render.draw_text(objpos2D_w2s.X, objpos2D_w2s.Y + 30, pObject->GetName(), true, ImColor(255, 255, 255, 255));
//			}
//			*/
//		}
//	}
//	if (pObject->IsTurret() && pObject->IsEnemyTo(me)) {
//		auto turretRange = 800.0f + me->GetBoundingRadius();
//		if (pObject->GetDistanceToMe() < (turretRange + 300.f)) {
//			auto turretPos = pObject->GetPos();
//			render.DrawCircle3D(turretPos, 80, turretRange, ImColor(250, 0, 0, 100), 1.0f);
//		}
//	}
//
//	//DRAW LASTHIT MINION
//	if (g_lasthit == true) {
//		if (pObject->IsMinion() && pObject->IsAlive() && !pObject->Isjungle() && pObject->IsEnemyTo(me) && pObject->GetDistanceToMe() < 1500.0f)
//		{
//			float targetHealth = pObject->GetHealth(); //pObject->IsMinion() && pObject->IsAlive() && pObject->IsVisible() && pObject->IsEnemyTo(me)
//			float myDamage = me->GetTotalAttackDamage();
//			float targetArmor = pObject->GetArmor();
//			float dmgReduction = 100 / (100 + targetArmor);
//			Vector obj_pos2D = pObject->GetPos2D();
//			Vector objpos2D_w2s;
//			Functions.WorldToScreen(&obj_pos2D, &objpos2D_w2s);
//			//render.draw_text(objpos2D_w2s.X, objpos2D_w2s.Y + 30, pObject->GetName(), true, ImColor(255, 0, 0, 255));
//			//render.draw_text(objpos2D_w2s.X+20, objpos2D_w2s.Y + 30, "0"+pObject->GetTeam(), true, ImColor(255, 0, 0, 255));
//			if ((myDamage * dmgReduction) > targetHealth) {
//				D3DXVECTOR3 target_pos = pObject->GetPos();
//				render.DrawCircle3D(target_pos, 80, pObject->GetBoundingRadius(), ImColor(255, 0, 0, 255), 5.0f);
//
//			}
//		}
//	}
//
//	//DRAW EVADE
//	if (g_drawevade == true) {
//		if (pObject->IsMissile())
//		{
//			//objcaster non funziona :s
//			auto objCaster = Engine::GetObjectByID(pObject->GetMissileSourceIndex());
//			if (objCaster->IsHero() && objCaster->GetDistanceToMe() < 1500.0f && !stristr(pObject->GetName(), "basic")) {
//				//D3DXVECTOR3 me_pos = objCaster->GetPos();
//				auto spellinfo = pObject->GetSpellInfo();
//				//auto spelldata = spellinfo->GetSpellData();
//				//Engine::PrintChat(pObject->GetName(), CHAT_FLAG_GOLD);
//				//render.DrawCircle3D(me_pos, 80, spelldata->GetSpellRange(), ImColor(250, 250, 250, 250), 1.0f);
//				Vector start_pos = pObject->GetMissileStartPos();
//				Vector start_pos_w2s;
//				Functions.WorldToScreen(&start_pos, &start_pos_w2s);
//				Vector end_pos = pObject->GetMissileEndPos();
//				Vector end_pos_w2s;
//				Functions.WorldToScreen(&end_pos, &end_pos_w2s);
//				//render.draw_text(start_pos_w2s.X, start_pos_w2s.Y + 30, pObject->GetMissileName(), true, ImColor(0, 255, 0, 255));
//				render.draw_line(start_pos_w2s.X, start_pos_w2s.Y, end_pos_w2s.X, end_pos_w2s.Y, ImColor(255, 255, 255, 255), 2.0F);
//			}
//		}
//	}
//
//	//AUTOSMITE
//	if (g_autosmite == true) {
//		if (pObject->IsMinion() && pObject->IsAlive() && pObject->Isjungle() && pObject->GetDistanceToMe() <= 500.0f + me->GetBoundingRadius() + pObject->GetBoundingRadius()) {
//			/*Vector obj_pos = pObject->GetPos2D();
//			Vector objpos_w2s;
//			Functions.WorldToScreen(&obj_pos, &objpos_w2s);
//			render.draw_text(objpos_w2s.X, objpos_w2s.Y + 30, pObject->GetName(), true, ImColor(255, 255, 255, 255));*/
//			if (pObject->IsDrake() || pObject->IsBaron() || pObject->IsHerald()) {
//				//char Get_Healthe[100];						///					
//				//sprintf(Get_Healthe, "%f", pObject->GetHealth());
//				//Engine::PrintChat(Get_Healthe);
//				//Engine::PrintChat("FOUND MINION IN SMITERANGE", CHAT_FLAG_GOLD);
//				if (pObject->GetHealth() < 900.0f) {
//					Vector obj_pos = pObject->GetPos2D();
//					Vector objpos_w2s;
//					Functions.WorldToScreen(&obj_pos, &objpos_w2s);
//					//render.draw_text(objpos_w2s.X, objpos_w2s.Y + 30, pObject->GetName(), true, ImColor(255, 255, 255, 255));
//					//Input::MoveCursorTo(objpos_w2s.X, objpos_w2s.Y);
//					//Input::MoveCursorTo(objpos_w2s.X, objpos_w2s.Y);
//					//Input::MoveCursorTo(objpos_w2s.X, objpos_w2s.Y);
//					//Input::PressKey(F);
//					//Input::PressKey(F);
//					//Input::PressKey(F);
//					Input::MoveCursorTo(objpos_w2s.X, objpos_w2s.Y);
//					Input::PressKey(F);
//				}
//			}
//		}
//
//	}
//
//}