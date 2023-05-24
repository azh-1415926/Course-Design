#ifndef _BOOK_CASE_H_
#define _BOOK_CASE_H_
#include <stdio.h>
struct book {
    int id;
    char name[20];
    char author[20];
    int totalCount;
    int curCount;
    int price;
    struct book* next;
};
void initalBookcase();
void removeBookcase(const char* type);
//static void showBook(struct book* pBook);
void showAllBooks();
void showSomeBooks(const char* type);
void addBooks(int *keys,struct book* books,int n);
void removeBooks();
void alterBooks();
void freeBookcase();
#endif