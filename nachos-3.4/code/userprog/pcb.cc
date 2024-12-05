#include "pcb.h"


PCB::PCB(int id) {

    pid = id;
    parent = NULL;
    children = new List();
    thread = NULL;
    exitStatus = -9999;
    openUserFiles = new UserOpenFile*[MAXUSERFILES];
    for (int i = 0; i < MAXUSERFILES; i++) {
        openUserFiles[i] = NULL;
    }
}



PCB::~PCB() {

    delete children;

}



void PCB::AddChild(PCB* pcb) {

    children->Append(pcb);


}


int PCB::RemoveChild(PCB* pcb){

    return children->RemoveItem(pcb);

}

void PCB::SetParent(PCB* pcb) {
    parent = pcb;
}


bool PCB::HasExited() {
    return exitStatus == -9999 ? false : true;
}


void decspn(int arg) {
    PCB* pcb = (PCB*)arg;
    if (pcb->HasExited()) pcbManager->DeallocatePCB(pcb);
    else pcb->parent = NULL;
}


void PCB::DeleteExitedChildrenSetParentNull() {
    children->Mapcar(decspn);
}

void PrintChild(int arg) {
    PCB* pcb = (PCB*)arg;
    printf("Child: [%d]\n", pcb->pid);
}

void PCB::CallPrint() {
    printf("Printing children:\n");
    children->Mapcar(PrintChild);
}

UserOpenFile* PCB::GetOpenUserFile(char* name) {
    for (int i = 0; i < MAXUSERFILES; i++) {
        if (openUserFiles[i]->GetFileName() == name) {
            return openUserFiles[i];
        }
    }
    return NULL;
}

UserOpenFile* PCB::GetOpenUserFilebyID(int i) {
    if (i < 0 || i >= MAXUSERFILES || openUserFiles[i]==NULL)
        return NULL;
    
    return openUserFiles[i];
}

OpenFile* GetOpenFile(int id) {
    return sofManager->GetOpenFile(id)->GetOpenFile();
}

int PCB::GetUserArraySize() {
    return MAXUSERFILES;
}

int PCB::FindOpenSpot() {
    for (int i = 0; i < MAXUSERFILES; i++) {
        if (openUserFiles[i] == NULL)
            return i;
    }
    return -1;      //No open spots
}

void PCB::AddUserFile(char* name, int fid, int offset, int pcbi) {
    UserOpenFile* ufile = new UserOpenFile(name, fid, offset);
    openUserFiles[pcbi] = ufile;
}

int PCB::RemoveUserFile(char* name) {
    for (int i = 0; i < MAXUSERFILES; i++) {
        if (openUserFiles[i] != NULL && openUserFiles[i]->GetFileName()==name) {
            delete openUserFiles[i];
            openUserFiles[i] = NULL;
            return i;
        }
    }
    return -1;
}