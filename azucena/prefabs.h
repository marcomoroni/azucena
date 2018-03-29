#pragma once

#include "ecm.h"
#include <string>

std::shared_ptr<Entity> create_player();
std::vector<std::shared_ptr<Entity>> create_enemies();
void add_physics_colliders_to_tiles();
std::shared_ptr<Entity> create_button(std::string);
std::shared_ptr<Entity> create_game_ui();
std::shared_ptr<Entity> create_player_bullet(sf::Vector2f direction);