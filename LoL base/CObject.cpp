#include "CObject.h"
#include "Hooks.h"
#include "Engine.h"
#include <iostream>

bool CObject::IsAlive() {
	return Functions.IsAlive(this) && this->GetHealth() > 0.0f; //Functions.IsAlive(this) && 
}

bool CObject::canLastHit() {
	float targetHealth = this->GetHealth(); //pObject->IsMinion() && pObject->IsAlive() && pObject->IsVisible() && pObject->IsEnemyTo(me)
	float myDamage = me->GetTotalAttackDamage();
	float targetArmor = this->GetArmor();
	float dmgReduction = 100 / (100 + targetArmor);
	return (myDamage * dmgReduction) > targetHealth;
}

bool CObject::IsMinion() {
	return Functions.IsMinion(this);
}

bool CObject::IsDrake() {
	return stristr(this->GetName(), "Dragon");
}

bool CObject::IsBaron() {
	return stristr(this->GetName(), "SRU_Baron");
}

bool CObject::IsHerald() {
	return stristr(this->GetName(), "SRU_RiftHerald");
}

bool CObject::IsWard() {
	return stristr(this->GetName(), "ward") || stristr(this->GetName(), "jammer");
}

bool CObject::IsTurret() {
	return Functions.IsTurret(this);
}

bool CObject::IsHero() {
	return CompareObjectTypeFlags((int)ObjectTypeFlags::Hero);
}

bool CObject::IsLaneMinion() {
	return stristr(this->GetName(), "Minion");
}

bool CObject::IsInvalidObject() {
	return CompareObjectTypeFlags((int)ObjectTypeFlags::InvalidObject);
}

bool CObject::IsMissile() {
	return Functions.IsMissile(this);
}

bool CObject::IsTargetable() {
	return Functions.IsTargetable(this);
}

bool CObject::IsNexus() {
	return Functions.IsNexus(this);
}

bool CObject::IsInhibitor() {
	return Functions.IsInhibitor(this);
}

bool CObject::IsTroyEnt() {
	return Functions.IsTroyEnt(this);
}

float CObject::GetDistanceToMe() {
	return this->GetPos2D().DistTo(Engine::GetLocalObject()->GetPos2D());
}


float CObject::GetAttackDelay() {
	return Functions.GetAttackDelay(this);
}

float CObject::GetAttackCastDelay() {
	return Functions.GetAttackCastDelay(this);
}

