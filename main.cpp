#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
int select_callback(void *NotUsed, int n_column, char **column_value, char **column_name)
{ //回调函数，会在数据库查询成功返回结果后立刻执行一次
  // para是你在 sqlite3_exec 里传入的 void * 参数

    //通过para参数，你可以传入一些特殊的指针（比如类指针、结构指针），然后在这里面强制转换成对应的类型（这里面是void*类型，必须强制转换成你的类型才可用）。然后操作这些数据

    // n_column是这一条记录有多少个字段 (即这条记录有多少列)

    // char ** column_value 是个关键值，查出来的数据都保存在这里，它实际上是个1维数组（不要以为是2维数组），每一个元素都是一个 char * 值，是一个字段内容（用字符串来表示，以/0结尾）

    // char ** column_name 跟 column_value是对应的，表示这个字段的字段名称
    int i;
    printf("现在执行的是手写回调函数的查询结果，包含 %d 个字段:\n", n_column);
    for (i = 0; i < n_column ; i++){
        printf("字段名: %s ß > 字段值: %s \n", column_name[i], column_value[i]);
    }
    printf( "-- -- -- -- -- -- -- -- -- \n");
    return 0;
}
int main(){
    sqlite3 *db = NULL;
    int result=sqlite3_open("first.db", &db);//要传指针的地址
    if(result!=SQLITE_OK){
        printf("Failed to open.\n");
        return -1;
    }
    else{
        printf("Successfully open.\n");
    }
    //需要执行的sql语句以字符串的形式传入
    char *errmsg = NULL; //失败时需要查阅的错误信息
    int result_create = sqlite3_exec(db, "create table if not exists MyTable_1(ID integer primary key autoincrement,name nvarchar(32))", NULL, NULL, &errmsg);
    //printf("创建表，现在还没有seg fault.\n");
    if (result_create != SQLITE_OK)
    {
        printf("创建表失败，错误码: %d，错误原因: %s \n", result, errmsg);
    }
    
    int result_insert1 = sqlite3_exec(db, "insert into MyTable_1(name) values( 'YYH' )", 0, 0, &errmsg);
    if(result_insert1 !=SQLITE_OK){
        printf("插入记录失败，错误码: %d，错误原因: %s \n", result, errmsg);
    }
    int result_insert2 = sqlite3_exec(db, "insert into MyTable_1(name) values( 'JXF' )", 0, 0, &errmsg);
    if (result_insert2 != SQLITE_OK)
    {
        printf("插入记录失败，错误码: %d，错误原因: %s \n", result, errmsg);
    }
    int result_insert3 = sqlite3_exec(db, "insert into MyTable_1(name) values( 'LZC' )", 0, 0, &errmsg);
    if (result_insert3 != SQLITE_OK)
    {
        printf("插入记录失败，错误码: %d，错误原因: %s \n", result, errmsg);
    }
    int result_select = sqlite3_exec(db, "select * from MyTable_1", select_callback, NULL, &errmsg);
    
    int result_get;
    int nRow, nColumn;
    char **dbResult;
    int index;
    result_get=sqlite3_get_table(db, "select * from MyTable_1", &dbResult, &nRow, &nColumn, &errmsg);
    if(result_get==SQLITE_OK){
        index = nColumn;
        printf("现在执行的是get_table的返回结果，查到%d条记录：\n", nRow);
        for (int i = 0; i < nRow;i++){
            printf("第%d条记录：\n", i + 1);
            for (int j = 0; j < nColumn;j++){
                printf("字段名: %s ß > 字段值: %s \n", dbResult[j], dbResult[index]);
                ++index;
            }
            printf("-- -- -- -- -- -- -- -- -- \n");
        }
    }
    else{
        printf("get_table失败，错误码: %d，错误原因: %s \n", result, errmsg);
    }
    sqlite3_free_table( dbResult );
    sqlite3_close(db);
    return 0;
}