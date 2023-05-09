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
        cout<<"�ļ�������"<<endl;
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
        cout<<"�ļ�Ϊ��"<<endl;
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
    cout<<"********** ��ӭʹ��ְ������ϵͳ*****************"<<endl;
    cout<<"**********    0.�˳��������  ******************"<<endl;
    cout<<"**********    1.����ְ����Ϣ  ******************"<<endl;
    cout<<"**********    2.��ʾְ����Ϣ  ******************"<<endl;
    cout<<"**********    3.ɾ��ְ����Ϣ  ******************"<<endl;
    cout<<"**********    4.�޸�ְ����Ϣ  ******************"<<endl;
    cout<<"**********    5.����ְ����Ϣ  ******************"<<endl;
    cout<<"**********    6.���ձ������  ******************"<<endl;
    cout<<"**********    7.��������ĵ�  ******************"<<endl;
    cout<<"************************************************"<<endl;
    cout<<endl;
}

void workerManager::exitSystem()
{
    cout<<"��ӭ�´�ʹ��" <<endl;

    system("pause");
    exit(0);
}

void workerManager::Add_Emp()
{
    cout<<"���������Ա������"<<endl;

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
            
            cout << "�������" << i + 1 << "����ְ���ı��" << endl;  
            cin >> id;
            while (this->IsExist(id) != -1)
            {
                cout << "�ñ��Ա���Ѵ��ڣ��������������" << endl;
                cin >> id;
            }
            cout << "�������" << i + 1 << "����ְ��������" << endl;
            cin >> name;
            cout << "��ѡ���ְ����λ" << endl;
            cout << "1����ͨԱ��" << endl;
            cout << "2������" << endl;
            cout << "3���ϰ�" << endl;
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
            cout<<"���"<< addNum <<"��Ա���ɹ�"<<endl;
    }
    else
    {
        cout<<"������������"<<endl;
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
        cout<< "�ļ������ڻ��¼Ϊ��" <<endl;
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
        cout << "�ļ������ڻ��¼Ϊ��" << endl;
        system("pause");
        system("cls");
        return ;
    }

    int id, idx = -1;
    cout << "��������Ҫɾ����ְ�����" << endl;
    cin>>id;

    idx = this->IsExist(id);
    if(idx == -1)
    {
        cout << "ɾ��ʧ�ܣ�δ�ҵ���Ա��" << endl;
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

        cout << "ɾ���ɹ�" << endl;
    }
    system("pause");
    system("cls");
}

void workerManager::Mod_Emp()
{
    if(this->m_FileIsEmpty)
    {
        cout << "�ļ������ڻ��¼Ϊ��" << endl;
        system("pause");
        system("cls");
        return ;
    }

    int id, idx = -1;
    cout << "��������Ҫ�޸ĵ�ְ�����" << endl;
    cin>>id;

    idx = this->IsExist(id);
    if(idx == -1)
    {
        cout << "�޸�ʧ�ܣ�δ�ҵ���Ա��" << endl;
    }
    else 
    {
        delete this->m_EmpArray[idx];
        this->m_EmpArray[idx] = NULL;


        int newId, newDid;
        string newName;

        cout << "���ҵ�" << id << "��ְ�����������µ�ְ����" << endl;
        cin>> newId;
        cout << "������������" << endl;
        cin >> newName;
        cout << "��ѡ���ְ����λ" << endl;
        cout << "1����ͨԱ��" << endl;
        cout << "2������" << endl;
        cout << "3���ϰ�" << endl;
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

        cout << "�޸ĳɹ�" << endl;
    }
    system("pause");
    system("cls");
}

void workerManager::Find_Emp()
{
    if(this->m_FileIsEmpty)
    {
        cout << "�ļ������ڻ��¼Ϊ��" << endl;
        system("pause");
        system("cls"); 
        return ;
    }

    cout << "��������ҵķ�ʽ" <<endl;
    cout << "1������ְ����Ų��ң�" <<endl;
    cout << "2������ְ���������ң�" <<endl;
    int s;
    cin>>s;
    if(s == 1)
    {
        int id;
        cout << "��������" <<endl;
        cin>>id;

        int ret = this->IsExist(id);
        if(ret == -1)
        {
            cout << "δ�ҵ���Ա��" << endl;
        }
        else 
        {
            cout << "���ҳɹ�" << endl;
            this->m_EmpArray[ret]->showInfo();
        }
    }
    else if(s == 2)
    {
        string name;
        cout << "����������" <<endl;
        cin>>name;

        bool f =false;
        for(int i = 0; i < this->m_EmpNum; i ++ )
        {
            if(this->m_EmpArray[i]->m_Name == name)
            {
                cout << "���ҳɹ�,ְ�����Ϊ:"
                    <<  this->m_EmpArray[i]->m_Id
                    << "ְ����Ϣ����" << endl;

                f = true;
                this->m_EmpArray[i]->showInfo();
            }
        }
        if(!f)
        {
            cout << "����ʧ�ܣ����޴���" <<endl;
        }
    }
    else
    {
        cout<<"����ѡ������"<<endl;
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
        cout << "�ļ������ڻ��¼Ϊ��" << endl;
        system("pause");
        system("cls"); 
    }
    else
    {
        cout << "��������ҵķ�ʽ" <<endl;
        cout << "1������ְ���������" <<endl;
        cout << "2������ְ����Ž���" <<endl;

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

        cout << "����ɹ���������Ϊ��" << endl;

        this->save();
        this->show_Emp();
    }
}

void workerManager::clear_Emp()
{
    cout << "��ȷ�����" <<endl;
    cout << "1��ȷ��" <<endl;
    cout << "2��ȡ��" <<endl;

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
        cout << "��ճɹ�" << endl;
    }
    system("pause");
    system("cls");
}