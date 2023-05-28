#ifndef _MENU_ACTION_H_
#define _MENU_ACTION_H_
#define ELE_INT 1
#define ELE_CHAR 2
#define ELE_STRING 3
#include <stdio.h>

void getInfo(const char* title,const char* question,void* data,int size,int flag);
void showbook();
void showallbooks();
void addbook();
void alterbook();
void removebook();
void borrowbook();
void returnbook();
void exitMenu();
#endif