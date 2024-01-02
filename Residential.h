#ifndef RESIDENTIAL_H
#define RESIDENTIAL_H

#include "Person.h"
#include "Persons.h"
#include <list>
#include <iterator>
#include <iostream>
#include "cell.h"
using namespace std;

int totalPop(vector<vector<struct Cell> > &c);

int getAdj(vector<vector<struct Cell> > &c, int w, int x);

int getAdj3P4(vector<vector<struct Cell> > &c, int w);

void popSize0(vector<vector<struct Cell> > &c, int &pop);

void popSize1To4(vector<vector<struct Cell> > &cc, int &unemp,int &pop);

#endif