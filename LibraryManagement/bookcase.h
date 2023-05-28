#ifndef _BOOK_CASE_H_
#define _BOOK_CASE_H_
#include <stdio.h>
#include <stdbool.h>
typedef struct Book {
    int id;
    char name[20];
    char author[20];
    int totalCount;
    int currCount;
    int price;
}Book;

void initalBookcase();
void freeBookcase(void(freeData)(void*));
Book* searchBook(int id);
void showBook(void* data);
void showAllBooks();
bool addBook(Book* book);
Book* removeBook(int id);
#endif