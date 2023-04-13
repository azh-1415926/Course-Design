#ifndef _MENU_ACTION_H_
#define _MENU_ACTION_H_
#define ELE_INT 1
#define ELE_CHAR 2
#define ELE_STRING 3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void getInfo(const char* title,const char* question,void* data,int size,int flag);
void showBook();
void addBook();
void alterBook();
void removeBook();
void exitMenu();
#endif