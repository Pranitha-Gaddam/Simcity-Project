#ifndef COMMERCIAL_H
#define COMMERCIAL_H

using namespace std;

void Commercial(vector<vector<struct Cell>> &city, int cityRows, int cityCols, int &numGoods, int &numWorkers);

bool adjPopulation(vector<vector<struct Cell>> &city, int cityRows, int cityCols, int cellRow, int cellCol, int numCellsToFind);

void available(Cell &currCell, int &goods, int &workers);

#endif