#ifndef CELLS_H
#define CELLS_H

/**
 * @brief Life blood of this project
 * 
 */
struct Cell
{
  char cell_type;
  int population = 0;
  bool next_to_power = false;
  int adjacent_cells_equal_pop = 0;
  int adjacent_cell_population = 0;
  int pollution_level = 0;
  int cell_position = 0;
  bool updated_this_step = false;
};

#endif