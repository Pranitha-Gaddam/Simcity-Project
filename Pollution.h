#ifndef POLLUTION_H
#define POLLUTION_H

#include <iostream>
#include <vector>
#include <list>
#include "cell.h"
using namespace std;

void updatePollution(vector<vector<struct Cell>> &vector, int rows, int cols);
//takes in the list of industrial cells produced in main() and updates the pollution values to be equal to their populations

void pollutionSpreadSrc(vector<vector<struct Cell>> &vector, int rows, int cols);
//takes in the city vector and its dimensions from main() and adjusts pollution for cells adjacent to industrial cells

void pollutionSpreadAdj(vector<vector<struct Cell>> &vector, int rows, int cols);
//takes the city vector and its dimensions from main() and adjusts pollution levels for cells adjacent to other non-industrial cells

int sumPollution(vector<vector<struct Cell>> &city, int top_bound_x, int top_bound_y, int bottom_bound_x, int bottom_bound_y);
//generates the sum of the pollution in the region

#endif
