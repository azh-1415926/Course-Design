#include "simpleMenu.h"
#include "menuAction.h"
#include "debug.h"
#include "bookcase.h"
int main(){
    struct menuItem item[]={
        {SAME_LEVEL_MENU,"Book Search",NULL,NULL,NULL},
        {SAME_LEVEL_MENU,"Book Management",NULL,NULL,NULL},
        {SUB_MENU,"Add books",addBook,NULL,NULL},
        {SAME_LEVEL_MENU,"Alter books",NULL,NULL,NULL},
        {SAME_LEVEL_MENU,"Remove books",NULL,NULL,NULL},
        {SAME_LEVEL_MENU,"Clear all the books",NULL,NULL,NULL},
        {LAST_MENU,"Back",NULL,NULL,NULL},
        {NEXT_LEVEL_MENU,"Library Loans",NULL,NULL,NULL},
        {SUB_MENU,"Borrow books",NULL,NULL,NULL},
        {SAME_LEVEL_MENU,"Return books",NULL,NULL,NULL},
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
                nextMenu=NULL;
        }     
    }
    showMenuItems(item,sizeof(item)/sizeof(struct menuItem));
    return 0;
}