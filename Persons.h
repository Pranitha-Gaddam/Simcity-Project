#include <vector>
#include <cmath>
#include "cell.h"
using namespace std;

class Person;

class Persons{
public:
    void addPerson(int);
    void givePerJob();

private:
vector<Person*> personList;
};