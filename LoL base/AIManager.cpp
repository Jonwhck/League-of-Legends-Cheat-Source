#include "AIManager.h"
#include "Offsets.h"	

Vector* AIManager::GetNavBegin() {
	return *(Vector**)((DWORD)this + oAIMGR_NavBegin); //oAINavBegin
}

Vector* AIManager::GetNavEnd() {
	return (Vector*)((DWORD)this + oAIMGR_NavEnd); //oAINavEnd
}

Vector AIManager::GetVelocity() {
	return *(Vector*)((DWORD)this + oAIMGR_Velocity); //oAIVelocity
}

Vector* AIManager::GetServerPos() {
	return (Vector*)((DWORD)this + oAIMGR_ServerPos); //oAIVelocity
}

bool AIManager::IsMoving() {
	return *(bool*)((DWORD)this + oAIMGR_IsMoving); //oAIisMoving
}

bool AIManager::IsDashing() {
	return *(bool*)((DWORD)this + oAIMGR_IsDashing); //oAIisMoving
}

//std::vector<Vector*> AIManager::GetPathList() {
//	std::vector<Vector*> test;
//	for (DWORD pBuffPtr = this->GetNavBegin(); pBuffPtr != this->GetNavEnd(); pBuffPtr += 0x8)
//	{
//		auto pBuff = *(Vector**)pBuffPtr;
//		if (!pBuff) continue;
//		if (pBuff) {
//			test.push_back(pBuff);
//		}
//
//	}
//	return test;
//}
