#include "bookcase.h"
#include <stdlib.h>
#include <string.h>
static struct bookcase* bookcase=NULL;
void initalBookcase(){
    //
}
void addBookcase(const char* type){
    //
}
static void showBook(struct book* pBook){
    printf("[*] Book id:  %d\n",pBook->id);
    printf("    Name:  %s",pBook->name);
    printf("\tTotal count:  %d\n",pBook->totalCount);
    printf("    Current count:  %d",pBook->curCount);
    printf("\tPrice:  %d\n",pBook->price);
}
void showAllBooks(){
    //
}
void showSomeBooks(const char* type){
    //
}
void addBooks(int *keys,struct book* books,int n){
    
}
void removeBooks(){

}
void alterBooks(){

}
void freeBookcase(){
    //
}