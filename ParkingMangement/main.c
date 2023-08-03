#include <myTools/simpleMenu.h>
#include "menuAction.h"
#include "parkingLot.h"
#include <myTools/debug.h>
int main(){
    struct menuItem item[]={
        {SAME_LEVEL_MENU,"Parking Management",NULL,NULL,NULL},
        {SUB_MENU,"Add car",addCars,NULL,NULL},
        {SAME_LEVEL_MENU,"Remove car",removeCars,NULL,NULL},
        {SAME_LEVEL_MENU,"Clear all the car",clearAllCars,NULL,NULL},
        {NEXT_LEVEL_MENU,"Exit",exitMenu,NULL,NULL}
    };
    initalMenu(item,sizeof(item)/sizeof(struct menuItem));
    initalSidewalk(10);
    initalParkingLot(5);
    int num,option;
    struct menuItem* nextMenu=item;
    while(nextMenu){
        printf("---------------Menu---------------\n");
        num=showBrotherMenu(nextMenu);
        option=getOption(1,num);
        nextMenu=jumpNextMenu(nextMenu,option);
        if(nextMenu&&nextMenu->flag==SUB_MENU)
            nextMenu=nextMenu->next;
        else if(nextMenu){
            executeAction(nextMenu);
            if(nextMenu->flag==PRE_LEVEL_MENU)
                nextMenu=nextMenu->next;
            else
                nextMenu=item;
        }     
    }
    struct car* pCar=NULL;
    while((pCar=removeCar()))
        free(pCar);
    freeSidewalk();
    freeParkingLot();   
    showMenuItems(item,sizeof(item)/sizeof(struct menuItem));
    return 0;
}