#pragma once

#include "ecm.h"
#include <string>

std::shared_ptr<Entity> create_player();
std::vector<std::shared_ptr<Entity>> create_enemies();
void create_walls();
std::shared_ptr<Entity> create_button(std::string);
std::shared_ptr<Entity> create_game_ui();
std::shared_ptr<Entity> create_player_bullet(sf::Vector2f direction);
std::shared_ptr<Entity> create_enemy_B_bullet(Entity* owner, sf::Vector2f direction);
std::shared_ptr<Entity> create_enemy_C_bullet(Entity* owner, sf::Vector2f direction);
std::shared_ptr<Entity> create_key();
std::shared_ptr<Entity> create_door();
// Main collectible (must have an index)
std::shared_ptr<Entity> create_baby_llama(int index);
std::vector<std::shared_ptr<Entity>> create_potions();