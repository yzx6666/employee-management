#include <iostream>
#include "worker.h"
#include <fstream>

#define FILENAME "empFile.txt"

using namespace std;


class workerManager
{
private:
    /* data */
public:

    int m_EmpNum;
    worker **m_EmpArray;
    bool m_FileIsEmpty;

    workerManager(/* args */);
    ~workerManager();

    void show_Menu();
    void exitSystem();

    void Add_Emp();
    void save();

    int get_EmpNum();
    void init_Emp();

    void show_Emp();

    void Del_Emp();
    int IsExist(int id);

    void Mod_Emp();

    void Find_Emp();

    void Sort_Emp();
    void clear_Emp();
};

