#include <myTools/debug.h>
const char* flagToString(int num){
    switch (num)
    {
    case 0:
        return "SAME_LEVEL_MENU";
    case 1:
        return "PRE_LEVEL_MENU";
    case 2:
        return "NEXT_LEVEL_MENU";
    case -1:
        return "LAST_MENU";
    case -2:
        return "NO_SUB_MENU";
    case -3:
        return "SUB_MENU";
    case -4:
        return "LAST_SUB_MENU";
    }
    return "NULL";
}
void showMenuItems(struct menuItem* menu,int size){
    struct menuItem* curMenu=menu;
    for(int i=0;i<size;i++){
        curMenu=&menu[i];
        printf("flag:%s,name:%s,brother:%p,next:%p,self:%p\n",flagToString(curMenu->flag),curMenu->name,curMenu->brother,curMenu->next,curMenu);
    }
        
}