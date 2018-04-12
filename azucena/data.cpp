#include "data.h"
#include <fstream>

using namespace std;

bool Data::main_collectible_right;
bool Data::main_collectible_top;
bool Data::main_collectible_left;
bool Data::door_top_opened;
bool Data::door_right_opened;
bool Data::door_left_opened;
int Data::max_health;
int Data::health;
int Data::max_potions;
int Data::potions;
float Data::shootCooldownTime;

string Data::save_file_path = "azucena_save.txt";

void Data::load()
{
	ifstream file(save_file_path);
	if (file.good())
	{
		file >> main_collectible_right;
		file >> main_collectible_top;
		file >> main_collectible_left;
		file >> door_top_opened;
		file >> door_right_opened;
		file >> door_left_opened;
		file >> max_health;
		file >> health;
		file >> max_potions;
		file >> potions;
		file >> (float)shootCooldownTime;
	}
}

void Data::save()
{
	printf("Opening save file...\n");
	ofstream file;
	file.open(save_file_path, ofstream::trunc);

	printf("Saving...\n");
	file <<
		(int)main_collectible_right << " " <<
		(int)main_collectible_top << " " <<
		(int)main_collectible_left << " " <<
		(int)door_top_opened << " " <<
		(int)door_right_opened << " " <<
		(int)door_left_opened << " " <<
		max_health << " " <<
		health << " " <<
		max_potions << " " <<
		potions << " " <<
		(int)shootCooldownTime;

	printf("Closing save file...\n");
	file.close();
}

void Data::reset()
{
	main_collectible_right = false;
	main_collectible_top = false;
	main_collectible_left = false;
	door_top_opened = false;
	door_right_opened = false;
	door_left_opened = false;
	max_health = 4;
	health = 4;
	max_potions = 2;
	potions = 0;
	shootCooldownTime = 1.2f;
}