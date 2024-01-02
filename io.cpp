#include "io.h"
#include "regex"

int readConfigFile(string &config_file_name, string &region_file_name, int &max_steps, int &refresh_rate)
{
  ifstream config_file;
  string input_s;

  config_file.open(config_file_name, ifstream::in); //Open config file for reading
  if (config_file.fail()) return 0;

  try //Read config file, throw exception if unable to read a variable
  {
    getline(config_file, region_file_name);
    getline(config_file, input_s);
    max_steps = stoi(input_s);
    getline(config_file, input_s);
    refresh_rate = stoi(input_s);
  } catch (const invalid_argument e)
  {
    cout << "\nError reading config file.\n" << e.what() << " failed to create int" << endl;
    exit(-1);
  }
  config_file.close();

  return 1;
}

int readRegionFile(string &config_file_name, string &region_file_name, vector<vector<struct Cell>> &city, list<struct Cell> &resident_list, list<struct Cell> &industrial_list, list<struct Cell> &commercial_list)
{
  ifstream region_file;
  vector<struct Cell> city_row;
  string input_s;
  char input_c;

  region_file.open(region_file_name, ifstream::in);
  if (region_file.fail())
    throw invalid_argument("\'" + region_file_name + "\' inside of \'" + config_file_name + "\' is an invalid file name.");

  int residential_increment = 0;
  int industrial_increment = 0;
  int commercial_increment = 0;
  int count = 0;
  while (!region_file.eof())
  {
    getline(region_file, input_s);

    do
    {
      input_c =  input_s.front();
      city_row.emplace_back();
      city_row.at(city_row.size() - 1).cell_type = input_c;
      if (input_c == ' ')
        city_row.at(city_row.size() - 1).cell_type = 176;//(TODO) For testing purposes, remove later
      input_s.erase(0,2);
      city_row.at(city_row.size() - 1).cell_position = count;
      count++;

      switch (input_c)
      {
        case('R'):
          city_row.at(city_row.size() - 1).cell_position = residential_increment++;
          resident_list.emplace_back(city_row.at(city_row.size() - 1));
          break;
        case('I'):
          city_row.at(city_row.size() - 1).cell_position = industrial_increment++;
          industrial_list.emplace_back(city_row.at(city_row.size() - 1));
          break;
        case('C'):
          city_row.at(city_row.size() - 1).cell_position = commercial_increment++;
          commercial_list.emplace_back(city_row.at(city_row.size() - 1));
          break;
        default: break;
      };

    } while (!input_s.empty());
    city.emplace_back(city_row);
    city_row.clear();
  }
  region_file.close();

  return 1;
}

void getBounds(int &city_cols, int &city_rows, int &top_bound_x, int &top_bound_y, int &bottom_bound_x, int &bottom_bound_y)
{
  string input_s, sub;
  regex coord_format ("^((\\(\\d+,\\d+\\)){2})$");
  int index;
  
  getline(cin, input_s);
  while (regex_match(input_s, coord_format) != 1)
  {
    cout << "Invalid response. Make sure to format the" << endl;
    cout << "coordinates as \"(1,2)(3,4)\": ";
    getline(cin, input_s);
  }

  input_s.pop_back();
  input_s.erase(0,1);

  index = input_s.find_first_of(',');
  sub = input_s.substr(0, index);
  input_s.erase(0, (index + 1));
  top_bound_x = stoi(sub);

  index = input_s.find_first_of('(');
  sub = input_s.substr(0, index - 1);
  input_s.erase(0, (index + 1));
  top_bound_y = stoi(sub);

  index = input_s.find_first_of(',');
  sub = input_s.substr(0, index);
  input_s.erase(0, (index + 1));
  bottom_bound_x = stoi(sub);

  bottom_bound_y = stoi(input_s);

  return;
}

int checkBounds(int &city_cols, int &city_rows, int &top_bound_x, int &top_bound_y, int &bottom_bound_x, int &bottom_bound_y)
{
  if (top_bound_x > bottom_bound_x)
  {
    top_bound_x = top_bound_x ^= bottom_bound_x;
    bottom_bound_x = bottom_bound_x ^= top_bound_y;
    top_bound_x = top_bound_x ^= bottom_bound_x;
  }
  if (top_bound_y > bottom_bound_y)
  {
    top_bound_y = top_bound_y ^= bottom_bound_y;
    bottom_bound_y = bottom_bound_y ^= top_bound_y;
    top_bound_y = top_bound_y ^= bottom_bound_y;
  }

  //TO-DO (Colton) Write actual fail statements
  if (top_bound_x < 0)
  {
    cout << "Invalid response. Make sure to format the" << endl;
    cout << "coordinates as \"(1,2)(3,4)\": ";
    return 0;
  }
  else if (bottom_bound_x > city_cols)
  {
    cout << "Invalid response. Make sure to format the" << endl;
    cout << "coordinates as \"(1,2)(3,4)\": ";
    return 0;
  }
  else if (top_bound_y < 0)
  {
    cout << "Invalid response. Make sure to format the" << endl;
    cout << "coordinates as \"(1,2)(3,4)\": ";
    return 0;
  }
  else if (bottom_bound_y > city_rows)
  {
    cout << "Invalid response. Make sure to format the" << endl;
    cout << "coordinates as \"(1,2)(3,4)\": ";
    return 0;
  }

  return 1;
}

void printCity(vector<vector<struct Cell>> city)
{
  for (int i = 0; i < city.size(); i++)
  {
    for (int j = 0; j < city[i].size(); j++)
    {
      if (city[i][j].population == 0)
        cout << city[i][j].cell_type << " ";
      else
        cout << city[i][j].population << " ";
    }  
    cout << endl;
  }

  return;
}

void printList(list<struct Cell> list)
{
  for (auto it = begin(list); it != end(list); ++it)
    cout << it->cell_type << ", ";

  cout << endl;
  return;
}

int sumPopulation(vector<vector<struct Cell>> &city, int top_bound_x, int top_bound_y, int bottom_bound_x, int bottom_bound_y, char c)
{
  int total = 0;
  for (int i = top_bound_x; i <= bottom_bound_x; i++)
      for (int j = top_bound_y; j <= bottom_bound_y; j++)
        if (city[i][j].cell_type == c)
          total += city[i][j].population;

  return total;
}

void printPollution(vector<vector<struct Cell>> city)
{
  for (int i = 0; i < city.size(); i++)
  {
    for (int j = 0; j < city[i].size(); j++)
    {
      if (city[i][j].pollution_level == 0)
        cout << "  " << city[i][j].cell_type << "   ";
      else if (city[i][j].cell_type == 'I')
        cout << "  " << city[i][j].pollution_level << "   ";
      else
        cout << " " << city[i][j].cell_type << "(" << city[i][j].pollution_level << ") ";
    }  
    cout << endl;
  }

  return;
};