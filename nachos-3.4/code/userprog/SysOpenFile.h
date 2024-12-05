#ifndef SYSOPENFILE_H
#define SYSOPENFILE_H

#include "filesys.h"
#include "SOFManager.h"

class SOFManager;
extern SOFManager* sofManager;

class SysOpenFile {
    public:
        SysOpenFile(OpenFile*, char*, int);
        ~SysOpenFile();
        OpenFile* GetOpenFile();
        char* GetOpenFileName();
        void AddReader();
        void RemoveReader();
        int GetReaders();
        int GetFileID();

    private:
        int FileID;
        char* fileName;
        OpenFile* of;
        int readers;

};

#endif