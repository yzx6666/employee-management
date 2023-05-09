#include <iostream>
#include "../include/workerManager.h"
#include "../include/worker.h"
#include "../include/employee.h"
#include "../include/boss.h"
#include "../include/manager.h" 

using namespace std;


int main()
{

	workerManager wm;

	int choice;
	while (true)
	{	
		wm.show_Menu();
		cout<<"ÇëÊäÈëÄãµÄÑ¡Ôñ"<<endl;
		cin>>choice;
		switch (choice)
		{
		case 0:
			wm.exitSystem();
			break;
		case 1:
			wm.Add_Emp();
			break;
		case 2:
			wm.show_Emp();
			break;
		case 3:
			wm.Del_Emp();
			break;
		case 4:
			wm.Mod_Emp();
			break;
		case 5:
			wm.Find_Emp();
			break;
		case 6:
			wm.Sort_Emp();
			break;
		case 7:
			wm.clear_Emp();
			break;
		default:
			break;
		}
	}
	
	system("pause");
	return 0;
}