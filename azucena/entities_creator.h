#pragma once

#include "ecm.h"

std::shared_ptr<Entity> create_player();
std::vector<std::shared_ptr<Entity>> create_enemies();
void add_physics_colliders_to_tiles();