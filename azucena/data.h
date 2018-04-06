#pragma once
#include <string>

class Data
{
public:
  static void load();
  static void save();
  static void reset();
  static std::string save_file_path;

  static bool main_collectible_1;
  static bool main_collectible_2;
  static bool main_collectible_3;
  static bool door_top_opened;
  static bool door_right_opened;
  static bool door_left_opened;
};