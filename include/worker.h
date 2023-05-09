#ifndef WORKER_H__
#define WORKER_H__
#include <iostream>
#include <string>

using namespace std;

class worker
{
public:

    virtual void showInfo() = 0;

    virtual string getDeptName() = 0;

    int m_Id;
    string m_Name;
    int m_DeptId;
    // virtual ~worker() = 0;
    // virtual ~worker();
    virtual ~worker() {}
};


#endif