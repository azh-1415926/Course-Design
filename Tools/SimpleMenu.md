# SimpleMenu 帮助文档
> 该文档用于查阅 simpleMenu 头文件内函数的具体用法

simpleMenu 用于创建一个多级菜单，需要包含 simpleMenu.h 头文件，这是一些函数原型。
```c
//初始化菜单
void initalMenu(struct menuItem* menu,int n);
//遍历兄弟菜单
int showBrotherMenu(struct menuItem* menu);
//获取用户选择
int getOption(int minnum,int maxnum);
//获取该菜单的指定兄弟菜单
struct menuItem* jumpNextMenu(struct menuItem* menu,int pos);
//获取该菜单的上级菜单
struct menuItem* jumpPreMenu(struct menuItem* menu);
//执行指定菜单功能
void executeAction(struct menuItem* menu);
```
**初始化菜单**

传入一个结构体数组，以及数组元素的个数对菜单进行初始化，可以创建在栈上，不需要释放
* 函数原型
    * `void initalMenu(struct menuItem* menu,int n);`
* 参数
    * menu
        * menuItem 结构体指针，指向一组菜单数组的首地址
    * n
        * 菜单个数

menuItem 结构体
```c
struct menuItem {
    int flag;
    //标志位
    const char* name;
    //菜单名称
    void (*handle)(void);
    //菜单功能
    struct menuItem* brother;
    //兄弟菜单指针
    struct menuItem* next;
    //下一个菜单指针
};
```
* flag
    * 取值
        * SAME_LEVEL_MENU 同级菜单
        * PRE_LEVEL_MENU 上级菜单
        * NEXT_LEVEL_MENU 下一个菜单
        * LAST_MENU 最后一个同级菜单
        * NO_SUB_MENU 无子菜单
        * SUB_MENU 子菜单
        * LAST_SUB_MENU 最后一个子菜单
    * 初始化前，表示该节点相对上个节点的关系
    * 初始化后，表示该节点与 next 中存放节点的关系
* name 菜单名称
    * 菜单显示出来的名称
* handle 菜单功能
    * 进入菜单触发的功能
* brother 兄弟菜单指针
    * 同级的其他菜单
* next 下级菜单指针
    * 指向子菜单、上级菜单、同级菜单，优先级从高到低
    * 当存在子菜单时，存放下级菜单，标志位设置子菜单
    * 当为最后一个菜单
        * 若存在上级菜单，存放上级菜单指针，标志位设置上级菜单
        * 若不存在上级菜单，存放同级菜单首地址，标志位设置同级菜单

函数示例
```c
struct menuItem item[]={
        {SAME_LEVEL_MENU,"level 1",NULL,NULL,NULL},
        {SAME_LEVEL_MENU,"level 2",NULL,NULL,NULL},
        {SUB_MENU,"2-1",action2_1,NULL,NULL},
        {SAME_LEVEL_MENU,"2-2",action2_2,NULL,NULL},
        {SAME_LEVEL_MENU,"2-3",action2_3,NULL,NULL},
        {SAME_LEVEL_MENU,"2-4",action2_4,NULL,NULL},
        {LAST_MENU,"2-5",action2_5,NULL,NULL},
        {NEXT_LEVEL_MENU,"level 3",NULL,NULL,NULL},
        {SUB_MENU,"3-1",action3_1,NULL,NULL},
        {SAME_LEVEL_MENU,"3-2",action3_2,NULL,NULL},
        {LAST_MENU,"3-3",action3_3,NULL,NULL},
        {NEXT_LEVEL_MENU,"level 4",NULL,NULL,NULL}
    };
    initalMenu(item,sizeof(item)/sizeof(struct menuItem));
```
注意事项 :
* 初始化前
    1. 当前菜单为上一个菜单的同级菜单，标志位为 `SAME_LEVEL_MENU`

    2. 当前菜单为上一个菜单的子菜单，标志位为  `SUB_LEVEL_MENU`

    3. 上个菜单为其他菜单的子菜单，当前菜单标志位为 `NEXT_LEVEL_MENU`

    4. 当前菜单与上一个菜单同级，为上级菜单的最后一个子菜单，标志位为 `LAST_MENU`

    5. 当前菜单为上一个菜单的唯一的一个子菜单，标志位为 `LAST_SUB_MENU`
* 初始化后
    1. 当前菜单的 brother 存放下一个同级菜单，没有则为空

    2. 当前菜单的 next 优先存放子菜单(没有则为空)，若为最后一个菜单则存放上级菜单(没有则为同级菜单)

    3. 当前菜单为下一个菜单的同级菜单，无子菜单，next，标志位为 `NO_SUB_MENU`

    4. 当前菜单的下一个菜单为子菜单，next 存放子菜单，标志位为  `SUB_LEVEL_MENU`

    5. 当前菜单为上个菜单的同级菜单，为上级菜单的最后一个子菜单， next 存放上级菜单，标志位为 `PRE_LEVEL_MENU`

    6. 当前菜单为上一个菜单的同级菜单，无上级菜单，next 存放同级菜单的首地址，标志位为 `SAME_LEVEL_MENU`

**显示同级菜单**

传入一个菜单节点，遍历它的所有 brother 节点
* 函数原型
    * `int showBrotherMenu(struct menuItem* menu);`
* 参数
    * menu
        * menuItem 结构体指针，为同级菜单的首地址，将遍历它的所有兄弟菜单
* 返回值
    * 返回同级菜单的个数，方便判断用户的合法选择

**获取用户选择**

给出最小合法值和最大合法值，检测用户是否做出合理的选择
* 函数原型
    * `int getOption(int minnum,int maxnum);`
* 参数
    * minnum
        * 最小序号，可相等
    * maxnum
        * 最大序号，可相等
* 返回值
    * 返回用户输入的合法序号 -1

**菜单跳转**
* 函数原型
    * `struct menuItem* jumpNextMenu(struct menuItem* menu,int pos);`
    * `struct menuItem* jumpPreMenu(struct menuItem* menu);`
* 参数
    * menu
        * menuItem 结构体指针
            * 在 jumpNextMenu 中，一般为同级菜单首地址，为任意兄弟菜单地址
            * 在 jumpPreMenu 中，需要传入任意子菜单地址，可以判断是否为最后一个节点，从而跳转
        * pos
            * 需要跳转节点相对兄弟节点的偏移量，传入用户选择的序号即可
* 返回值
    * 正常返回节点指针，异常返回 NULL

**执行菜单功能**
* 函数原型
    * `void executeAction(struct menuItem* menu);`
* 参数
    * menu 
        * menuItem 结构体
        * 执行菜单节点中的函数指针指向的函数

