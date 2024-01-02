#include <iostream>
#include <string>
using namespace std;

class Person{
public:
    Person(string name, int rZone, bool hasJob, int n);

    string getName();
    int getRZone();
    int getNum();
    bool getHasJob();

    void setName(string);
    void setRZone(int);
    void setNum(int);
    void setHasJob(bool);

private:
    string pName;
    int pNum;
    int zone;
    bool job;
};