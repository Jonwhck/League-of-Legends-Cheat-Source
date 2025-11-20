#pragma once
#include "CObject.h"
#include "SpellSlot.h"

class Typedefs {
public:
	typedef void(__thiscall* tPrintChat)(DWORD ChatClient, const char* Message, int color); //int color
	typedef void(__thiscall* tSendChat)(DWORD ChatClient, const char* Message); //int color
	typedef int*(__thiscall* fnIssueOrder)(void *thisPtr, int Order, Vector *Loc, CObject *Target, bool IsAttackMove, bool IsMinion, DWORD Unknown);
	//typedef int* (__thiscall* fnIssueOrder)(void* thisPtr, bool IsAttackMove, bool IsMinion, DWORD Unknown, CObject* Target, Vector* Loc, int Order);
	typedef float(__cdecl* fnGetAttackCastDelay)(CObject* pObj);
	typedef float(__cdecl* fnGetAttackDelay)(CObject* pObj);
	typedef void(__cdecl* fnDrawCircle)(Vector* position, float range, int* color, int a4, float a5, int a6, float alpha);
	typedef int* (__thiscall* fnCastSpell)(DWORD spellbook_addr, SpellSlot* spellslot, int SlotID, Vector* targetpos, Vector* startpos, DWORD NetworkID);
	typedef void(__thiscall* fnPrintChat)(DWORD ChatClient, const char* Message, int Color);

	//typedef int(__thiscall* fnPrintChat)(CObject* pObj, SpellCastInfo* castinfo)

	typedef bool(__cdecl* WorldToScreen)(Vector* vectorIn, Vector* vectorOut);

	typedef bool(__cdecl* fnIsHero)(CObject* pObj);
	typedef bool(__cdecl* fnIsMissile)(CObject* pObj);
	typedef bool(__cdecl* fnIsMinion)(CObject* pObj);
	typedef bool(__cdecl* fnIsDrake)(CObject* pObj);
	typedef bool(__cdecl* fnIsBaron)(CObject* pObj);
	typedef bool(__cdecl* fnIsTurret)(CObject* pObj);
	typedef bool(__cdecl* fnIsInhibitor)(CObject* pObj);
	typedef bool(__cdecl* fnIsTroyEnt)(CObject* pObj);
	typedef bool(__cdecl* fnIsNexus)(CObject* pObj);
	typedef float(__cdecl* fnGetAttackCastDelay)(CObject* pObj);
	typedef float(__cdecl* fnGetAttackDelay)(CObject* pObj);
	typedef bool(__thiscall* fnIsAlive)(CObject* pObj);
	typedef bool(__thiscall* fnIsTargetable)(CObject* pObj);
	typedef bool(__thiscall* fnGetPing)(CObject* pObj);



};

class CFunctions {
public:
	Typedefs::fnIsTurret IsTurret;
	Typedefs::fnIsMinion IsMinion;
	Typedefs::fnIsDrake IsDrake;
	Typedefs::fnIsBaron IsBaron;
	Typedefs::fnIsHero IsHero;
	Typedefs::fnIsMissile IsMissile;
	Typedefs::fnIsTroyEnt IsTroyEnt;
	Typedefs::fnIsNexus IsNexus;
	Typedefs::fnIsInhibitor IsInhibitor;
	Typedefs::WorldToScreen WorldToScreen;
	Typedefs::fnIsTargetable IsTargetable;
	Typedefs::fnIsAlive IsAlive;

	Typedefs::fnGetPing GetPing;


	Typedefs::fnIssueOrder IssueOrder;
	Typedefs::fnGetAttackCastDelay GetAttackCastDelay;
	Typedefs::fnGetAttackDelay GetAttackDelay;
	Typedefs::fnDrawCircle DrawCircle;
	Typedefs::fnCastSpell CastSpell;
	Typedefs::fnPrintChat PrintChat;
	Typedefs::fnPrintChat SendChat;
};

extern CFunctions Functions;