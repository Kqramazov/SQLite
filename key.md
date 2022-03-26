可能需要注意的要点：  
操作sqlite的准备工作：  
1：sudo apt install sqlite3  
它将在Linux上安装sqlite解释器（？）  
2: sudo apt install libsqlite3-dev  
它将在Linux系统的的c库中放入sqlite的头文件等相关文件  
完成后可直接以#include<sqlite3.h>的方式调用库函数  
3:编译时需要手动加载第三方库 lsqlite3才不会链接失败  
编译代码的例子：  
g++ main.cpp -o run -lsqlite3  
./run  
  
附带的main函数实现了基本的新建文件，新建表，通过调用函数在表中插入记录，  
返回查询结果的功能。  
核心的接口思路是：  
sqlite3_open和sqlite3_close函数控制文件指针的打开与关闭  
可以注意到这样的数据库会全部封装在一个文件中，对应一个文件指针的操作  
而之后所有原来的sql查询语言的接口都通过sqlite3_exec函数实现  
该函数需要提供之前open出来的文件指针和一个字符串（对应查询语句）来实现基本功能  
回调函数机制挺有意思的，建议搜索一下了解其的功能和实现方式  