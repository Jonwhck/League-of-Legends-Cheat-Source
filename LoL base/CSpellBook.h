#pragma once
#include <Windows.h>
#include "Offsets.h"
#include "Vector.h"
#include "Utils.h"
#include "SpellSlot.h"

class CSpellBook {
public:

	SpellSlot* GetSpellSlotByID(int ID) {
		return *(SpellSlot**)((DWORD)this + oSpellBookSpellSlots + (0x4 * ID));

	}

	SpellInfo* GetActiveSpellEntry() {
		return *(SpellInfo**)((DWORD)this + oSpellBookActiveSpellCast);
	}

};
