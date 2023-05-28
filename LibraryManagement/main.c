#include "simpleMenu.h"
#include "menuAction.h"
#include "debug.h"
#include "bookcase.h"
int main(){
    struct menuItem item[]={
        {SAME_LEVEL_MENU,"Book Search",NULL,NULL,NULL},
        {SUB_MENU,"Search all books",showallbooks,NULL,NULL},
        {SAME_LEVEL_MENU,"Search book",showbook,NULL,NULL},
        {LAST_MENU,"Back",NULL,NULL,NULL},
        {NEXT_LEVEL_MENU,"Book Management",NULL,NULL,NULL},
        {SUB_MENU,"Add books",addbook,NULL,NULL},
        {SAME_LEVEL_MENU,"Alter books",alterbook,NULL,NULL},
        {SAME_LEVEL_MENU,"Remove books",removebook,NULL,NULL},
        {LAST_MENU,"Back",NULL,NULL,NULL},
        {NEXT_LEVEL_MENU,"Library Loans",NULL,NULL,NULL},
        {SUB_MENU,"Borrow books",borrowbook,NULL,NULL},
        {SAME_LEVEL_MENU,"Return books",returnbook,NULL,NULL},
        {LAST_MENU,"Back",NULL,NULL,NULL},
        {NEXT_LEVEL_MENU,"Exit",exitMenu,NULL,NULL}
    };
    initalMenu(item,sizeof(item)/sizeof(struct menuItem));
    initalBookcase();
    int num,option;
    struct menuItem* nextMenu=item;
    while(nextMenu){
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
                //nextMenu=NULL;
                nextMenu=item;
        }     
    }
    //showMenuItems(item,sizeof(item)/sizeof(struct menuItem));
    return 0;
}