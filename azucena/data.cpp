#include "data.h"
#include <fstream>

using namespace std;

bool Data::main_collectible_1;
bool Data::main_collectible_2;
bool Data::main_collectible_3;
bool Data::door_top_opened;
bool Data::door_right_opened;
bool Data::door_left_opened;

string Data::save_file_path = "azucena_save.txt";

void Data::load()
{
  ifstream file(save_file_path);
  if (file.good())
  {
    file >> main_collectible_1;
    file >> main_collectible_2;
    file >> main_collectible_3;
    file >> door_top_opened;
    file >> door_right_opened;
    file >> door_left_opened;
  }
}

void Data::save()
{
  printf("Opening save file...\n");
  ofstream file;
  file.open(save_file_path, ofstream::trunc);

  printf("Saving...\n");
  file <<
    (int)main_collectible_1 << " " <<
    (int)main_collectible_2 << " " <<
    (int)main_collectible_3 << " " <<
    (int)door_top_opened << " " <<
    (int)door_right_opened << " " <<
    (int)door_left_opened;

  printf("Closing save file...\n");
  file.close();
}

void Data::reset()
{
  main_collectible_1 = false;
  main_collectible_2 = false;
  main_collectible_3 = false;
  door_top_opened = false;
  door_right_opened = false;
  door_left_opened = false;
}