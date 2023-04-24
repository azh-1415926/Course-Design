#ifndef _PARKING_LOT_H_
#define _PARKING_LOT_H_
#include <stdio.h>
#include <time.h>
#define LEAVING 0
#define ARRIVING 1
#define WAITTING 2
struct car {
    int id;
    char name[10];
    int parkingPosition;
    int status;
    time_t begintime;
    time_t endtime;
};
const char* getStatus(int status);
void initalSidewalk(int size);
void initalParkingLot(int size);
void freeSidewalk();
void freeParkingLot();
void addCar(struct car* pCar);
struct car* removeCar();
#endif