#pragma once
#include <Windows.h>
#include "Vector.h"
#include <d3dx9.h>
#include "base.h"

#define baseAddr (DWORD)GetModuleHandle(NULL)

/*#define baseAddr (DWORD)GetModuleHandle(NULL)*/

template< typename Function > Function CallVirtual(PVOID Base, DWORD Index)
{
    PDWORD* VTablePointer = (PDWORD*)Base;
    PDWORD VTableFunctionBase = *VTablePointer;
    DWORD dwAddress = VTableFunctionBase[Index];

    return (Function)(dwAddress);
}

inline char* GetStr(DWORD offset) {

    if (*(int*)(offset + 0x10) > 15)
    {
        return (char*)(*(DWORD*)offset);
    }
    else
        return (char*)offset;
}

inline char* GetStrRIOT(DWORD offset) {
    return (char*)(*(DWORD*)offset);
}

inline float calculate2dDistance(float x1, float y1, float x2, float y2)
{
    float diffY = y1 - y2;
    float diffX = x1 - x2;
    return sqrtf((diffY * diffY) + (diffX * diffX));
}

inline float GetEffectiveHP(float Armor, float HP) {
    return HP * (100.0f + Armor) / 100.0f;
}

inline int createRGB(int r, int g, int b)
{
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

inline bool isKeyPressed(int key) {
    SHORT keyState = GetKeyState(key);
    bool isDown = keyState & 0x8000;
    return isDown;
}

inline char* stristr(const char* str1, const char* str2)
{
    const char* p1 = str1;
    const char* p2 = str2;
    const char* r = *p2 == 0 ? str1 : 0;

    while (*p1 != 0 && *p2 != 0)
    {
        if (tolower((unsigned char)*p1) == tolower((unsigned char)*p2))
        {
            if (r == 0)
            {
                r = p1;
            }

            p2++;
        }
        else
        {
            p2 = str2;
            if (r != 0)
            {
                p1 = r + 1;
            }

            if (tolower((unsigned char)*p1) == tolower((unsigned char)*p2))
            {
                r = p1;
                p2++;
            }
            else
            {
                r = 0;
            }
        }

        p1++;
    }

    return *p2 == 0 ? (char*)r : 0;
}


/*Vector World2Screen(const Vector& pos) {
    Vector out = { 0.f, 0.f };
    Vector screen = { (float)width, (float)height };
    static Vector clipCoords;
    clipCoords.x = pos.x * viewProjMatrix[0] + pos.y * viewProjMatrix[4] + pos.z * viewProjMatrix[8] + viewProjMatrix[12];
    clipCoords.y = pos.x * viewProjMatrix[1] + pos.y * viewProjMatrix[5] + pos.z * viewProjMatrix[9] + viewProjMatrix[13];
    clipCoords.z = pos.x * viewProjMatrix[2] + pos.y * viewProjMatrix[6] + pos.z * viewProjMatrix[10] + viewProjMatrix[14];
    clipCoords.w = pos.x * viewProjMatrix[3] + pos.y * viewProjMatrix[7] + pos.z * viewProjMatrix[11] + viewProjMatrix[15];

    if (clipCoords.w < 1.0f)
        clipCoords.w = 1.f;

    Vector M;
    M.x = clipCoords.x / clipCoords.w;
    M.y = clipCoords.y / clipCoords.w;
    M.z = clipCoords.z / clipCoords.w;

    out.x = (screen.x / 2.f * M.x) + (M.x + screen.x / 2.f);
    out.y = -(screen.y / 2.f * M.y) + (M.y + screen.y / 2.f);


    return out;
}*/