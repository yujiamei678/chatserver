#ifndef GROUPUSER_H
#define GROUPUSER_H

#include "user.hpp"

// 群组用户类
// 多了一个role角色信息，从User类直接继承，复用User的其它信息
class GroupUser : public User
{
public:
    // 设置用户群内角色
    void setRole(string role) { this->role = role; }

    //获取用户群内角色
    string getRole() { return this->role; }

private:
    string role;    //群内角色
};

#endif