#include "memmain.h"

void StartMemory()
{
    manager.freeBlocks = (MemoryBlock*)manager.memory;
    manager.freeBlocks->next = NULL;
    manager.freeBlocks->size = MEMORY_POOL - BLOCK_SIZE;
    manager.freeBlocks->used = 0;

    InitVirtualMemory();
}