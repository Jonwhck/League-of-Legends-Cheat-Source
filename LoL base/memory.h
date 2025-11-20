#pragma once
template <class T> static
T readMem(uintptr_t address)
{
    //T buffer{ };
    //if (ReadProcessMemory(GetCurrentProcess(), (LPVOID)address, &buffer, sizeof(T), 0))
    //    return buffer;
    ////if (!IsBadReadPtr(reinterpret_cast<void*>(address), sizeof(T)))
    ////    return *reinterpryet_cast<T*>(address);

    T buffer{ };
    if (ReadProcessMemory(GetCurrentProcess(), (LPVOID)address, &buffer, sizeof(T), 0))
        return buffer;

    //__try {
    //    return *(T*)(address);
    //}
    //__except (EXCEPTION_EXECUTE_HANDLER) {
    //    return T{};
    //}
}

template <class T> static
bool writeMem(uintptr_t address, T* buffer, SIZE_T sizeh)
{
    if (address > 0x7FFFFFFFFFFF || address < 1) return 0;
    WriteProcessMemory(GetCurrentProcess(), (LPVOID)address, buffer, sizeh, 0);

    //__try {
    //    *(T*)(address) = buffer;
    //    return true;
    //}
    //__except (EXCEPTION_EXECUTE_HANDLER) { return FALSE; }
}