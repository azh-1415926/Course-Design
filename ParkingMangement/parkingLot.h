#ifndef _PARKING_LOT_H_
#define _PARKING_LOT_H_
#include <stdio.h>
#include <time.h>
#define LEAVING 0
#define ARRIVING 1
struct car {
    int id;
    char name[10];
    int parkingPosition;
    int status;
    time_t begintime;
    time_t endtime;
};
void initalSidewalk(int size);
void initalParkingLot(int size,double fee);
void freeSidewalk();
void freeParkingLot();
void addCar(struct car* pCar);
struct car* removeCar();
#endif