# 停车场管理系统

**菜单初始化**

创建菜单需要一个菜单节点数组，设置标志位，包含了节点之间的关系，方便对菜单节点进行初始化。
1. 创建一个菜单节点数组。
    * 节点为一个结构体。
    * 结构体中数据项为 `标志位`、`名称`、`功能`、`brother 菜单节点指针`、`next 菜单节点指针`。
    * 初始化前，其标志位为当前节点相对于其在该数组中对应下标的前一个下标的节点之间的关系，指针全置为 `NULL`。
2. 调用 `initalMenu` 函数。
    * 传入参数为菜单项数组指针、菜单项个数。
    * 初始化时，将同级菜单节点保存在 brother 节点指针中，将子菜单节点保存在 next 节点指针中，并设置标志位。
    * 初始化后，其标志位为该节点与 next 节点的关系，brother 节点存放下一个同级节点，next 存放下级节点或同级节点首地址。
3. 调用 `showBrotherMenu` 函数。
    * 传入参数为同级菜单节点的首地址。
    * 将依次遍历输出所有的 brother 节点。
    * 返回值为同级节点个数。
4. 调用 `getOption` 函数。
    * 传入参数为最小合法输入序号和最大合法输入序号。
    * 最大合法输入序号可以传入 `showBrotherMenu` 函数返回的同级节点个数。
    * 返回值为序号-1，可作为下标索引。
5. 调用 `jumpNextMenu` 函数。
    * 传入同级菜单首地址和下标索引。
    * 合法的下标索引为 0 至 n-1。
    * 返回值为指定同级菜单节点指针。
6. 判断传出的当前节点标志位，即判断 next 中是否存有子菜单。
    * 若有。
        * 当前节点将指向 next，即子菜单。
        * 并调用函数输出该菜单。
    * 若无。
        * 调用 `executeAction` 函数。
        * 并调用 `showBrotherMenu` 函数输出最上级菜单，返回到开始菜单。
    * 若有需要，可以调用 `jumpPreMenu` 函数，尝试获取上级菜单节点，跳转到上级菜单。或者直接跳转到最上级菜单。

**菜单功能**

菜单节点没有子菜单，我们将绑定一个函数指针，用于调用特定函数。
1. 菜单功能函数用一个源文件存储，可供菜单直接调用。
2. 停车场和便道的实现另外用一个源文件编写，并把停车场和便道的作用域限定在该文件内，防止篡改，并调用数据类型对应文件开放的接口，该文件应开放一些接口供菜单功能函数使用，满足菜单的间接调用。
3. 数据类型文件，如栈、队列分别用独立的文件编写，开放相应的接口。

**具体实现**

菜单功能函数的具体实现
1. 初始化便道和停车道。
    * 给定便道和停车道的容量，分别调用函数初始化顺序队列和顺序栈
2. addCar 函数。
    * 判断传入的车指针是否为空，为空直接退出。
    * 调用 parking 函数。
3. removeCar 函数。
    * 判断停车场是否为空，不为空，调用 drivingaway 函数。
4. clearAllCars 函数。
    * 若停车场不为空，循环调用 drivingaway 函数。
5. 以下函数都设置为 static，将定义域限定在该文件内。
    * parking 函数。
        * 开进来的车都调用 parking 函数。
        * 判断停车道是否已满。
            * 若未满，直接进入停车道。
            * 若满了，调用 waiting 函数。
    * waiting 函数
        * 判断便道是否已满。
            * 若未满，进入便道等待停车道。
            * 若满了，直接退出，不做任何操作。
    * drivingaway 函数
        * 从停车道中开走一辆车，即出栈。
        * 判断便道是否为空，不为空，将便道队头的车辆入栈。
