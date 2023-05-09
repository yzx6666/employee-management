#include "../include/workerManager.h"
#include "../include/worker.h"
#include "../include/employee.h"
#include "../include/boss.h"
#include "../include/manager.h" 
#include <string>
#include <algorithm>

workerManager::workerManager(/* args */)
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    if(!ifs.is_open())
    {
        cout<<"文件不存在"<<endl;
        this->m_EmpNum = 0;
        this->m_EmpArray = NULL;
        this->m_FileIsEmpty = true;

        ifs.close();
        return ;
    }
     
    char ch;
    ifs >> ch;
    if(ifs.eof())
    {
        cout<<"文件为空"<<endl;
        this->m_EmpNum = 0;
        this->m_EmpArray = NULL;
        this->m_FileIsEmpty = true;

        ifs.close();
        return ;
    }

    int num = this->get_EmpNum();
    this->m_EmpNum = num;
    this->m_FileIsEmpty = false;
    
    this->m_EmpArray = new worker*[this->m_EmpNum];
    this->init_Emp();
   
    // for(int i = 0; i < this->m_EmpNum; i ++ )
    // {
    //     cout << this->m_EmpArray[i]->m_Id << " " << this->m_EmpArray[i]->m_Name << " "
    //         <<  this->m_EmpArray[i]->m_DeptId << endl;
    // }
}

workerManager::~workerManager()
{
    if(this->m_EmpArray != NULL)
    {
        for(int i = 0; i < this->m_EmpNum; i ++ )
        {
            if(this->m_EmpArray[i] != NULL)
            {
                delete this->m_EmpArray[i];
                this->m_EmpArray[i] = NULL;
            }
        } 
        delete [] this->m_EmpArray;
        this->m_EmpArray = NULL;
    }
   
}

void workerManager::show_Menu()
{
    cout<<"************************************************"<<endl;
    cout<<"********** 欢迎使用职工管理系统*****************"<<endl;
    cout<<"**********    0.退出管理程序  ******************"<<endl;
    cout<<"**********    1.增加职工信息  ******************"<<endl;
    cout<<"**********    2.显示职工信息  ******************"<<endl;
    cout<<"**********    3.删除职工信息  ******************"<<endl;
    cout<<"**********    4.修改职工信息  ******************"<<endl;
    cout<<"**********    5.查找职工信息  ******************"<<endl;
    cout<<"**********    6.按照编号排序  ******************"<<endl;
    cout<<"**********    7.清空所有文档  ******************"<<endl;
    cout<<"************************************************"<<endl;
    cout<<endl;
}

void workerManager::exitSystem()
{
    cout<<"欢迎下次使用" <<endl;

    system("pause");
    exit(0);
}

void workerManager::Add_Emp()
{
    cout<<"请输入添加员工数量"<<endl;

    int addNum = 0;
    cin>>addNum;

    if(addNum > 0) 
    {
        int newSize = this->m_EmpNum + addNum;

        worker **newSpace = new worker*[newSize];

        for(int i = 0; i < this->m_EmpNum; i ++ )
        {
            newSpace[i] = this->m_EmpArray[i];
        }

        for(int i = 0; i < addNum; i ++ )
        {
            int id;
            string name;
            int did;
            
            cout << "请输入第" << i + 1 << "个新职工的编号" << endl;  
            cin >> id;
            while (this->IsExist(id) != -1)
            {
                cout << "该编号员工已存在，请输入其他编号" << endl;
                cin >> id;
            }
            cout << "请输入第" << i + 1 << "个新职工的姓名" << endl;
            cin >> name;
            cout << "请选择该职工岗位" << endl;
            cout << "1、普通员工" << endl;
            cout << "2、经理" << endl;
            cout << "3、老板" << endl;
            cin >> did;

            worker * w = NULL;

            switch (did)
            {       
            case 1:
                w = new employee(id, name, did);
                break;
            case 2:
                w = new manager(id, name, did);
                break;
            case 3:
                w = new boss(id, name, did);
                break;
            default:
                break;
            }

            newSpace[this->m_EmpNum + i] = w;
        }

            delete [] this->m_EmpArray;

            this->m_EmpArray = newSpace;
            this->m_EmpNum = newSize;

            this->save();
            this->m_FileIsEmpty = false;
            cout<<"添加"<< addNum <<"名员工成功"<<endl;
    }
    else
    {
        cout<<"输入数据有误"<<endl;
    }

    system("pause");
    system("cls");
}

