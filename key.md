可能需要注意的要点：
操作sqlite的准备工作：
1：sudo apt install sqlite3
2: sudo apt install libsqlite3-dev
完成后可直接以#include<sqlite3.h>的方式调用库函数
3:编译时需要手动加载第三方库 lsqlite3才不会链接失败
例子：
g++ main.cpp -o run -lsqlite3
./run
