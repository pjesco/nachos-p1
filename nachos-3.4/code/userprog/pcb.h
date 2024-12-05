#ifndef PCB_H
#define PCB_H

#include "list.h"
#include "pcbmanager.h"
#include "UserOpenFile.h"
#include "SOFManager.h"

#define MAXUSERFILES 40

class Thread;
class PCBManager;
extern PCBManager* pcbManager;
class UserOpenFile;

class PCB {

    public:
        PCB(int id);
        ~PCB();
        int pid;
        PCB* parent;
        Thread* thread;
        int exitStatus;

        void AddChild(PCB* pcb);
        int RemoveChild(PCB* pcb);
        void SetParent(PCB* pcb);
        bool HasExited();
        void DeleteExitedChildrenSetParentNull();
        void CallPrint();
        void AddUserFile(char*, int, int, int);
        int RemoveUserFile(char*);
        UserOpenFile* GetOpenUserFile(char*);
        UserOpenFile* GetOpenUserFilebyID(int);
        int GetUserArraySize();
        int FindOpenSpot();

    private:
        List* children;
        UserOpenFile** openUserFiles;

};

#endif // PCB_H