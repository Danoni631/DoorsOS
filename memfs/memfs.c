/*
    Credits to ArTicZera/JhoPro, to make memfs
*/

#include "../Include/stdint.h"
#include "../memory/memmain.h"

#include "memfs.h"

FileSystem* fs = (FileSystem*) FSADDRESS;

void InitFileSystem()
{
    fs = (FileSystem*) FSADDRESS;

    memset(fs, 0, sizeof(FileSystem));

    strncpy(fs->root.name, "", MAXFILENAME);

    fs->root.parent = NULL;

    // 🔥 alinhado
    fs->root.nextFreeBlock = (FSADDRESS + sizeof(FileSystem) + 3) & ~3;

    currentDir = &fs->root;
}

int CreateFile(const char* filename, const LPBYTE data, DWORD size, BYTE permissions)
{
    if (size == 0 || strlen(filename) >= MAXFILENAME)
        return -1;

    int fileIndex = -1;

    for (int i = 0; i < MAXFILES; i++)
    {
        if (currentDir->files[i].filename[0] == '\0')
        {
            fileIndex = i;
            break;
        }
    }

    if (fileIndex == -1)
        return -2;

    // 🔥 ALIGN (ESSENCIAL)
    DWORD dataOffset = (currentDir->nextFreeBlock + 3) & ~3;

    currentDir->nextFreeBlock = dataOffset + size;

    strncpy(currentDir->files[fileIndex].filename, filename, MAXFILENAME);
    currentDir->files[fileIndex].size = size;
    currentDir->files[fileIndex].dataOffset = dataOffset;
    currentDir->files[fileIndex].permissions = permissions;

    memcpy((void*)dataOffset, data, size);

    return 0;
}

int ReadFile(const char* filename, LPBYTE buffer, LPDWORD size)
{
    for (int i = 0; i < MAXFILES; i++) 
    {
        if (strncmp(currentDir->files[i].filename, filename, MAXFILENAME) == 0) 
        {
            if (!(currentDir->files[i].permissions & PERM_R))
            { 
                return -1;
            }

            *size = currentDir->files[i].size;

            if (buffer != NULL)
            {
                LPBYTE fileData = (LPBYTE) currentDir->files[i].dataOffset;
                memcpy(buffer, fileData, *size);
            }
            return 0x00;
        }
    }

    return -1;
}

int DeleteFile(const char* filename)
{
    for (int i = 0; i < MAXFILES; i++) 
    {
        if (strncmp(currentDir->files[i].filename, filename, MAXFILENAME) == 0) 
        {
            memset(currentDir->files[i].filename, 0x00, MAXFILENAME);

            currentDir->files[i].size = 0x00000000;
            currentDir->files[i].dataOffset = 0x00000000;
            currentDir->files[i].permissions = 0x00;

            return 0x00;
        }
    }

    return -1; 
}

int FindFile(const char* filename) 
{
    for (int i = 0; i < MAXFILES; i++) 
    {
        if (strncmp(currentDir->files[i].filename, filename, MAXFILENAME) == 0) 
        {
            return i;
        }
    }

    return -1;
}

int RenameFile(const char* oldFilename, const char* newFilename) 
{
    int fileIndex = FindFile(oldFilename);

    if (fileIndex == -1) 
    {
        return -1;
    }

    if (strlen(newFilename) >= MAXFILENAME) 
    {
        return -2; 
    }

    strncpy(currentDir->files[fileIndex].filename, newFilename, MAXFILENAME);

    return 0x00;
}

int MakeDir(const char* dir)
{
    if (strlen(dir) >= MAXFILENAME || dir[0] == '\0')
        return -1;

    for (int i = 0; i < MAXSUBDIR; i++)
    {
        if (currentDir->subdirs[i] == NULL)
        {
            // 🔥 ALIGN
            DWORD addr = (currentDir->nextFreeBlock + 3) & ~3;

            Directory* newDir = (Directory*) addr;

            currentDir->nextFreeBlock = addr + sizeof(Directory);

            memset(newDir, 0, sizeof(Directory));

            strncpy(newDir->name, dir, MAXFILENAME - 1);

            newDir->parent = currentDir;
            newDir->nextFreeBlock = (DWORD)newDir + sizeof(Directory);

            currentDir->subdirs[i] = newDir;

            return 0;
        }
    }

    return -2;
}

int DeleteDir(const char* dirname)
{
    for (int i = 0; i < MAXSUBDIR; i++)
    {
        if (currentDir->subdirs[i] != 0x00 && strncmp(currentDir->subdirs[i]->name, dirname, MAXFILENAME) == 0x00)
        {
            Directory* dir = currentDir->subdirs[i];

            for (int j = 0; j < MAXFILES; j++)
            {
                if (dir->files[j].filename[0] != '\0')
                {
                    return -1;
                }
            }

            for (int j = 0; j < MAXSUBDIR; j++)
            {
                if (dir->subdirs[j] != NULL)
                {
                    return -1;
                }
            }

            currentDir->subdirs[i] = NULL;

            return 0x00;
        }
    }

    return -2;
}

int ChangeDir(const char* dirname)
{
    if (strcmp(dirname, "..") == 0x00)
    {
        if (currentDir->parent != 0x00)
        {
            currentDir = currentDir->parent;

            return 0x00;
        }

        return -1;
    }

    for (int i = 0; i < MAXSUBDIR; i++)
    {
        if
        (
            currentDir->subdirs[i] != 0x00 &&
            strncmp
            (
                currentDir->subdirs[i]->name,
                dirname, MAXFILENAME
            ) == 0x00
        )
        {
            currentDir = currentDir->subdirs[i];

            return 0x00;
        }
    }

    return -2;
}

Directory* GetRootDir()
{
    return currentDir;
}