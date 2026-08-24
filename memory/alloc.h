void* AllocateMemory(unsigned int size);
void FreeMemory(void* ptr);
void* C_Allocate(int number, int size);
void* ReAllocate(void* ptr, unsigned int newsize);
void EnablePaging();