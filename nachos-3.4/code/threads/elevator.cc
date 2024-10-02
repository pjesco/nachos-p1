#include "copyright.h"
#include "system.h"
#include "synch.h"
#include "elevator.h"


int nextPersonID = 1;
Lock *personIDLock = new Lock("PersonIDLock");


ELEVATOR *e;


void ELEVATOR::start() {

    while(1) {

        // A. Wait until hailed
                //printf("Current Floor: %d\n", currentFloor);
        // B. While there are active persons, loop doing the following
        //      0. Acquire elevatorLock
                //printf("Acquiring lock\n");
                elevatorLock->Acquire();
                //printf("Lock acquired\n");
        //      1. Signal persons inside elevator to get off (leaving->broadcast(elevatorLock))
                //printf("Signaling leavers\n");
                leaving[currentFloor-1]->Broadcast(elevatorLock);
        //      2. Signal persons atFloor to get in, one at a time, checking occupancyLimit each time
                //printf("Signaling enters\n");
                entering[currentFloor-1]->Broadcast(elevatorLock);
        //      2.5 Release elevatorLock
                //printf("Releasing lock\n");
                elevatorLock->Release();
        //      3. Spin for some time
                //printf("Lock released\n");
                for(int j =0 ; j< 1000000; j++) {
                    currentThread->Yield();
                }
        //      4. Go to next floor
                //printf("Floor change incoming\n");
                if (direction) {
                    if (currentFloor == _numFloors) {
                        direction = false;
                        currentFloor--;
                    } else {
                        currentFloor++;
                    }
                } else {
                    if (currentFloor == 1) {
                        direction = true;
                        currentFloor++;
                    } else {
                        currentFloor--;
                    }
                }
        //  printf("Elevator arrives on floor %d", )
                printf("Elevator arrives on floor %d\n", currentFloor);
    }
}

void ElevatorThread(int numFloors) {

    printf("Elevator with %d floors was created!\n", numFloors);

    e = new ELEVATOR(numFloors);

    e->start();


}

ELEVATOR::ELEVATOR(int numFloors) {
    currentFloor = 1;
    _numFloors = numFloors;
    entering = new Condition*[numFloors];
    // Initialize entering
    for (int i = 0; i < numFloors; i++) {
        entering[i] = new Condition("Entering " + i);
    }
    personsWaiting = new int[numFloors];
    elevatorLock = new Lock("ElevatorLock");

    // Initialize leaving
    leaving = new Condition*[numFloors];
    for (int i = 0; i < numFloors; i++) {
        leaving[i] = new Condition("Leaving " + i);
    }
}


void Elevator(int numFloors) {
    // Create Elevator Thread
    Thread *t = new Thread("Elevator");
    t->Fork(ElevatorThread, numFloors);
}


void ELEVATOR::hailElevator(Person *p) {
    //printf("Begin Hail\n");
    // 1. Increment waiting persons atFloor
    personsWaiting[p->atFloor-1]++;
    ///printf("Increment personWaiting\n");
    // 2. Hail Elevator
    // 2.5 Acquire elevatorLock;
    //printf("About to Acquire Lock\n");
    elevatorLock->Acquire();
    //totalWaiting++;
    //printf("Lock Acquired\n");
    // 3. Wait for elevator to arrive atFloor [entering[p->atFloor]->wait(elevatorLock)]
    //printf("Waiting at atFloor\n");
    entering[p->atFloor-1]->Wait(elevatorLock);
    //printf("Elevator Arrived at wating floor\n");
    // 5. Get into elevator
    printf("Person %d got into the elevator.\n", p->id);
    //printf("Entered elevator\n");
    // 6. Decrement persons waiting atFloor [personsWaiting[atFloor]++]
    personsWaiting[p->atFloor-1]--;
    // 7. Increment persons inside elevator [occupancy++]
    //totalWaiting--;
    occupancy++;
    // 8. Wait for elevator to reach toFloor [leaving[p->toFloor]->wait(elevatorLock)]
    leaving[p->toFloor-1]->Wait(elevatorLock);
    //printf("Arrived at toFloor\n");
    // 9. Get out of the elevator
    printf("Person %d got out of the elevator.\n", p->id);
    // 10. Decrement persons inside elevator
    occupancy--;
    // 11. Release elevatorLock;
    //printf("About to release lock\n");
    elevatorLock->Release();
    //printf("Lock released\n");
}

void PersonThread(int person) {

    Person *p = (Person *)person;

    printf("Person %d wants to go from floor %d to %d\n", p->id, p->atFloor, p->toFloor);

    e->hailElevator(p);

}

int getNextPersonID() {
    int personID = nextPersonID;
    personIDLock->Acquire();
    nextPersonID = nextPersonID + 1;
    personIDLock->Release();
    return personID;
}


void ArrivingGoingFromTo(int atFloor, int toFloor) {


    // Create Person struct
    Person *p = new Person;
    p->id = getNextPersonID();
    p->atFloor = atFloor;
    p->toFloor = toFloor;

    // Creates Person Thread
    Thread *t = new Thread("Person " + p->id);
    t->Fork(PersonThread, (int)p);

}