#ifndef USEROPENFILE_H
#define USEROPENFILE_H

#include "SOFManager.h"

class PCB;

class UserOpenFile {
    public:
        UserOpenFile(char*, int, int);
        ~UserOpenFile();
        int GetIndex();
        int GetOffset();
        void SetOffset(int);
        char* GetFileName();
        OpenFile* GetOpenFile(int);

    private:
        char* filename;
        int index;
        int offset;
};

#endif