void workerManager::save()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out);

    for(int i = 0; i < this->m_EmpNum; i ++ )
    {
        ofs << this->m_EmpArray[i]->m_Id << " "
            << this->m_EmpArray[i]->m_Name << " "
            << this->m_EmpArray[i]->m_DeptId << endl;
    }

    ofs.close();
}

int workerManager::get_EmpNum()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int id, did;
    string name;

    int num = 0;

    while(ifs>>id&&ifs>>name&&ifs>>did)
    {
        num ++ ;
    }
    
    return num;
}

void workerManager::init_Emp()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int id, did;
    string name;

    int idx = 0;
    while (ifs >> id && ifs >> name && ifs >> did)
    {
        worker * w = NULL;
        switch (did)
        {
            case 1:
                w = new employee(id ,name, did);
                break;
            case 2:
                w = new manager(id ,name, did);
                break;
            case 3:
                w = new boss(id ,name, did);
                break;
            
            default:
                break;
        }
        this->m_EmpArray[idx++] = w;
    }

    ifs.close();
    
}

void workerManager::show_Emp()
{
    if(this->m_FileIsEmpty)
    {
        cout<< "文件不存在或记录为空" <<endl;
    }
    else
    {
        for(int i = 0; i < this->m_EmpNum; i ++ )
        {
            this->m_EmpArray[i]->showInfo();
        }
    }

    system("pause");
    system("cls");
}

int workerManager::IsExist(int id)
{
    int idx = -1;
    for(int i = 0; i < this->m_EmpNum; i ++ )
    {
        if(this->m_EmpArray[i]->m_Id == id)
        {
            idx = i;
            break;
        }
    }

    return idx;
}

void workerManager::Del_Emp()
{

    if(this->m_FileIsEmpty)
    {
        cout << "文件不存在或记录为空" << endl;
        system("pause");
        system("cls");
        return ;
    }

    int id, idx = -1;
    cout << "请输入想要删除的职工编号" << endl;
    cin>>id;

    idx = this->IsExist(id);
    if(idx == -1)
    {
        cout << "删除失败，未找到该员工" << endl;
    }
    else 
    {
        for(int i = idx; i < this->m_EmpNum - 1; i ++ )
        {
            this->m_EmpArray[i] = this->m_EmpArray[i + 1];
        }
        this->m_EmpNum -- ;
        if(this->m_EmpNum == 0) this->m_FileIsEmpty = true;

        this->save();

        cout << "删除成功" << endl;
    }
    system("pause");
    system("cls");
}

void workerManager::Mod_Emp()
{
    if(this->m_FileIsEmpty)
    {
        cout << "文件不存在或记录为空" << endl;
        system("pause");
        system("cls");
        return ;
    }

    int id, idx = -1;
    cout << "请输入想要修改的职工编号" << endl;
    cin>>id;

    idx = this->IsExist(id);
    if(idx == -1)
    {
        cout << "修改失败，未找到该员工" << endl;
    }
    else 
    {
        delete this->m_EmpArray[idx];
        this->m_EmpArray[idx] = NULL;


        int newId, newDid;
        string newName;

        cout << "查找到" << id << "号职工，请输入新的职工号" << endl;
        cin>> newId;
        cout << "请输入新姓名" << endl;
        cin >> newName;
        cout << "请选择该职工岗位" << endl;
        cout << "1、普通员工" << endl;
        cout << "2、经理" << endl;
        cout << "3、老板" << endl;
        cin >> newDid;

        worker * w = NULL;

            switch (newDid)
            {       
            case 1:
                w = new employee(newId, newName, newDid);
                break;
            case 2:
                w = new manager(newId, newName, newDid);
                break;
            case 3:
                w = new boss(newId, newName, newDid);
                break;
            default:
                break;
            }

            this->m_EmpArray[idx] = w;

        this->save();

        cout << "修改成功" << endl;
    }
    system("pause");
    system("cls");
}

