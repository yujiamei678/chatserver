#include "usermodel.hpp"
#include "db.hpp"
#include <iostream>
using namespace std;

// User表的增加方法
bool UserModel::insert(User &user)
{
    // 1.组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "insert into User(name, password, state) values('%s', '%s', '%s')", 
            user.getName().c_str(), user.getPwd().c_str(), user.getState().c_str()); 
    
    MySQL mysql;
    if (mysql.connect())
    {
        if (mysql.update(sql)) //相当于在数据库chat中执行 insert into User(name, password, state) values('%s', '%s', '%s')语句   
        {
            // 获取插入成功的用户数据生成的主键id 自动设置id
            user.setId(mysql_insert_id(mysql.getConnection()));// mysql_insert_id：给一个mysql返回这个mysql的id
            return true;
        }
    }

    return false;
}

// 根据用户号码查询用户信息
User UserModel::query(int id)
{
    // 1.组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "select * from User where id = %d", id);

    MySQL mysql;
    if (mysql.connect())
    {
        MYSQL_RES *res = mysql.query(sql);  //相当于在mysql执行 select * from user where id = ‘id’ 语句并返回一个MYSQL_RES变量
        if (res != nullptr)
        {
            MYSQL_ROW row = mysql_fetch_row(res); //mysql_fetch_row：返回res的一行
            if (row != nullptr)
            {
                User user; //将查询到的结果放入User对象中返回
                user.setId(atoi(row[0]));
                user.setName(row[1]);
                user.setPwd(row[2]);
                user.setState(row[3]);
                mysql_free_result(res); //释放内存资源
                return user;    
            }
        }
    }

    return User();
}

// 更新用户的状态信息
bool UserModel::updateState(User user)
{
    // 1.组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "update User set state = '%s' where id = %d", user.getState().c_str(), user.getId());

    MySQL mysql;
    if (mysql.connect())
    {
        if (mysql.update(sql))
        {
            return true;
        }
    }
    return false;
}

// 重置用户的状态信息
void UserModel::resetState()
{
    // 1.组装sql语句
    char sql[1024] = "update User set state = 'offline' where state = 'online'";

    MySQL mysql;
    if (mysql.connect())
    {
        mysql.update(sql);
    }
}