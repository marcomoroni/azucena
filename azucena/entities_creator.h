#pragma once

#include "ecm.h"

std::shared_ptr<Entity> create_player(Scene* scene);
std::vector<std::shared_ptr<Entity>> create_enemies(Scene* scene);