void workerManager::Find_Emp()
{
    if(this->m_FileIsEmpty)
    {
        cout << "文件不存在或记录为空" << endl;
        system("pause");
        system("cls"); 
        return ;
    }

    cout << "请输入查找的方式" <<endl;
    cout << "1、按照职工编号查找：" <<endl;
    cout << "2、按照职工姓名查找：" <<endl;
    int s;
    cin>>s;
    if(s == 1)
    {
        int id;
        cout << "请输入编号" <<endl;
        cin>>id;

        int ret = this->IsExist(id);
        if(ret == -1)
        {
            cout << "未找到该员工" << endl;
        }
        else 
        {
            cout << "查找成功" << endl;
            this->m_EmpArray[ret]->showInfo();
        }
    }
    else if(s == 2)
    {
        string name;
        cout << "请输入姓名" <<endl;
        cin>>name;

        bool f =false;
        for(int i = 0; i < this->m_EmpNum; i ++ )
        {
            if(this->m_EmpArray[i]->m_Name == name)
            {
                cout << "查找成功,职工编号为:"
                    <<  this->m_EmpArray[i]->m_Id
                    << "职工信息如下" << endl;

                f = true;
                this->m_EmpArray[i]->showInfo();
            }
        }
        if(!f)
        {
            cout << "查找失败，查无此人" <<endl;
        }
    }
    else
    {
        cout<<"输入选项有误"<<endl;
    }

    system("pause");
    system("cls");
}

bool cmp1(worker *a, worker *b)
{   
    return a->m_Id < b->m_Id;
}

bool cmp2(worker *a, worker *b)
{   
    return a->m_Id > b->m_Id;
}

void workerManager::Sort_Emp()
{
    if(this->m_FileIsEmpty)
    {
        cout << "文件不存在或记录为空" << endl;
        system("pause");
        system("cls"); 
    }
    else
    {
        cout << "请输入查找的方式" <<endl;
        cout << "1、按照职工编号升序" <<endl;
        cout << "2、按照职工编号降序" <<endl;

        int s;
        cin >> s;

        if(s == 1)
        {
            sort(this->m_EmpArray, this->m_EmpArray + this->m_EmpNum, cmp1);
        }
        else 
        {
            sort(this->m_EmpArray, this->m_EmpArray + this->m_EmpNum, cmp2);
        }

        cout << "排序成功，排序结果为：" << endl;

        this->save();
        this->show_Emp();
    }
}

void workerManager::clear_Emp()
{
    cout << "请确认清空" <<endl;
    cout << "1、确认" <<endl;
    cout << "2、取消" <<endl;

    int s = 0;
    cin>>s;

    if(s == 1)
    { 
        ofstream ofs;
        ofs.open(FILENAME, ios::trunc);
        ofs.close();

        if(this->m_EmpArray != NULL)
        {
            for(int i = 0; i < this->m_EmpNum; i ++ )
            {
                if(this->m_EmpArray[i] != NULL)
                {
                    delete this->m_EmpArray[i];
                    this->m_EmpArray[i] = NULL;
                }
            }
            delete [] this->m_EmpArray;
            this->m_EmpArray = NULL;

            this->m_EmpNum = 0;
            this->m_FileIsEmpty = true;
        }
        cout << "清空成功" << endl;
    }
    system("pause");
    system("cls");
}