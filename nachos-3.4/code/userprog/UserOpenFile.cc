#include "UserOpenFile.h"

UserOpenFile::UserOpenFile(char* name, int i, int off) {
    filename = name;
    index = i;
    offset = off;
}

UserOpenFile::~UserOpenFile() {}

int UserOpenFile::GetIndex() {
    return index;
}

int UserOpenFile::GetOffset() {
    return offset;
}

char* UserOpenFile::GetFileName() {
    return filename;
}

OpenFile* UserOpenFile::GetOpenFile(int fid) {
    return sofManager->GetOpenFile(fid)->GetOpenFile();
}

void UserOpenFile::SetOffset(int size) {
    offset += size;
}