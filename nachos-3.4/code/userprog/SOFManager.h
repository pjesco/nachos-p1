#ifndef SOFMANAGER_H
#define SOFMANAGER_H

#include "SysOpenFile.h"
#include "list.h"
#include "bitmap.h"

class SysOpenFile;

class SOFManager {
    public:
        SOFManager(int);
        ~SOFManager();
        int AddFile(OpenFile*, char*);
        int RemoveFile(int);
        SysOpenFile* GetOpenFile(int);
        SysOpenFile* HasFile(char*);

    private:
        SysOpenFile** openFiles;
        BitMap* bitmap;
        int maxF;
};

#endif