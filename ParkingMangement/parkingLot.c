#include "parkingLot.h"
#include "seqQueue.h"
#include "seqStack.h"
static seqQueue sidewalk=NULL;
static seqStack parkingLot=NULL;
static int pos=1;
static struct car* drivingAway(){
    if(seqStackIsEmpty(parkingLot))
        return NULL;
    pos--;
    struct car* pCar=seqStackTop(parkingLot);
    time(&pCar->endtime);
    pCar->parkingPosition=-1;
    pCar->status=LEAVING;
    seqStackPop(parkingLot);
    const char* begintime=ctime(&pCar->begintime);
    const char* endtime=ctime(&pCar->endtime);
    //printf("[ * ] Driving away a car,id is %d,name is %s.\n\tStart-time:%s\tEnd-time:%s",pCar->id,pCar->name,begintime,endtime);
    //printf("\tUsing time %lds,Cost %lf yuan.\n",pCar->endtime-pCar->begintime,(pCar->endtime-pCar->begintime)*parkingFee);
    //printf("\tStatus:%s\n",pCar->status?"PARKING":"LEAVING");
    return pCar;
}
static void waiting(struct car* pCar){
    if(seqQueueIsFull(sidewalk)){
        printf("[ ! ] ParkingLot is full,Sidewalk is full!\n");
        return;
    }
    pCar->parkingPosition=0;
    pCar->status=WAITTING;
    printf("[ - ] ParkingLot is full,the car is waiting on the Sidewalk.\n");
    seqQueueEnqueue(sidewalk,pCar);
}
static bool parking(struct car* pCar){
    if(seqStackIsFull(parkingLot))
        return false;
    time(&pCar->begintime);
    pCar->parkingPosition=pos++;
    pCar->status=ARRIVING;
    seqStackPush(parkingLot,pCar);
    //printf("[ * ] Parking a Car!On the postion %d,id is %d,name is %s.\n",parkingLot->capacity-parkingLot->top,pCar->id,pCar->name);
    return true;
}
const char* getStatus(int status){
    switch (status)
    {
    case LEAVING:
        return "LEAVING";
        break;
    case ARRIVING:
        return "ARRIVING";
        break;
    case WAITTING:
        return "WAITTING";
        break;
    default:
        break;
    }
    return "NULL";
}
void initalSidewalk(int size){
    printf("[ - ] Inital Sidewalk,size is %d.\n",size);
    seqQueueInitalize(&sidewalk,size);
}
void initalParkingLot(int size){
    printf("[ - ] Inital ParkingLot,size is %d.\n",size);
    seqStackInitalize(&parkingLot,size);
}
void freeSidewalk(){
    printf("[ - ] Close the Sidewalk.\n");
    seqQueueFree(&sidewalk);
}
void freeParkingLot(){
    printf("[ - ] Close the ParkingLot.\n");
    seqStackFree(&parkingLot);
}
void addCar(struct car* pCar){
    if(pCar==NULL)
        return;
    pCar->parkingPosition=-1;
    pCar->status=LEAVING;
    if(!parking(pCar)){
        waiting(pCar);
    }
}
struct car* removeCar(){
    struct car* pCar=drivingAway();
    struct car* pTemp=NULL;
    if(!seqQueueIsEmpty(sidewalk)){
        pTemp=seqQueueFront(sidewalk);
        seqQueueDequeue(sidewalk);
        parking(pTemp);
    }
    return pCar;
}