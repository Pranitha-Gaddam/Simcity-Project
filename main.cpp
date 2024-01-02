/*  SimCity main
 *  Handles the reading of config and region file
 */
#include <iostream>
#include <vector>
#include <list>
#include "cell.h"
#include "io.h"
#include "power.h"
#include "Residential.h"
#include "Industrial.h"
#include "Commercial.h"
#include "Pollution.h"

using namespace std;

int main(int argc, char* argv[])
{
  string config_file_name;
  string region_file_name;

  int max_steps;
  int refresh_rate;

  vector<vector<struct Cell>> city;
  
  //Lists were not implemented. May be implemented in future versions.
  list<struct Cell> resident_list;
  list<struct Cell> industrial_list;
  list<struct Cell> commercial_list;

  int total_population = 0;
  int total_goods = 0;
  int unemployed_workers = 0;
  int total_pollution = 0;

  int city_rows, city_cols;
  int top_bound_x, top_bound_y, bottom_bound_x, bottom_bound_y;

  if (argc == 2)
    config_file_name = argv[1];
  else
  {
    //Get config file name from the user
    cout << "Enter the name of the simulation config file: ";
    getline(cin, config_file_name);
  }

  //Get file name until given name is valid
  while (!readConfigFile(config_file_name, region_file_name, max_steps, refresh_rate))//Prompt user for file until the file name is valid
  {
    cout << "\n\'" << config_file_name << "\' is an invalid file name. Please try again: ";
    getline(cin, config_file_name);
  }
  readRegionFile(config_file_name, region_file_name, city ,resident_list, industrial_list, commercial_list);

  city_cols = city.size();
  city_rows = city.at(0).size();

  //Print the initial state of the city
  cout << "\nInitial state" << endl;
  printCity(city);
  cout << "Available workers: " << unemployed_workers << endl;
  cout << "Available goods:   " << total_goods << endl << endl;

  checkForPower(city, city_cols, city_rows);

  //Increment time steps
  for (int step_count = 1; step_count <= max_steps; step_count++)
  {
    Commercial(city, city_rows, city_cols, unemployed_workers, total_goods);
    Industrial(city, city_rows, city_cols, unemployed_workers, total_goods);
    popSize1To4(city, unemployed_workers, total_population);

    if (step_count % refresh_rate == 0)
    {
      cout << "\nStep #" << step_count << endl;
      printCity(city);
      cout << "Available workers: " << unemployed_workers << endl;
      cout << "Available goods:   " << total_goods << endl << endl;
    }

    if (!checkForUpdate(city, city_cols, city_rows))
      break;

    undoUpdate(city, city_cols, city_rows);
    updateAdjacentPop(city, city_cols, city_rows);
  }

  cout << "\nFinal state:" << endl;
  printCity(city);

  cout << "Total population: " << total_population << endl;
  int t = sumPopulation(city, 0, 0, city_cols - 1, city_rows - 1, 'R');
  cout << "Residential population: " << t << endl;
  t = sumPopulation(city, 0, 0, city_cols - 1, city_rows - 1, 'I');
  cout << "Industrial population: " << t << endl;
  t = sumPopulation(city, 0, 0, city_cols - 1, city_rows - 1, 'C');
  cout << "Commercial population: " << t << endl;

  updatePollution(city, city_cols, city_rows);
  pollutionSpreadSrc(city, city_cols, city_rows);
  pollutionSpreadAdj(city, city_cols, city_rows);

  cout << "\nFinal Pollution: " << endl;
  printPollution(city);

  t = sumPollution(city, 0, 0, city_cols - 1, city_rows - 1);
  cout << "Total pollution: " << t << endl;
  
  cout << "\nEnter the coordinates of the area you'd like to analye." << endl;
  cout << "Enter it as \"(1,2)(3,4)\" without the quotes: ";
  do 
  {
    getBounds(city_cols, city_rows, top_bound_x, top_bound_y, bottom_bound_x, bottom_bound_y);
  }
  while (!checkBounds(city_cols, city_rows, top_bound_x, top_bound_y, bottom_bound_x, bottom_bound_y));

  cout << "\nIn the bounds ";
  cout << "(" << top_bound_x << "," << top_bound_y << ")(" << bottom_bound_x << "," << bottom_bound_y << ")," << endl;

  t = sumPopulation(city, top_bound_x, top_bound_y, bottom_bound_x, bottom_bound_y, 'R');
  cout << "Residential population: " << t << endl;
  t = sumPopulation(city, top_bound_x, top_bound_y, bottom_bound_x, bottom_bound_y, 'I');
  cout << "Industrial population: " << t << endl;
  t = sumPopulation(city, top_bound_x, top_bound_y, bottom_bound_x, bottom_bound_y, 'C');
  cout << "Commercial population: " << t << endl;
  
  t = sumPollution(city, top_bound_x, top_bound_y, bottom_bound_x, bottom_bound_y);
  cout << "Pollution: " << t << endl;
  
  return 1;
}