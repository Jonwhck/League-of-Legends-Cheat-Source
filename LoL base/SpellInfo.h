#pragma once

#include "Utils.h"
#include "SpellData.h"

class SpellInfo
{
public:

	SpellInfo* GetSpellInfoFromSpellCast() {
		return (SpellInfo*)((DWORD)this + 0x8);
	}

	SpellData* GetSpellData() {
		return (SpellData*)((DWORD)this + oSpellInfoSpellData);
	}
	bool IsBasicAttack() {
		return *(bool*)((DWORD)this + 0xC4);
	}
	int GetTargetIndex() {
		return *(int*)((DWORD)this + oSpellCastDestIdx);
	}

	Vector GetMissileEndPos() {
		Vector spellEndPos = *(Vector*)((DWORD)this + oMissileEndPos);
		spellEndPos.Y += 100;
		return spellEndPos;
	}
	Vector GetStartPos() {
		Vector startPos = *(Vector*)((DWORD)this + oSpellCastStart);
		startPos.Y += 120;
		return startPos;
	}
	Vector GetEndPos() {
		Vector endPos = *(Vector*)((DWORD)this + oSpellCastEnd);
		endPos.Y += 120;
		return endPos;
	}
	char* GetName() {
		return GetStr((DWORD)this + 0x18);
	}
};