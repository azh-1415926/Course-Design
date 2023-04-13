#include "menuAction.h"
#include "bookcase.h"
void getInfo(const char* title,const char* question,void* data,int size,int flag){
    printf("\t%s\n",title);
    printf("%s\n",question);
    fflush(stdin);
    switch(flag){
        case ELE_INT:
            scanf("%d",(int*)data);
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
    fflush(stdin);
}
void showBook(){

}
void addBook(){
    int count;
    getInfo("Add Books","How many books do you want to add?",&count,0,ELE_INT);
    struct book* pBook=(struct book*)malloc(sizeof(struct book));
    for(int i=0;i<count;i++){
        printf("This is the %d book!\n",i+1);
        pBook[i].id=i+1;
        getInfo("Book Name","What is the book's name?",&pBook[i].name,sizeof(pBook->name),ELE_STRING);
        getInfo("Book Author","What is the book's author?",&pBook[i].author,sizeof(pBook->author),ELE_STRING);
        getInfo("Book Total","What is the book's total count?",&pBook[i].totalCount,0,ELE_INT);
        getInfo("Book Price","What is the book's price?",&pBook[i].price,0,ELE_INT);
        pBook[i].curCount=pBook[i].totalCount;
        if(i!=count-1)
            pBook[i].next=&pBook[i+1];
        else
            pBook[i].next=NULL;
        
    }
    addBooks("test",pBook,count);
}
void alterBook(){
    int pos;
}
void removeBook(){
    int pos;
}
void exitMenu(){
    printf("exit!\n");
    freeBookcase();
    exit(0);
}