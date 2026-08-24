#include "../include/stdint.h"

#define PAGE_SIZE 4096
#define TOTAL_PAGES 1024
#define VIRTUAL_MEMORY_SIZE (PAGE_SIZE * TOTAL_PAGES)

#define BLOCK_SIZE sizeof(MemoryBlock)

typedef enum
{
    READ_PROT = 0x1,
    WRITE_PROT = 0x2,
    EXECUTE_PROT = 0x4,
    USER_PROT = 0x8
} PROT;

typedef struct PAGE_TABLE_ENTRY
{
    DWORD physicalAddress;
    BYTE present;
    BYTE writable;
    BYTE user;
} PAGE_TABLE_ENTRY;

typedef struct VIRTUAL_MEMORY_MANAGER 
{
    PAGE_TABLE_ENTRY pageTable[TOTAL_PAGES];
    BYTE physicalMemory[TOTAL_PAGES * PAGE_SIZE];
} VIRTUAL_MEMORY_MANAGER;

#define MEMORY_POOL 0xF00000

typedef struct MemoryBlock
{
    struct MemoryBlock* next;
    DWORD size;
    BYTE used;
} MemoryBlock;

typedef struct
{
    MemoryBlock* freeBlocks;
    BYTE memory[MEMORY_POOL];
} MemoryManager;