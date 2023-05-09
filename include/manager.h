#include <iostream>
#include <string>
#include "worker.h"

using namespace std;

class manager: public worker
{
public:
    manager(int id, string name, int dId);

    void showInfo();

    string getDeptName();
};
