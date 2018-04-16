#pragma once
#include <string>

class Data
{
public:
	static void load();
	static void save();
	static void reset();
	static std::string save_file_path;

	static bool main_collectible_right;
	static bool main_collectible_top;
	static bool main_collectible_left;
	static bool door_top_opened;
	static bool door_right_opened;
	static bool door_left_opened;
	static int max_health;
	static int health;
	static int max_potions;
	static int potions;
	static float shootCooldownTime;
	static bool introPlayed;
};