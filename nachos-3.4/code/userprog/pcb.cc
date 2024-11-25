#include "pcb.h"


PCB::PCB(int id) {

    pid = id;
    parent = NULL;
    children = new List();
    thread = NULL;
    exitStatus = -9999;

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