#pragma once
#include "Offsets.h"
#include "Utils.h"
#include "Vector.h"
#include "Hooks.h"
#include "CObjectManager.h"
#include "Input.h"



#define me Engine::GetLocalObject()
#define undermouse Engine::GetUnderMouseObject()


class Engine {
public:
	static Vector GetMouseWorldPosition() {
		DWORD MousePtr = (DWORD)GetModuleHandle(NULL) + oHudInstance;
		auto aux1 = *(DWORD*)MousePtr;
		aux1 += 0x14;
		auto aux2 = *(DWORD*)aux1;
		aux2 += 0x1C;

		float X = *(float*)(aux2 + 0x0);
		float Y = *(float*)(aux2 + 0x4);
		float Z = *(float*)(aux2 + 0x8);

		return Vector{ X, Y, Z };
	}

	static float GetGameTime() {
		return *(float*)(baseAddr + oGameTime);
	}

	static auto GetZoomInstance() {
		return*(DWORD*)(baseAddr + oZoomClass);
	}

	static float SetZoomAmount() {
		*(float*)((DWORD)GetZoomInstance() + oZoomAmount) = 4000;
		return *(float*)((DWORD)GetZoomInstance() + oZoomAmount);
		//auto hud = *(DWORD*)(baseAddr + oHudInstance);
		//auto camerapointer = *(DWORD*)(hud + 0xc);
		//*(float*)((DWORD)camerapointer + 0x26c) = 4000;
	}

	static void ChangeName() {
		char newName[] = "NIGGER";
		CopyMemory((void*)(me + oObjName), &newName, sizeof(newName));
	}

	static auto Chat() {
		return*(DWORD*)(baseAddr + oChat);
	}

	static bool isChatOpen() {
		return *(bool*)((DWORD)Chat() + oChatIsOpen);
	}

	static D3DXMATRIX* GetViewMatrix() {
		return(D3DXMATRIX*)(baseAddr + oViewMatrix);
	}

	static D3DXMATRIX* GetProjectionMatrix() {
		return(D3DXMATRIX*)(baseAddr + oViewMatrix + 0x40);
	}

	static D3DXMATRIX* GetVeiwProjectionMatrix(D3DXMATRIX* matrix) {
		D3DXMatrixMultiply(matrix, GetViewMatrix(), GetProjectionMatrix());
		return matrix;
	}	

	static auto GetRenderInstance() {
		return*(DWORD*)(baseAddr + oRenderer);
}
	static D3DXVECTOR2 ScreenRes() {
		int x = *(int*)((DWORD)GetRenderInstance() + oRendererWidth);
		int y = *(int*)((DWORD)GetRenderInstance() + oRendererHeight);
		return D3DXVECTOR2(x,y);
	}

