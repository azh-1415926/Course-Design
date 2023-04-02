#ifndef _SIMPLE_MENU_H_
#define _SIMPLE_MENU_H_
#include <stdio.h>
#define SAME_LEVEL_MENU 0
#define PRE_LEVEL_MENU 1
#define NEXT_LEVEL_MENU 2
#define LAST_MENU -1
#define NO_SUB_MENU -2
#define SUB_MENU -3
#define LAST_SUB_MENU -4
struct menuItem {
    int flag;
    const char* name;
    void (*handle)(void);
    struct menuItem* brother;
    struct menuItem* next;
};
void initalMenu(struct menuItem* menu,int size);
int showBrotherMenu(struct menuItem* menu);
int getOption(int minnum,int maxnum);
struct menuItem* jumpNextMenu(struct menuItem* menu,int pos);
struct menuItem* jumpPreMenu(struct menuItem* menu);
void executeAction(struct menuItem* menu);
#endif