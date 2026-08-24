#include "memmain.h"

void EnablePaging()
{
    asm volatile
    (
        "mov %cr4, %ebx \n"
        "or $0x10, %ebx \n"
        "mov %ebx, %cr4 \n"

        "mov %cr0, %ebx \n"
        "or $0x80000000, %ebx \n"
        "mov %ebx, %cr0 \n"
    );
}

void* AllocateMemory(unsigned int size)
{
    MemoryBlock* block = manager.freeBlocks;
    MemoryBlock* prev = NULL;

    size = (size + BLOCK_SIZE - 1) / BLOCK_SIZE * BLOCK_SIZE;

    while (block) 
    {
        if (!block->used && block->size >= size) 
        {
            if (block->size > size + BLOCK_SIZE) 
            {
                MemoryBlock* newBlock = (MemoryBlock*)((BYTE*)block + BLOCK_SIZE + size);
                newBlock->size = block->size - size - BLOCK_SIZE;
                newBlock->used = 0;
                newBlock->next = block->next;

                block->next = newBlock;
                block->size = size;
            }
            
            block->used = 1;
            return (BYTE*)block + BLOCK_SIZE;

        }

        prev = block;
        block = block->next;
    }

    return NULL;
}

void* C_Allocate(int number, int size)
{
    int total = number * size;

    void* ptr = AllocateMemory(total);

    if (!ptr)
    {
        return NULL;
    }

    memset(ptr, 0x00, total);

    return ptr;
}

void* ReAllocate(void* ptr, unsigned int newsize)
{
    if(ptr == NULL)
    {
        return AllocateMemory(newsize);
    }

    if(newsize == 0)
    {
        FreeMemory(ptr);
        return NULL;
    }

    MemoryBlock* block = (MemoryBlock*)((BYTE*)ptr - BLOCK_SIZE);

    #define ALIGN 4

    newsize = (newsize + ALIGN - 1) & ~(ALIGN - 1);

    if(block->size >= newsize)
    {
        return ptr;
    }

    MemoryBlock* next = block->next;

    if
    (
        next && !next->used &&
        (block->size + BLOCK_SIZE + next->size)
        >= newsize
    )
    {
        block->size += BLOCK_SIZE + next->size;
        block->next = next->next;

        return ptr;
    }

    void* newPtr = AllocateMemory(newsize);

    if(newPtr == NULL)
    {
        return NULL;
    }

    memcpy(newPtr, ptr, block->size);

    FreeMemory(ptr);

    return newPtr;
}

void FreeMemory(void* ptr)
{
    if (!ptr) return;

    MemoryBlock* block = (MemoryBlock*)((BYTE*)ptr - BLOCK_SIZE);
    block->used = 0;

    MemoryBlock* current = manager.freeBlocks;

    while (current) 
    {
        if
        (
            (BYTE*)current + BLOCK_SIZE
            + current->size == (BYTE*)block
        ) 
        {
            current->size += BLOCK_SIZE + block->size;
            current->next = block->next;
            
            return;
        }

        if
        (
            (BYTE*)block + BLOCK_SIZE +
            block->size == (BYTE*)current
        )
        {
            block->size += BLOCK_SIZE + current->size;
            block->next = current->next;

            if (manager.freeBlocks == current) 
            {
                manager.freeBlocks = block;
            }
            
            return;
        }

        current = current->next;
    }

    block->next = manager.freeBlocks;
    manager.freeBlocks = block;
}