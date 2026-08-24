#include "../include/stdint.h"

void InitVirtualMemory();

int MapPage
(
    DWORD virtualaddr,
    uint32_t physicaladdr,
    UCHAR writable,
    BYTE user
);

void UnmapPage(DWORD virtualaddr);
DWORD TranslateAddress(DWORD virtualaddr);

void* AllocVirtualMemory
(
    DWORD virtualaddr,
    DWORD size,
    BYTE writable,
    BYTE user
);

void FreeVirtualMemory(DWORD virtualaddr, UINT size);

int SetMemoryProtection
(
    DWORD virtualaddr,
    UINT size,
    BYTE protectionFlags
);