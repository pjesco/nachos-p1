#ifndef PCB_H
#define PCB_H

#include "list.h"
#include "pcbmanager.h"

class Thread;
class PCBManager;
extern PCBManager* pcbManager;

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

    private:
        List* children;

};

#endif // PCB_H