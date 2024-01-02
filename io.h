#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <list>
#include "cell.h"
using namespace std;

/**
 *  @brief  Read contents of config file into variables
 *  @param[in] config_file_name  Name of the config file. Provided by user
 *  @param[out] region_file_name  Name of the region file. Found in config file
 *  @param[out] max_steps Highest number of steps the simulation can run
 *  @param[out] refresh_rate How often to print the city
 *  @return 1 on success, 0 on fail
 *
 *  @details Uses ifstream to open the file provided by config_file_name. Returns 0
 *  if ifstream failbit is true. Otherwise it reads in the region file name,
 *  the max steps, and refresh rate from the config file into appropriate
 *  variables.
 */
int readConfigFile(string &config_file_name, string &region_file_name, int &max_steps, int &refresh_rate);

/**
 * @brief Read contents of region file into 2D array and linked lists
 * 
 * @param config_file_name  Name of the config file
 * @param region_file_name  Name of the region file
 * @param city Main 2D array
 * @param resident_list Linked list containing ordered resident cells
 * @param industrial_list Linked list containing ordered industial cells
 * @param commercial_list Linked list containing ordered commercial cells
 * @return 1 on success
 * 
 * @details
 */
int readRegionFile(string &config_file_name, string &region_file_name, vector<vector<struct Cell>> &city, list<struct Cell> &resident_list, list<struct Cell> &industrial_list, list<struct Cell> &commercial_list);

/**
 * @brief Get the bounds for the subsection the user wants to analyze
 * 
 * @param city_cols 
 * @param city_rows 
 * @param top_bound_x 
 * @param top_bound_y 
 * @param bottom_bound_x 
 * @param bottom_bound_y 
 */
void getBounds(int &city_cols, int &city_rows, int &top_bound_x, int &top_bound_y, int &bottom_bound_x, int &bottom_bound_y);

/**
 * @brief Check the given bounds to make sure they are within the bounds of the given city
 * 
 * @param city_cols 
 * @param city_rows 
 * @param top_bound_x 
 * @param top_bound_y 
 * @param bottom_bound_x 
 * @param bottom_bound_y 
 * @return int 
 */
int checkBounds(int &city_cols, int &city_rows, int &top_bound_x, int &top_bound_y, int &bottom_bound_x, int &bottom_bound_y);

/**
 * @brief Print the letter/populatin of each cell in the city to the terminal
 * 
 * @param city Main 2D array
 */
void printCity(vector<vector<struct Cell>> city);

/**
 * @brief Print each cell in the given list to the terminal
 * 
 * @param list Linked list containing ordered Cells
 */
void printList(list<struct Cell> list);

/**
 * @brief Sum the population of a given cell type within a given bounds
 * 
 * @param city 
 * @param top_bound_x 
 * @param top_bound_y 
 * @param bottom_bound_x 
 * @param bottom_bound_y 
 * @param c 
 * @return int 
 */
int sumPopulation(vector<vector<struct Cell>> &city, int top_bound_x, int top_bound_y, int bottom_bound_x, int bottom_bound_y, char c);

/**
 * @brief Print the city and its pollution
 * 
 * @param city 
 */
void printPollution(vector<vector<struct Cell>> city);

#endif