/* Name: Ryan Arnold
Date: 4/2/23
Email: RyanArnold2@my.unt.edu */

#include <iostream>
#include <vector>
#include <list>
#include "cell.h"
#include "Pollution.h"
using namespace std;

void updatePollution(vector<vector<struct Cell>> &vector, int rows, int cols) { //pass industrial_list from main() for this
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++) //vector iteration loops
			if (vector[i][j].cell_type == 'I')
				vector[i][j].pollution_level = vector[i][j].population; //for each cell in the list, updates the pollution level to be equal to the population

	return;
}

void pollutionSpreadSrc(vector<vector<struct Cell>> &vector, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) { //vector iteration loops
			if (vector[i][j].cell_type == 'I') {
				//if cell type is industrial, check adjacent cells
				for (int k = i - 1; k < i + 2; ++k) {
					if (i + 2 > cols) continue;
					for (int l = j - 1; l < j + 2; ++l) {
						if (j + 2 > rows) continue;
						if (k < 0) {
							k = 0;
						} 

						if (l < 0) {
							l = 0;
						} //if k or l are less than 0, increases them to 0

						if (k > rows) {
							break;
						} //if k is greater than the number of rows, breaks the loop (no more possible cells to check)

						if (l > cols) {
							l = j - 1;
							k += 1;
						} //if l is greater than the number of columns, resets l and increments k (this will probably cause issues)
						
						//if cell is not industrial, check pollution value
						if (vector[k][l].cell_type != 'I') {
							if (vector[k][l].pollution_level <= vector[i][j].pollution_level - 2) {
								vector[k][l].pollution_level = vector[i][j].pollution_level - 1;
							} //if cell pollution is less than or equal to the source pollution - 2, increase the cell pollution to the source - 1

							if (vector[k][l].pollution_level >= vector[i][j].pollution_level) { 
								if (vector[i][j].pollution_level == 0) {
									vector[k][l].pollution_level = 0;
								} //if the adjacent cell has a higher pollution level and the source pollution is 0, sets adjacent pollution to 0

								else {
									vector[k][l].pollution_level = vector[i][j].pollution_level - 1;
								} //otherwise, sets adjacent pollution to source pollution - 1
							}
						}
						else {
							if (vector[k][l].cell_type == 'I') {
								if (vector[k][l].pollution_level < (vector[i][j].pollution_level - 1))
									vector[k][l].pollution_level = vector[i][j].pollution_level - 1;
							}
						}
					}
				}
			}
		}
	}
	
	return;
}

void pollutionSpreadAdj(vector<vector<struct Cell>> &vector, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (vector[i][j].cell_type != 'I') {
				for (int k = i - 1; k < i + 2; ++k) {
					if (i + 2 > cols) continue;
					for (int l = j - 1; l < j + 2; ++l) { //same loop code as pollutionSpreadSrc(), looking for non-industrial cells
						if (j + 2 > rows) continue;
						if (k < 0) {
							k = 0;
						} 

						if (l < 0) {
							l = 0;
						} //if k or l are less than 0, increases them to 0

						if (k > rows) {
							break;
						} //if k is greater than the number of rows, breaks the loop (no more possible cells to check)

						if (l > cols) {
							l = j - 1;
							k += 1;
						} //if l is greater than the number of columns, resets l and increments k (this will probably cause issues)
						
						//if adjacent cell has a pollution value of 2 or greater (unnecessary to do anything otherwise)
						if (vector[k][l].pollution_level > 1) {
							if (vector[i][j].pollution_level <= vector[k][l].pollution_level - 2) {
								vector[i][j].pollution_level = vector[k][l].pollution_level - 1;
							} //if cell pollution is less than or equal to the adjacent pollution - 2, increase the cell pollution to the source - 1
						}

						if (vector[k][l].cell_type == 'I' && vector[k][l].pollution_level < vector[i][j].pollution_level) {
							if (vector[k][l].pollution_level == 0) {
								vector[i][j].pollution_level = 0;
							} //if adjacent cell pollution level is less than the cell and equal to 0, sets cell pollution to 0

							else {
								vector[i][j].pollution_level = vector[k][l].pollution_level - 1; 
							} //otherwise, sets cell pollution equal to adjacent cell pollution - 1
						}
					}
				}
			}
		}
	}

	return;
} //thought about it, no longer want to think about it

int sumPollution(vector<vector<struct Cell>> &city, int top_bound_x, int top_bound_y, int bottom_bound_x, int bottom_bound_y)
{
	int total = 0;
  for (int i = top_bound_x; i <= bottom_bound_x; i++)
      for (int j = top_bound_y; j <= bottom_bound_y; j++)
        total += city[i][j].pollution_level;

  return total;
}