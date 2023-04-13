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
struct bookcase {
    const char* type;
    int id;
    struct book* books;
    struct bookcase* next;
};
void initalBookcase();
void addBookcase(const char* type);
struct bookcase* getBookcaseByType(const char* type);
void removeBookcase(const char* type);
//static void showBook(struct book* pBook);
void showAllBooks();
void showSomeBooks(const char* type);
void addBooks(const char* type,struct book* books,int n);
void removeBooks();
void alterBooks();
void freeBookcase();
#endif