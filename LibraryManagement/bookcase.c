#include "bookcase.h"
#include <myDS/bTree.h>
#include <stdlib.h>
#include <string.h>
static BTree bookcase=NULL;

void initalBookcase(){
    bTreeInitalize(&bookcase);
}

void freeBookcase(void(freeData)(void*)){
    if(freeData!=NULL)
        bTreeLevelOrderTraversal(bookcase,freeData);
    bTreeFree(&bookcase);
}

Book* searchBook(int id){
    return bTreeSearch(bookcase,id);
}

void showBook(void* data){
    if(data==NULL)
        return;
    Book* pBook=(Book*)data;
    printf("[*] Book id: %d",pBook->id);
    printf("\tName: %s",pBook->name);
    printf("\tAuthor: %s",pBook->author);
    printf("\tTotal count: %d",pBook->totalCount);
    printf("\tCurrent count: %d",pBook->currCount);
    printf("\tPrice: %d\n",pBook->price);
}

void showAllBooks(){
    bTreeInOrderTraversal(bookcase,showBook);
}

bool addBook(Book* book){
    return bTreeInsert(bookcase,book->id,book);
}
Book* removeBook(int id){
    return bTreeDelete(bookcase,id);
}