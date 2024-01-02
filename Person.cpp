#include "Person.h"

Person::Person(string name, int rZone, bool hasJob, int n){
    string result = name + to_string(n);
    pName = result;
    zone = rZone;
    job = hasJob;
}

string Person::getName(){return pName;}
int Person::getRZone(){return zone;}
int Person::getNum(){return pNum;}
bool Person::getHasJob(){return job;}

void Person::setName(string theName){pName = theName;}
void Person::setRZone(int theZone){zone = theZone;}
void Person::setNum(int theNum){pNum = theNum;}
void Person::setHasJob(bool theJob){job = theJob;}