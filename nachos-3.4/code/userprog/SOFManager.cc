#include "SOFManager.h"
#include "system.h"

SOFManager::SOFManager(int maxFiles) {
    bitmap = new BitMap(maxFiles);
    openFiles = new SysOpenFile*[maxFiles];
    maxF = maxFiles;
    bitmap->Mark(1);

    for (int i = 0; i < maxFiles; i++) {
        openFiles[i] = NULL;
    }
}

SOFManager::~SOFManager() {
    delete openFiles;
    delete bitmap;
}

int SOFManager::AddFile(OpenFile* file, char* name) {//, int fileID) {
    //Acquiree Lock
    sofManagerLock->Acquire();

    int fid = bitmap->Find();

    sofManagerLock->Release();

    if (fid == -1)
        return -1;

    openFiles[fid] = new SysOpenFile(file, name, fid);
    
    return fid;
}

int SOFManager::RemoveFile(int findex) {
    if (findex < 0 || findex >= maxF)
        return -1;

    //Acquire lock
    sofManagerLock->Acquire();

    bitmap->Clear(findex);

    sofManagerLock->Release();

    delete openFiles[findex];

    openFiles[findex] = NULL;


    return 0;
}

SysOpenFile* SOFManager::GetOpenFile(int index) {
    if (index < 0 || index >= maxF)
        return NULL;
    
    return openFiles[index];
}

SysOpenFile* SOFManager::HasFile(char* name) {
    for (int i = 0; i < maxF; i++) {
        if (openFiles[i] != NULL && openFiles[i]->GetOpenFileName() == name) {
            return openFiles[i];
        }
    }
    return NULL;
}
