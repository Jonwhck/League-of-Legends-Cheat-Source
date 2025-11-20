#pragma once
#include <Windows.h>
#include "Offsets.h"
#include "Vector.h"
#include "SpellInfo.h"
#include <stdio.h>
#include "stdafx.h"
#include <iostream>
#include <string> 
#include "Utils.h"
using namespace std;

class SpellSlot {
public:

	int GetLevel() {
		return *(int*)((DWORD)this + oSpellSlotLevel);
	}

	float GetCooldownExpire() {
		return *(float*)((DWORD)this + oSpellSlotTime);
	}

	float GetFinalCooldownExpire() {
		return *(float*)((DWORD)this + 0x18);
	}

	float GetCooldown() {
		return *(float*)((DWORD)this + 0xA4);
	}

	int GetCharges() {
		return *(int*)((DWORD)this + oSpellSlotCharges);
	}

	static float GetGameTime() {
		return *(float*)(baseAddr + oGameTime);
	}

	bool IsReady() {
		return GetLevel() >= 1 && (GetGameTime() >= GetCooldownExpire());
	}

	char* RemainingCD(char* slot) {	
		char* remainq = new char[100];
		int remaint = GetCooldownExpire() - GetGameTime();
		sprintf(remainq, "%d", remaint); //f
		if (GetGameTime() >= GetCooldownExpire())
			return slot;
		return remainq;
	}
	SpellInfo* getSpellInfo() {
		return (SpellInfo*)((DWORD)this + oSpellSlotSpellInfo);
}

};