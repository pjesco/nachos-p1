#include "SysOpenFile.h"

SysOpenFile::SysOpenFile(OpenFile* file, char* name, int id) {
    of = file;
    FileID = id;
    fileName = name;
    readers = 0;
}

SysOpenFile::~SysOpenFile() {}

OpenFile* SysOpenFile::GetOpenFile() {
    return of;
}

char* SysOpenFile::GetOpenFileName() {
    return fileName;
}

void SysOpenFile::AddReader() {
    readers++;
}

void SysOpenFile::RemoveReader() {
    readers--;
}

int SysOpenFile::GetReaders() {
    return readers;
}

int SysOpenFile::GetFileID() {
    return FileID;
}