#ifndef INDUSTRIAL_H
#define INDUSTRIAL_H

#include <iostream>
#include <vector>
#include "cell.h"
#include "Commercial.h"
using namespace std;

void Industrial(vector<vector<struct Cell>> &city, int rows, int cols, int &numWorkers, int &numGoods);

bool isAdjacent(vector<vector<struct Cell>> &city, int rows, int cols, int x, int y, int cellNum);

int availableI(Cell &currCell, int &workers, int &goods);

int industrialPopulation(const vector<vector<struct Cell>> &city, int rows, int cols);

void produceGoods(const vector<vector<struct Cell>> &city, int rows, int cols, int &goods);

#endif

