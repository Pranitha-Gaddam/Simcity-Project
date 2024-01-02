#include "power.h"

void undoUpdate(vector<vector<struct Cell>> &city, int city_cols, int city_rows)
{
  for (int i = 0; i < city_cols; i++)
    for (int j = 0; j < city_rows; j++)
      city[i][j].updated_this_step = false;

  return;
}

void checkForPower(vector<vector<struct Cell>> &city, int city_cols, int city_rows)
{
  for (int i = 0; i < city_cols; i++)
    for (int j = 0; j < city_rows; j++)
      for (int k = ((i - 1) >= 0) ? (i - 1) : i; k <= (((i + 1) >= city_cols) ? i : i + 1); k++)
      {
        if (city[i][j].next_to_power)
          continue;
          
        for (int l = ((j - 1) >= 0) ? j - 1 : j; l <= (((j + 1) >= city_rows) ? j : j + 1); l++)
          if (city[i][j].next_to_power)
            continue;
          else if (city[k][l].cell_type == 'T' || city[k][l].cell_type == 'P')
            city[i][j].next_to_power = true;
      }
  return;
}

void updateAdjacentPop(vector<vector<struct Cell>> &city, int city_cols, int city_rows)
{
  int adj_pop = 0;
  int cells_with_equal_pop = 0;
  for (int i = 0; i < city_cols; i++)
    for (int j = 0; j < city_rows; j++)
    {
      for (int k = ((i - 1) >= 0) ? (i - 1) : i; k <= (((i + 1) >= city_cols) ? i : i + 1); k++)
        for (int l = ((j - 1) >= 0) ? j - 1 : j; l <= (((j + 1) >= city_rows) ? j : j + 1); l++)
        {  
          if (i == k && j == l) continue;
          
          adj_pop += city[k][l].population;
          if (city[k][l].population >= city[i][j].population)
            cells_with_equal_pop += 1;
        }

      city[i][j].adjacent_cell_population = adj_pop;
      city[i][j].adjacent_cells_equal_pop = cells_with_equal_pop;
      adj_pop = 0;
      cells_with_equal_pop = 0;
    }

  return;
}

int checkForUpdate(vector<vector<struct Cell>> &city, int city_cols, int city_rows)
{
  for (int i = 0; i < city_cols; i++)
    for (int j = 0; j < city_rows; j++)
      if (city[i][j].updated_this_step)
        return 1;
  
  return 0;
}