#ifndef POWER_H
#define POWER_H

#include <iostream>
#include <vector>
#include <list>
#include "cell.h"
using namespace std;

/**
 * @brief Check if a cell is adjacent to a power line/plant
 * 
 * @param city 
 * @param city_cols 
 * @param city_rows 
 */
void checkForPower(vector<vector<struct Cell>> &city, int city_cols, int city_rows);

/**
 * @brief Reset the updated_this_step back to false for each cell
 * 
 * @param city 
 * @param city_cols 
 * @param city_rows 
 */
void undoUpdate(vector<vector<struct Cell>> &city, int city_cols, int city_rows);

/**
 * @brief Total a cells adjacent population and count the cells that have >= population
 * 
 * @param city 
 * @param city_cols 
 * @param city_rows 
 */
void updateAdjacentPop(vector<vector<struct Cell>> &city, int city_cols, int city_rows);

/**
 * @brief Check if any cells were updated in the given step
 * 
 * @param city 
 * @param city_cols 
 * @param city_rows 
 * @return int 
 */
int checkForUpdate(vector<vector<struct Cell>> &city, int city_cols, int city_rows);

#endif