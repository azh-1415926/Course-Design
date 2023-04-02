#include "menuAction.h"
#include "parkingLot.h"
static int id=0;
static void getInfo(const char* title,const char* question,void* data,int size,int flag){
    printf("\t%s\n",title);
    printf("%s\n",question);
    fflush(stdin);
    switch(flag){
        case ELE_INT:
            scanf("%d",(int*)data);
            break;
        case ELE_CHAR:
            scanf("%c",(char*)data);
            break;
        case ELE_STRING:
            memset(data,0,size);
            scanf("%s",(char*)data);
            break;
        default:
            printf("no that option.\n");
    }
    fflush(stdin);
}
void addCars(){
    int count;
    char buf[10];
    getInfo("Add Cars","How many cars do you want to add?",&count,0,ELE_INT);
    struct car* pCar=NULL;
    for(int i=0;i<count;i++){
        pCar=(struct car*)malloc(sizeof(struct car));
        printf("This is the %d car!\n",i+1);
        pCar->id=++id;
        getInfo("Car Name","What is the car's name?",buf,sizeof(buf),ELE_STRING);
        strcpy(pCar->name,buf);
        addCar(pCar);
    }
}
void removeCars(){
    int count;
    getInfo("Add Cars","How many cars do you want to remove?",&count,0,ELE_INT);
    struct car* pCar=NULL;
    for(int i=0;i<count;i++){
        pCar=removeCar();
        if(pCar)
            free(pCar);
    }
}
void clearAllCars(){
    struct car* pCar=NULL;
    while((pCar=removeCar()))
        free(pCar);
    printf("Clear all the cars!\n");
}
void exitMenu(){
    struct car* pCar=NULL;
    while((pCar=removeCar()))
        free(pCar);
    printf("Exit!\n");
    exit(0);
}