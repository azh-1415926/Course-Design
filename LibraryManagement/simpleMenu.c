#include "simpleMenu.h"
#include "linkStack.h"
void initalMenu(struct menuItem* menu,int size){
    struct menuItem* parentMenu=menu;
    struct menuItem* preMenu=NULL;
    struct menuItem* curMenu=menu;
    linkStack parentStack;
    linkStackInitalize(&parentStack);
    for(int i=0;i<size;i++){
        curMenu=&menu[i];
        if(preMenu==NULL)
            curMenu->flag=SAME_LEVEL_MENU;
        switch (curMenu->flag)
        {
        case SAME_LEVEL_MENU:
            if(preMenu!=NULL){
                preMenu->brother=curMenu;
                preMenu->flag=NO_SUB_MENU;
            }   
            break;
        case SUB_MENU:
            linkStackPush(parentStack,parentMenu);
            parentMenu=preMenu;
            parentMenu->flag=SUB_MENU;
            parentMenu->next=curMenu;
            break;
        case LAST_MENU:
            preMenu->flag=NO_SUB_MENU;
            preMenu->brother=curMenu;
            if(!linkStackIsEmpty(parentStack)){
                curMenu->flag=PRE_LEVEL_MENU;
                parentMenu=linkStackTop(parentStack);
                linkStackPop(parentStack);
            }else
                curMenu->flag=SAME_LEVEL_MENU;
            curMenu->next=parentMenu;
            break;
        case LAST_SUB_MENU:
            preMenu->flag=SUB_MENU;
            preMenu->next=curMenu;
            curMenu->flag=PRE_LEVEL_MENU;
            curMenu->next=parentMenu;
            if(preMenu==parentMenu)
                curMenu->flag=SAME_LEVEL_MENU;
            break;
        case NEXT_LEVEL_MENU:
            preMenu=parentMenu;
            while(preMenu->brother)
                preMenu=preMenu->brother;
            preMenu->brother=curMenu;
            break;
        default:
            break;
        }
        if(i==size-1){
            curMenu->flag=SAME_LEVEL_MENU;
            if(!linkStackIsEmpty(parentStack)){
                curMenu->flag=PRE_LEVEL_MENU;
                parentMenu=linkStackTop(parentStack);
                linkStackPop(parentStack);
            }
            curMenu->next=parentMenu;
        }
        preMenu=curMenu;
    }
    linkStackFree(&parentStack);
}
int showBrotherMenu(struct menuItem* menu){
    struct menuItem* curMenu=menu;
    int i=0;
    printf("-----------LibraryMangement-----------\n");
    while(curMenu!=NULL){
        printf("\t[ %d ]     %s\n",i+1,curMenu->name);
        i++;
        curMenu=curMenu->brother;
    }
    return i;
}
int getOption(int minnum,int maxnum){
    if(maxnum<minnum)
        return 0;
    int option;
    printf("Please enter:");
    scanf("%d",&option);
    while(option<minnum||option>maxnum){
        scanf("%*s");
        printf("error!Please enter incorrect option!\nenter:");
        scanf("%d",&option);
    }
    return option-1;
}	
struct menuItem* jumpNextMenu(struct menuItem* menu,int pos){
    struct menuItem* curMenu=menu;
    int i=0;
    while(curMenu!=NULL&&i++<pos){
        if(curMenu->brother!=NULL)
            curMenu=curMenu->brother;
        else
            break;
    }
    return curMenu;
}
struct menuItem* jumpPreMenu(struct menuItem* menu){
    struct menuItem* curMenu=menu;
    while(curMenu&&curMenu->brother)
        curMenu=curMenu->brother;
    if(curMenu&&curMenu->flag==PRE_LEVEL_MENU)
        return curMenu->next;
    return NULL;
}
void executeAction(struct menuItem* menu){
    if(menu&&menu->handle)
        (menu->handle)();
}
