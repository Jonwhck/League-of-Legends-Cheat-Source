#pragma once
#include "Offsets.h"
#include "Utils.h"

#include <Windows.h>
#include "Vector.h"
#include <vector>

class AIManager
{
public:
	Vector* GetNavBegin();

	Vector* GetNavEnd();

	Vector GetVelocity();

	Vector* GetServerPos();

	bool IsMoving();

	bool IsDashing();
	//std::vector<Vector*> GetPathList();
};
