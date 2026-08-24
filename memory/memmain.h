#include "memdefs.h"
#include "mem.h"
#include "alloc.h"
#include "vmm.h"

MemoryManager manager;

void StartMemory();
void InitMemory(DWORD memoryhigh, DWORD PhysicalAllocStart);