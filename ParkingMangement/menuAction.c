#include "menuAction.h"
#include "parkingLot.h"
static int id=0;
static double fee=5.0;
// static void getInfo(const char* title,const char* question,void* data,int size,int flag){
//     printf("\t%s\n",title);
//     printf("%s\n",question);
//     fflush(stdin);
//     switch(flag){
//         case ELE_INT:
//             scanf("%d",(int*)data);
//             break;
//         case ELE_CHAR:
//             scanf("%c",(char*)data);
//             break;
//         case ELE_STRING:
//             memset(data,0,size);
//             scanf("%s",(char*)data);
//             break;
//         default:
//             printf("no that option.\n");
//     }
//     fflush(stdin);
// }
static void showCar(struct car* pCar){
    printf("[ * ] The Car's id is %d,name is %s.\n\t",pCar->id,pCar->name);
    printf("Status: %s \n",getStatus(pCar->status));
}
static void showBill(struct car* pCar){
    time_t costTime=pCar->endtime-pCar->begintime;
    printf("\tBegin at: %s \t",ctime(&pCar->begintime));
    printf("End at: %s \t",ctime(&pCar->endtime));
    printf("Cost time: %d s\t",costTime);
    printf("Fee: %.2lf $\n",costTime*fee);
}
void addCars(){
    int count;
    printf("[ - ] Add Cars\n\t");
    printf("How many cars do you want to add?\n\t");
    while(!scanf("%d",&count)){
        printf("\tError,please enter again!\n\t");
        scanf("%*s");
    }
    //getInfo("Add Cars","How many cars do you want to add?",&count,0,ELE_INT);
    struct car* pCar=NULL;
    for(int i=0;i<count;i++){
        pCar=(struct car*)malloc(sizeof(struct car));
        printf("[ - ] This is the %d car!\n",i+1);
        pCar->id=++id;
        //getInfo("Car Name","What is the car's name?",buf,sizeof(buf),ELE_STRING);
        printf("--- Car Name\n\t");
        printf("What is the car's name\n\t");
        scanf("%s",&pCar->name);
        addCar(pCar);
        showCar(pCar);
    }
}
void removeCars(){
    int count;
    //getInfo("Add Cars","How many cars do you want to remove?",&count,0,ELE_INT);
    printf("[ - ] Remove Cars\n\t");
    printf("How many cars do you want to remove?\n\t");
    while(!scanf("%d",&count)){
        printf("\tError,please enter again!\n\t");
        scanf("%*s");
    }
    struct car* pCar=NULL;
    for(int i=0;i<count;i++){
        pCar=removeCar();
        if(pCar){
            showCar(pCar);
            showBill(pCar);
            free(pCar);
        } 
    }
}
void clearAllCars(){
    struct car* pCar=NULL;
    while((pCar=removeCar())){
        showCar(pCar);
        showBill(pCar);
        free(pCar);
    }   
    printf("Clear all the cars!\n");
}
void exitMenu(){
    struct car* pCar=NULL;
    while((pCar=removeCar())){
        showCar(pCar);
        showBill(pCar);
        free(pCar);
    }
    freeSidewalk();
    freeParkingLot(); 
    printf("Exit!\n");
    exit(0);
}