#pragma once
#include "Utils.h"
class SpellData
{
public:

	float GetSpellWidth() {
		return *(float*)(DWORD)this + 0x488;
	}
	char* GetMissileName() {
		return GetStrRIOT((DWORD)this + oSpellDataSpellName);
	}
	char* GetSpellName() {
		return GetStrRIOT((DWORD)this + oSpellDataSpellName);
	}
	char* GetDescription() {
		return GetStr((DWORD)this + 0x0088);
	}
	float GetEffectAmount() {
		return *(float*)((DWORD)this + 0xD0);
	}
	float GetIncreaseDamage() {
		return *(float*)((DWORD)this + 0xEC);
	}
	float GetSpellDuration() {
		return *(float*)((DWORD)this + 0x108);
	}
	float GetRootDuration() {
		return *(float*)((DWORD)this + 0x15C);
	}
	float GetIncreaseDamageBonus() {
		return *(float*)((DWORD)this + 0x178);
	}
	float GetCoefficient() {
		return *(float*)((DWORD)this + 0x1D4);
	}
	float GetCoefficient2() {
		return *(float*)((DWORD)this + 0x1D8);
	}
	int GetMaxHighlightTargets() {
		return *(int*)((DWORD)this + 0x1DC);
	}
	float GetCooldownTime() {
		return *(float*)((DWORD)this + 0x280);
	}
	float GetMissileLineWidth()
	{
		return  *(float*)((DWORD)this + 0x44C);
	}
	float GetDelayCastOffsetPercent() {
		return *(float*)((DWORD)this + 0x26C);
	}
	float GetDelayTotalTimePercent() {
		return *(float*)((DWORD)this + 0x2A0);
	}
	int GetMaxAmmo() {
		return *(int*)((DWORD)this + 0x31C);
	}
	int GetAmmoUsed() {
		return *(int*)((DWORD)this + 0x338);
	}
	float GetAmmoRechargeTime() {
		return *(float*)((DWORD)this + 0x354);
	}
	float GetMissileSpeed() {
		return *(float*)((DWORD)this + 0x454);
	}
	float GetMaxCooldown()
	{
		return  *(float*)((DWORD)this + 0x25C);
	}
	short GetCasterIndex() {
		return *(short*)((DWORD)this + oObjIndex);
	}
	float GetSpellRange()
	{
		return *(float*)((DWORD)this + 0x3c8); // 0x3B4
	}
	float GetSpellRadius()
	{
		return *(float*)((DWORD)this + 0x458);
	}
	float GetManaCostByLevel(unsigned int level)
	{
		if (level > 4) {
			return 0.f;
		}
		return *(float*)((DWORD)this + 0x4FC + ((level - 1) * 0x4));
	}
};