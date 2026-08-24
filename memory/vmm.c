#include "memmain.h"

VIRTUAL_MEMORY_MANAGER vmm;

void InitVirtualMemory()
{
    for (int i = 0; i < TOTAL_PAGES; i++)
    {
        vmm.pageTable[i].physicalAddress = 0;
        vmm.pageTable[i].present = 0;
        vmm.pageTable[i].writable = 0;
        vmm.pageTable[i].user = 0;
    }
}

int MapPage
(
    DWORD virtualaddr,
    uint32_t physicaladdr,
    UCHAR writable,
    BYTE user
)
{
    DWORD pageIndex = virtualaddr / PAGE_SIZE;

    if (pageIndex >= TOTAL_PAGES) 
    {
        return -1;
    }

    vmm.pageTable[pageIndex].physicalAddress = physicaladdr;
    vmm.pageTable[pageIndex].present = 1;
    vmm.pageTable[pageIndex].writable = writable;
    vmm.pageTable[pageIndex].user = user;

    return 0;
}

void UnmapPage(DWORD virtualaddr)
{
    DWORD pageIndex = virtualaddr / PAGE_SIZE;

    if (pageIndex < TOTAL_PAGES) 
    {
        vmm.pageTable[pageIndex].present = 0;
    }
}

DWORD TranslateAddress(DWORD virtualaddr)
{
    DWORD pageIndex = virtualaddr / PAGE_SIZE;
    DWORD offset = virtualaddr % PAGE_SIZE;

    if
    (
        pageIndex >= TOTAL_PAGES ||
        !vmm.pageTable[pageIndex].present
    ) 
    {
        return 0;
    }

    return vmm.pageTable[pageIndex].physicalAddress + offset;
}

void* AllocVirtualMemory
(
    DWORD virtualaddr,
    DWORD size,
    BYTE writable,
    BYTE user
)
{
    DWORD pages = (size + PAGE_SIZE - 1) / PAGE_SIZE;

    for (DWORD i = 0; i < pages; i++) 
    {
        DWORD pageIndex = (virtualaddr / PAGE_SIZE) + i;
        
        if (pageIndex >= TOTAL_PAGES) 
        {
            return NULL;
        }

        DWORD physicalAddress =
        (DWORD)&vmm.physicalMemory[pageIndex * PAGE_SIZE];
        MapPage(virtualaddr + i * PAGE_SIZE, physicalAddress, writable, user);
    }

    return (void*)virtualaddr;
}

void FreeVirtualMemory(DWORD virtualaddr, UINT size)
{
    uint32_t pages = (size + PAGE_SIZE - 1) / PAGE_SIZE;

    for (uint32_t i = 0; i < pages; i++) 
    {
        UnmapPage(virtualaddr + i * PAGE_SIZE);
    }
}

int SetMemoryProtection
(
    DWORD virtualaddr,
    UINT size,
    BYTE protectionFlags
)
{
    DWORD pages = (size + PAGE_SIZE - 1) / PAGE_SIZE;
    DWORD pageIndex = virtualaddr / PAGE_SIZE;

    for (DWORD i = 0; i < pages; i++) 
    {
        DWORD currentPage = pageIndex + i;

        if (currentPage >= TOTAL_PAGES) 
        {
            return -1;
        }

        if (!vmm.pageTable[currentPage].present) 
        {
            return -1;
        }

        vmm.pageTable[currentPage].writable =
        (protectionFlags & USER_PROT) ? 1 : 0;
        
        vmm.pageTable[currentPage].user =
        (protectionFlags & USER_PROT) ? 1 : 0;
    }

    return 0;
}