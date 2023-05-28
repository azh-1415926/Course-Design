#include "menuAction.h"
#include "bookcase.h"
#include <stdlib.h>
#include <string.h>

static void freeBook(void* data){
    if(data==NULL)
        return;
    free(data);
}

void getInfo(const char* title,const char* question,void* data,int size,int flag){
    printf("\t%s\n",title);
    printf("%s\n",question);
    switch(flag){
        case ELE_INT:
            while(!scanf("%d",(int*)data))
                scanf("%*s");
            break;
        case ELE_CHAR:
            scanf("%c",(char*)data);
            break;
        case ELE_STRING:
            memset(data,0,size);
            scanf("%s",(char*)data);
            break;
        default:
            printf("no that option.\n");
    }
}
void showbook(){
    int id=0;
    getInfo("Search book","What the book's Id?",&id,0,ELE_INT);
    Book* pBook=searchBook(id);
    if(pBook){
        printf("Search the book.\n");
        showBook(pBook);
    }else{
        printf("Search error!,No that book.\n");
    }
}
void showallbooks()
{
    showAllBooks();
}
void addbook()
{
    int count=0;
    int id=0;
    getInfo("Add Books","How many books do you want to add?",&count,0,ELE_INT);
    Book* pBook=NULL;
    printf("Insert %d books.\n",count);
    for(int i=0;i<count;i++){
        printf("This is the %d book!\n",i+1);
        getInfo("Book Id","What is the book's id?",&id,0,ELE_INT);
        pBook=searchBook(id);
        if(pBook==NULL){
            pBook=(Book*)malloc(sizeof(Book));
            pBook->id=id;
            getInfo("Book Name","What is the book's name?",pBook->name,sizeof(pBook->name),ELE_STRING);
            getInfo("Book Author","What is the book's author?",pBook->author,sizeof(pBook->author),ELE_STRING);
            getInfo("Book Total","What is the book's total count?",&pBook->totalCount,0,ELE_INT);
            getInfo("Book Price","What is the book's price?",&pBook->price,0,ELE_INT);
            pBook->currCount=pBook->totalCount;
            addBook(pBook);
            showBook(pBook);
        }else{
            int option=0;
            int num=0;
            printf("The book already exists!\n");
            showBook(pBook);
            getInfo("Add books","Do you want to add some books?\n[0-1]",&option,0,ELE_INT);
            if(option)
                getInfo("Add books","How many books you want to add?",&num,0,ELE_INT);
            while(num<0)
                getInfo("Add books","Add error!Please enter again.",&num,0,ELE_INT);
            pBook->totalCount+=num;
            pBook->currCount+=num;
            printf("Add finish.\n");
            showBook(pBook);
        }
    }
}
void alterbook(){
    int id=0;
    int option=0;
    getInfo("Alter book","What the book's Id?",&id,0,ELE_INT);
    Book* pBook=searchBook(id);
    if(pBook){
        showBook(pBook);
        getInfo("Alter book","Do you want to alter name?\n[0-1]",&option,0,ELE_INT);
        if(option)
            getInfo("Book Name","Please enter book's name?",pBook->name,sizeof(pBook->name),ELE_STRING);
        getInfo("Alter book","Do you want to alter author?\n[0-1]",&option,0,ELE_INT);
        if(option)
            getInfo("Book Author","Please enter book's author?",pBook->author,sizeof(pBook->author),ELE_STRING);
        getInfo("Alter book","Do you want to alter price?\n[0-1]",&option,0,ELE_INT);
        if(option)
            getInfo("Book Author","Please enter book's price?",&pBook->price,0,ELE_INT);
        printf("Alter finish.\n");
        showBook(pBook);
    }else{
        printf("Alter error!No that book.\n");
    }
}
void removebook(){
    int id=0;
    getInfo("Remove book","What the book's Id?",&id,0,ELE_INT);
    Book* pBook=removeBook(id);
    if(pBook){
        printf("Remove a book.\n");
        showBook(pBook);
    }else{
        printf("Remove error!No that book.\n");
    }
}
void borrowbook()
{
    int id=0;
    getInfo("Borrow book","What the book's Id?",&id,0,ELE_INT);
    Book* pBook=searchBook(id);
    if(pBook){
        int currCount=pBook->currCount;
        int num=0;
        showBook(pBook);
        getInfo("Borrow book","How many books you want to borrow?",&num,0,ELE_INT);
        while(num>currCount){
            getInfo("Borrow book","Borrow error!Please enter again.",&num,0,ELE_INT);
        }
        pBook->currCount=pBook->totalCount-num;
        printf("Borrow finish.\n");
        showBook(pBook);
    }else{
        printf("Borrow error!No that book.\n");
    }
}
void returnbook()
{
    int id=0;
    getInfo("Return book","What the book's Id?",&id,0,ELE_INT);
    Book* pBook=searchBook(id);
    if(pBook){
        int count=pBook->totalCount-pBook->currCount;
        int num=0;
        showBook(pBook);
        getInfo("Return book","How many books you want to return?",&num,0,ELE_INT);
        while(num>count){
            getInfo("Return book","return error!Please enter again.\n",&num,0,ELE_INT);
        }
        pBook->currCount=pBook->currCount+num;
        printf("Return finish.\n");
        showBook(pBook);
    }else{
        printf("Return error!No that book.\n");
    }
}
void exitMenu()
{
    printf("exit!\n");
    freeBookcase(freeBook);
    exit(0);
}