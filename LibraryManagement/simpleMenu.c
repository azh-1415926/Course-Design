#include "simpleMenu.h"
#include "linkStack.h"
void initalMenu(struct menuItem* menu,int n){
    //定义节点指针分别用于存储上级菜单、上个节点、当前节点
    struct menuItem* parentMenu=menu;
    struct menuItem* preMenu=NULL;
    struct menuItem* curMenu=menu;
    //定义一个链栈用于存放上级菜单节点指针
    linkStack parentStack;
    //初始化链栈
    linkStackInitalize(&parentStack);
    //我们以当前同级节点的第一个节点为上级节点，方便初始化其他节点的时候存放新的 brother 节点
    //brother 存放同级节点地址
    //next 存放
        //下级节点(所有节点优先存放下级节点)
        //上级节点(最后的同级节点且有上级节点)
        //同级节点(最后的同级节点且没有上级节点和下级节点)
    for(int i=0;i<n;i++){
        //读取第 i 个节点
        curMenu=&menu[i];
        //第一个结点的前一个节点为NULL
        if(preMenu==NULL)
            //我们默认认为第一个结点为同级节点
            curMenu->flag=SAME_LEVEL_MENU;
        switch (curMenu->flag)
        {
        //若当前节点为上个结点的同级节点
        case SAME_LEVEL_MENU:
            //排除第 0 个节点为NULL的情况，当前节点应为上级节点的 brother，上级节点标志位置为 无子菜单
            if(preMenu!=NULL){
                preMenu->brother=curMenu;
                preMenu->flag=NO_SUB_MENU;
            }   
            break;
        //若当前节点为上个结点的下级节点
        case SUB_MENU:
            //将上个节点的上级节点入栈
            linkStackPush(parentStack,parentMenu);
            //上个节点置为新的上级节点
            parentMenu=preMenu;
            //上级节点的 next 存放下级节点(当前节点)，并将标志位置为 子菜单
            parentMenu->flag=SUB_MENU;
            parentMenu->next=curMenu;
            break;
        //若当前节点为上个结点的同级节点且为最后一个节点
        case LAST_MENU:
            //上个节点标志位置为无子菜单，且 brother 存放当前节点
            preMenu->flag=NO_SUB_MENU;
            preMenu->brother=curMenu;
            //还原上上级节点为当前上级节点，并用 next 存放
            if(!linkStackIsEmpty(parentStack)){
                //还原成功，即为当前节点的上级节点
                curMenu->flag=PRE_LEVEL_MENU;
                parentMenu=linkStackTop(parentStack);
                linkStackPop(parentStack);
            }else
                //还原失败，即为当前节点的同级节点
                curMenu->flag=SAME_LEVEL_MENU;
            curMenu->next=parentMenu;
            break;
        //若当前节点为上个结点的子节点且为最后一个节点
        case LAST_SUB_MENU:
            //上个节点标志位置为 子菜单，next 存放当前节点
            preMenu->flag=SUB_MENU;
            preMenu->next=curMenu;
            //当前节点标志位置为 上级节点，next 存放上级节点
            curMenu->flag=PRE_LEVEL_MENU;
            curMenu->next=parentMenu;
            //若上级节点为上个节点，当前节点的标志位应该置为 同级节点
            //因为方便初始化，于是把当前同级节点的首地址置为了上级节点
            if(preMenu==parentMenu)
                curMenu->flag=SAME_LEVEL_MENU;
            break;
        //若当前节点为上个结点的下级节点
        case NEXT_LEVEL_MENU:
            //preMenu 临时置为上级菜单，这时的 preMenu 无特定意义
            preMenu=parentMenu;
            //利用当前不使用的 preMenu 找到上级节点的末尾 brother 节点，并把这个节点的 brother 置为当前节点
            while(preMenu->brother)
                preMenu=preMenu->brother;
            preMenu->brother=curMenu;
            break;
        default:
            break;
        }
        //处理最后一个节点
        if(i==n-1){
            //标志位默认置为 同级菜单
            curMenu->flag=SAME_LEVEL_MENU;
            //若有上级节点，恢复成真正的上级节点
            if(!linkStackIsEmpty(parentStack)){
                curMenu->flag=PRE_LEVEL_MENU;
                parentMenu=linkStackTop(parentStack);
                linkStackPop(parentStack);
            }
            //若栈为空，parentMenu 不用更新，默认为当前同级节点的首地址，所以需要检查栈中是否存有上级节点
            curMenu->next=parentMenu;
        }
        //更新上个节点为当前节点
        preMenu=curMenu;
    }
    //销毁链栈
    linkStackFree(&parentStack);
}
int showBrotherMenu(struct menuItem* menu){
    struct menuItem* curMenu=menu;
    int i=0;
    while(curMenu!=NULL){
        printf(" [ %d ]     %s\n",i+1,curMenu->name);
        i++;
        curMenu=curMenu->brother;
    }
    return i;
}
int getOption(int minnum,int maxnum){
    if(maxnum<minnum)
        return 0;
    char option;
    printf("Please enter:");
    fflush(stdin);
    scanf("%c",&option);
    while(option<minnum+48||option>maxnum+48){
        fflush(stdin); 
        printf("error!Please enter incorrect option!\nenter:");
        scanf("%c",&option);
        fflush(stdin);
    }
    return option-49;
}
struct menuItem* jumpNextMenu(struct menuItem* menu,int pos){
    struct menuItem* curMenu=menu;
    int i=0;
    while(curMenu!=NULL&&i++<pos){
        if(curMenu->brother!=NULL)
            curMenu=curMenu->brother;
        else
            break;
    }
    return curMenu;
}
struct menuItem* jumpPreMenu(struct menuItem* menu){
    struct menuItem* curMenu=menu;
    while(curMenu!=NULL){
        if(curMenu->brother!=NULL)
            curMenu=curMenu->brother;
        else
            break;
    }
    if(curMenu&&curMenu->flag==PRE_LEVEL_MENU)
        return curMenu->next;
    return NULL;
}
void executeAction(struct menuItem* menu){
    if(menu&&menu->handle)
        (menu->handle)();
}