	static D3DXVECTOR2 World2Screen(D3DXVECTOR3 pos) {
		D3DXVECTOR2 returnVec;
		D3DXVECTOR2 screen = ScreenRes();
		D3DXMATRIX matrix;
		GetVeiwProjectionMatrix(&matrix);

		D3DXVECTOR4 clipCoords;
		clipCoords.x = pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8] + matrix[12];
		clipCoords.y = pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9] + matrix[13];
		clipCoords.z = pos.x * matrix[2] + pos.y * matrix[6] + pos.z * matrix[10] + matrix[14];
		clipCoords.w = pos.x * matrix[3] + pos.y * matrix[7] + pos.z * matrix[11] + matrix[15];

		if (clipCoords[3] < 0.1f) return returnVec;

		D3DXVECTOR3 M;
		M.x = clipCoords.x / clipCoords.w;
		M.y = clipCoords.y / clipCoords.w;
		M.z - clipCoords.z / clipCoords.w;

		returnVec.x = (screen.x / 2 * M.x) + (M.x + screen.x / 2);
		returnVec.y = -(screen.y / 2 * M.y) + (M.y + screen.y / 2);

		return returnVec;
	}

	static CObject* GetLocalObject() {
		auto retaddr = *(DWORD*)(baseAddr + oLocalPlayer);
		
		if (retaddr == NULL)
			return NULL;

		return (CObject*)retaddr;
	}

	static CObject* GetUnderMouseObject() {
		auto retaddr = *(DWORD*)(baseAddr + oUnderMouseObject);
		auto realObj = *(DWORD*)(retaddr + 0xc);
		if (realObj == NULL)
			return NULL;

		return (CObject*)realObj;
	}

	static void PrintChat(const char* Message, DWORD color) {
		typedef void(__thiscall* tPrintChat)(DWORD ChatClient, const char* Message, int color);
		tPrintChat fnPrintChat = (tPrintChat)(baseAddr + oPrintChat); //oPrintChat
		//fnPrintChat(*(DWORD*)(baseAddr + oChatClientPtr), Message, color);

		static DWORD chatClient = *(DWORD*)(baseAddr + oChatClientPtr);

		char messageBuffer[100];
		int size = sprintf(messageBuffer, "<font color='#%06X'>%s</font>", color & 0x00FFFFFF, Message);

		return fnPrintChat(chatClient, messageBuffer, 1);
	}

	template<typename ...Args>
	void APrintChat(const char* message, DWORD color, Args ... args)
	{
		char messageBuffer[100];
		sprintf(messageBuffer, message, args...);
		PrintChat(messageBuffer, color);
	}

	static void SendChat(const char* Message) {
		typedef void(__thiscall* tSendChat)(DWORD MenuGUI, const char* Message, int Color);
		tSendChat fnSendChat = (tSendChat)(baseAddr + oSendChat);
		fnSendChat(*(DWORD*)(baseAddr + oMenuGUI), Message, 1);
	}

	static CObject* Engine::GetObjectByID(int ID)
	{
		if (ObjManager && ID >= 0 && ID <= ObjManager->GetHighestIndex()) {
			return ObjManager->GetObjByIndex(ID);
		}
		return nullptr;
	}

	static void MoveTo(Vector* pos) { //Vector* pos
		////Functions.IssueOrder(GetLocalObject(), 2, pos, NULL, false, false, false);
		//DWORD SpoofAddress = baseAddr + oRetAddr; //retn instruction
		//DWORD IssueOrderAddr = baseAddr + oIssueOrder;//IssueOrder
		//void* LocalPlayer = (void*)*(DWORD*)(baseAddr + oLocalPlayer);

		//__asm
		//{
		//	push retnHere
		//	mov ecx, LocalPlayer
		//	push 0
		//	push 0
		//	push 0
		//	push 0
		//	push pos
		//	push 2
		//	push SpoofAddress
		//	jmp IssueOrderAddr
		//	retnHere :
		//}
	
	}
		
	static void AttackTarget(CObject* obj) {//CObject* obj
/*		auto objPos = obj->GetPos2D();
		//Functions.IssueOrder(GetLocalObject(), 3, &objPos, obj, true, false, false);
		DWORD SpoofAddress = baseAddr + oRetAddr; //retn instruction
		DWORD IssueOrderAddr = baseAddr + oIssueOrder;//IssueOrder
		void* LocalPlayer = me;

		__asm
		{
			push retnHere
			mov ecx, LocalPlayer
			push 1
			push 0
			push 0
			push obj
			push objPos
			push 3
			push SpoofAddress
			jmp IssueOrderAddr
			retnHere :
		}*/

	}

	static void Engine::CastSpellSelf(int SlotID) {
		if (me->IsAlive()) {
			auto spellbook = (DWORD)me + oObjSpellBook;
			auto spellslot = me->GetSpellBook()->GetSpellSlotByID(SlotID);
			Functions.CastSpell(spellbook, spellslot, SlotID, &me->GetPos2D(), &me->GetPos2D(), 0);
		}
	}

	static void Engine::CastSpellPos(int SlotID, Vector pos) {
		auto spellbook = (DWORD)me + oObjSpellBook;
		auto spellslot = me->GetSpellBook()->GetSpellSlotByID(SlotID);
		auto targetpos = &pos;

		Functions.CastSpell(spellbook, spellslot, SlotID, targetpos, new Vector(0, 0, 0), 0x0);
	}

	static void Engine::CastSpellPos(int SlotID, float x, float y, float z, CObject* obj) {
		auto spellbook = (DWORD)me + oObjSpellBook;
		auto spellslot = me->GetSpellBook()->GetSpellSlotByID(SlotID);
		Vector* pos = new Vector(x, y, z);
		//Functions.CastSpell(spellbook, spellslot, SlotID, &obj->GetPos(), &me->GetPos(), obj->GetNetworkID());
		delete pos;
	}

	static void Engine::CastSpellTargetted(int SlotID, CObject* obj) {
		auto spellbook = (DWORD)me + oObjSpellBook;
		auto spellslot = me->GetSpellBook()->GetSpellSlotByID(SlotID);

		//Functions.CastSpell(spellbook, spellslot, SlotID, &obj->GetPos(), &me->GetPos(), obj->GetNetworkID());
	}

	static float Engine::getCD(int slot, CObject* obj) {

		//Console.print("CD : %f", obj->GetSpellBook()->GetSpellSlotByID(slot)->GetCD() - Engine::GetGameTime());
		return obj->GetSpellBook()->GetSpellSlotByID(slot)->GetFinalCooldownExpire();
	}

	static bool Engine::IsReady(int slot, CObject* obj) {
		//Console.print("LEVEL : %i", obj->GetSpellBook()->GetSpellSlotByID(slot)->GetLevel());
		return obj->GetSpellBook()->GetSpellSlotByID(slot)->GetLevel() >= 1 && getCD(slot, obj) == 0.0f;
	}


};



