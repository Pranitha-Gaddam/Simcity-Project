#include "Person.h"
#include "Persons.h"

const static int pID = 1;
int pGen = 0;
int save;
bool check;

void Persons::addPerson(int cellPos) {
    Person* temp;
    string named = "Person"; bool work = false;

    if(personList.size() > 0){
        save = personList.back()->getNum();
        check = true;
    } else {
        check = false;
    }

    int pGen2 = pID+pGen;

    if(check){
        temp = new Person(named, cellPos, work, save+1);
    } else {
        temp = new Person(named, cellPos, work, pGen2);
    }

    personList.push_back(temp);
    pGen++;
}

void Persons::givePerJob() {
    for(int i = 0; i < personList.size(); i++) {
        if(!(personList[i]->getHasJob())){personList[i]->setHasJob(true); break;}
    }
}