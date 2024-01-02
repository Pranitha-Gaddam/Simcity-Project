#include <iostream>
#include <vector>
#include "Commercial.h"
#include "cell.h"

using namespace std;

void Commercial(vector<vector<struct Cell>> &city, int cityRows, int cityCols, int &numWorkers, int &numGoods)
{
    for (int i = 0; i < cityRows; i++)// looping through the city to check for 'C'
    {
        for (int j = 0; j < cityCols; j++)
        {
            if (city[i][j].updated_this_step)// FIRST CASE: When cell has 0 population
                continue;
            
            if (city[i][j].cell_type == 'C')
            {
                if (city[i][j].population == 0)// FIRST CASE: When cell has 0 population
                {
                    if (city[i][j].next_to_power == true) // checks if the cell is next to a powerline
                    {
                        available(city[i][j], numGoods, numWorkers); // if true, changes population, goods and workers accordingly
                    }
                    else
                    {
                        if (adjPopulation(city, cityRows, cityCols, i, j, 1)) // checks if cell has atleast 1 adjacent cell with a population >=1
                        {
                            available(city[i][j], numGoods, numWorkers); // if true, changes population, goods, and workers accordingly
                        }
                    }
                }

                if (city[i][j].population == 1) // SECOND CASE: When cell has 1 population
                {
                    if (adjPopulation(city, cityRows, cityCols, i, j, 2)) // checks if cell has atleast 2 adjacent cells with a population >=1
                    {
                        available(city[i][j], numGoods, numWorkers); // if true, changes population, goods, and workers accordingly
                    }
                }
            }
        }
    }
    return;
}

bool adjPopulation(vector<vector<struct Cell>> &city, int cityRows, int cityCols, int cellRow, int cellCol, int numCellsToFind)
{
    int count = 0; // a counter to keep track of the number of adjacent cells with population >=1
    /*
    The following 8 char variables are created to represent the cell types of each of the adjacent cells as following:

        l1      m1      r1
        l2   currCell   r2
        l3      m2      r3

        All 8 char variables are initialized to 'z' and changed later, if conditions are satisfied
    */
    char r3Type = 'z';
    char m2Type = 'z';
    char l3Type = 'z';
    char r1Type = 'z';
    char m1Type = 'z';
    char l1Type = 'z';
    char r2Type = 'z';
    char l2Type = 'z';

    if (cellCol + 1 < cityCols) // checks if r1, r2, r3 exist
    {
        if (cellRow - 1 >= 0)
        {
            r1Type = city[cellRow - 1][cellCol + 1].cell_type;

            if ((r1Type == 'I' || r1Type == 'R' || r1Type == 'C'))
            {
                if (city[cellRow - 1][cellCol + 1].population >= 1) // checks if r1 has population >=1 and increments count
                {
                    count++;
                }
            }
        }

        r2Type = city[cellRow][cellCol + 1].cell_type;
        if (r2Type == 'I' || r2Type == 'R' || r2Type == 'C')
        {
            if (city[cellRow][cellCol + 1].population >= 1) // checks if r2 has population >=1 and increments count
            {
                count++;
            }
        }

        if (cellRow + 1 < cityRows)
        {
            r3Type = city[cellRow + 1][cellCol + 1].cell_type;
            if ((r3Type == 'I' || r3Type == 'R' || r3Type == 'C'))
            {
                if (city[cellRow + 1][cellCol + 1].population >= 1) // checks if r3 has population >=1 and increments count
                {
                    count++;
                }
            }
        }
    }

    if (cellRow - 1 >= 0)
    {
        m1Type = city[cellRow - 1][cellCol].cell_type;
        if ((m1Type == 'I' || m1Type == 'R' || m1Type == 'C'))
        {
            if (city[cellRow - 1][cellCol].population >= 1) // checks if m1 has population >=1 and increments count
            {
                count++;
            }
        }
    }

    if (cellRow + 1 < cityRows)
    {
        m2Type = city[cellRow + 1][cellCol].cell_type;
        if ((m2Type == 'I' || m2Type == 'R' || m2Type == 'C'))
        {
            if (city[cellRow + 1][cellCol].population >= 1) // checks if m2 has population >=1 and increments count
            {
                count++;
            }
        }
    }

    if (cellCol - 1 >= 0)
    {

        if (cellRow - 1 >= 0)
        {
            l1Type = city[cellRow - 1][cellCol - 1].cell_type;
            if ((l1Type == 'I' || l1Type == 'R' || l1Type == 'C'))
            {
                if (city[cellRow - 1][cellCol - 1].population >= 1) // checks if l1 has population >=1 and increments count
                {
                    count++;
                }
            }
        }

        l2Type = city[cellRow][cellCol - 1].cell_type;
        if (l2Type == 'I' || l2Type == 'R' || l2Type == 'C')
        {
            if (city[cellRow][cellCol - 1].population >= 1) // checks if l2 has population >=1 and increments count
            {
                count++;
            }
        }

        if (cellRow + 1 < cityRows)
        {
            l3Type = city[cellRow + 1][cellCol - 1].cell_type;
            if ((l3Type == 'I' || l3Type == 'R' || l3Type == 'C'))
            {
                if (city[cellRow + 1][cellCol - 1].population >= 1) // checks if l3 has population >=1 and increments count
                {
                    count++;
                }
            }
        }
    }

    if (count >= numCellsToFind) // checks if atleast n(numCellsToFind) adjacent cells have a population >=1 and returns true if true
    {
        return true;
    }
    return false;
}


void available(Cell &currCell, int &goods, int &workers)
{
    if (currCell.updated_this_step)
        return;

    if (goods > 0 && workers > 0)// checks if there is atleast 1 good and 1 worker available
    {
        currCell.updated_this_step = true;// sets 'updated_this_step' to true, and population is increased by 1 at the end of the timestep, for all cells that have this boolean value set to true// sets 'updated_this_step' to true, and population is increased by 1 at the end of the timestep, for all cells that have this boolean value set to true
        currCell.population++;
        goods--;// decreases goods by 1
        workers--;// decreases workers by 1
    }
    return;
}
