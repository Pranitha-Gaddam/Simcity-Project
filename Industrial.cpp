#include "Industrial.h"

void Industrial(vector<vector<struct Cell>> &city, int rows, int cols, int &numWorkers, int &numGoods)
{
	for(int i=0; i<rows; ++i)
	{
		for(int j=0; j<cols; ++j)
		{
			if(city[i][j].cell_type == 'I')
			{
				if(city[i][j].population == 0) //case for if population is equal to 0
				{
					if((city[i][j].next_to_power == true && numWorkers >= 2) || (isAdjacent(city, rows, cols, i, j, 1) && numWorkers >= 2))
					{
						if (availableI(city[i][j], numWorkers, numGoods))
						{
							Commercial(city, rows, cols, numWorkers, numGoods);
						}
					}
				}
				else if(city[i][j].population == 1) //case for if population is equal to 1
				{
					if(isAdjacent(city, rows, cols, i, j, 2) && numWorkers >= 2)
					{
						if (availableI(city[i][j], numWorkers, numGoods))
						{
							Commercial(city, rows, cols, numWorkers, numGoods);
						}
					}
				}
				else if(city[i][j].population == 2) //case for if population is equal to 2
				{
					if(isAdjacent(city, rows, cols, i, j, 4) && numWorkers >= 2)
					{
						if (availableI(city[i][j], numWorkers, numGoods))
						{
							Commercial(city, rows, cols, numWorkers, numGoods);
						}
					}
				}
			}
		}
	}

	produceGoods(city, rows, cols, numGoods);
	return;
}

bool isAdjacent(vector<vector<struct Cell>> &city, int rows, int cols, int x, int y, int cellNum)
{
	int count = 0;

	if (y + 1 < cols) //Checks cells to the right for adjacency
	{
		if ((city[x][y+1].cell_type == 'I' || city[x][y+1].cell_type == 'R' || city[x][y+1].cell_type == 'C') && city[x][y+1].population >= 1)
		{
			count++;
		}
	}

	
	if (y - 1 >= 0) //Checks cells to the left for adjacency 
	{
		if ((city[x][y-1].cell_type == 'I' || city[x][y-1].cell_type == 'R' || city[x][y-1].cell_type == 'C') && city[x][y-1].population >= 1)
		{
			count++;
		}
}
	if (x - 1 >= 0) //Checks cells above for adjacency
	{
		if ((city[x-1][y].cell_type == 'I' || city[x-1][y].cell_type == 'R' || city[x-1][y].cell_type == 'C') && city[x-1][y].population >= 1)
		{
			count++;
		}

		if (y + 1 < cols && (city[x-1][y+1].cell_type == 'I' || city[x-1][y+1].cell_type == 'R' || city[x-1][y+1].cell_type == 'C') && city[x-1][y+1].population >= 1)
		{
			count++;
		}

		if (y - 1 >= 0 && (city[x-1][y-1].cell_type == 'I' || city[x-1][y-1].cell_type == 'R' || city[x-1][y-1].cell_type == 'C') && city[x-1][y-1].population >= 1)
		{
			count++;
		}
	}

	if (x + 1 < rows) //Checks cells below for adjacency
	{
		if ((city[x+1][y].cell_type == 'I' || city[x+1][y].cell_type == 'R' || city[x+1][y].cell_type == 'C') && city[x+1][y].population >= 1)
		{
			count++;
		}

		if (y + 1 < cols && (city[x+1][y+1].cell_type == 'I' || city[x+1][y+1].cell_type == 'R' || city[x+1][y+1].cell_type == 'C') && city[x+1][y+1].population >= 1)
		{
			count++;
		}

		if (y - 1 >= 0 && (city[x+1][y-1].cell_type == 'I' || city[x+1][y-1].cell_type == 'R' || city[x+1][y-1].cell_type == 'C') && city[x+1][y-1].population >= 1)
		{
			count++;
		}
	}

	return count >= cellNum;
}


int availableI(Cell &currCell, int &workers, int &goods)
{
  if (currCell.updated_this_step)
    return 0;
	
	if (workers > 1) //Check if workers are availableI
	{
		currCell.updated_this_step = true;
    currCell.population++;
		goods += currCell.population;
		workers -= 2;
		return 1;
	}

	return 0;
}


int industrialPopulation(const vector<vector<struct Cell>> &city, int rows, int cols)
{
    int industrialPop = 0;

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if (city[i][j].cell_type == 'I')
            {
                industrialPop += city[i][j].population;
            }
        }
    }

    return industrialPop;
}

void produceGoods(const vector<vector<struct Cell>> &city, int rows, int cols, int &goods)
{
	for (int i = 0; i < rows; ++i)
  	for (int j = 0; j < cols; ++j)
		{
			if (city[i][j].cell_type != 'I' || city[i][j].updated_this_step) continue;

			goods += city[i][j].population;
		}
        
}

















			



	

