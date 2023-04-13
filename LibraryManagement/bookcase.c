#include "bookcase.h"
#include <stdlib.h>
#include <string.h>
static struct bookcase* bookcase=NULL;
void initalBookcase(){
    bookcase=(struct bookcase*)malloc(sizeof(struct bookcase));
    bookcase->type="NULL";
    bookcase->id=0;
    bookcase->books=(struct book*)malloc(sizeof(struct book));
    bookcase->next=NULL;
}
void addBookcase(const char* type){
    struct bookcase* pBookcase=bookcase;
    while(pBookcase->next)
        pBookcase=pBookcase->next;
    pBookcase->next=(struct bookcase*)malloc(sizeof(struct bookcase));
    pBookcase=pBookcase->next;
    pBookcase->type=type;
    pBookcase->books=(struct book*)malloc(sizeof(struct book));
    pBookcase->books->next=NULL;
    pBookcase->next=NULL;
}
struct bookcase* getBookcaseByType(const char* type){
    struct bookcase* pBookcase=bookcase;
    while(pBookcase){
        if(strcmp(pBookcase->type,type))
            break;
        pBookcase=pBookcase->next;
    }
    return pBookcase;
}
void removeBookcase(const char* type){
    struct bookcase* pBookcase=bookcase;
    struct book* pBook=NULL;
    struct book* temp_book=NULL;
    while(pBookcase->next){
        if(strcmp(pBookcase->next->type,type))
            break;
        pBookcase=pBookcase->next;
    }
    if(pBookcase->next)
        pBookcase->next=pBookcase->next->next;
    pBook=pBookcase->next->books;
    while(pBook){
        temp_book=pBook;
        pBook=pBook->next;
        free(temp_book);
    }
    free(pBookcase->next);
}
static void showBook(struct book* pBook){
    printf("Book id:  %d",pBook->id);
    printf(",Book name:  %s",pBook->name);
    printf(",Book total count:  %d",pBook->totalCount);
    printf(",Book current count:  %d",pBook->curCount);
    printf(",Book price:  %d",pBook->price);
}
void showAllBooks(){
    struct bookcase* pBookcase=bookcase;
    struct book* pBook=NULL;
    while(pBookcase){
        pBook=pBookcase->books;
        while(pBook)
            showBook(pBook);
        pBookcase=pBookcase->next;
    }
}
void showSomeBooks(const char* type){
    struct bookcase* pBookcase=getBookcaseByType(type);
    struct book* pBook=pBookcase?pBookcase->books:NULL;
    while(pBook){
        showBook(pBook);
        pBook=pBook->next;
    }
}
void addBooks(const char* type,struct book* books,int n){
    //struct bookcase* pBookcase=getBookcaseByType(type);
    //struct book* pBook=pBookcase?pBookcase->books:NULL;
    struct book* pBook=bookcase->books;
    if(pBook==NULL)
        return;
    while(pBook->next)
        pBook=pBook->next;
    for(int i=0;i<n;i++){
        pBook->next=&books[i];
        pBook=pBook->next;
        showBook(pBook);
    }
}
void removeBooks(){

}
void alterBooks(){

}
void freeBookcase(){
    struct bookcase* pBookcase=NULL;
    struct book* pBook=NULL;
    struct book* temp_book=NULL;
    while(bookcase){
        pBookcase=bookcase;
        pBook=bookcase->books;
        while(pBook){
            temp_book=pBook;
            pBook=pBook->next;
            free(temp_book);
        }
        free(pBookcase);
        bookcase=bookcase->next;    
    }
}