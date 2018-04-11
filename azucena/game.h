#pragma once

#include "data.h"
#include "scenes/scene_center.h"
#include "scenes/scene_top.h"
#include "scenes/scene_left.h"
#include "scenes/scene_right.h"
#include "scenes/scene_game_over.h"
#include "scenes/scene_menu.h"
#include "scenes/scene_options.h"

static unsigned int game_width = 1600;
static unsigned int game_heigth = 1200;

extern MenuScene scene_menu;
extern OptionsScene scene_options;
extern GameOverScene scene_game_over;
extern CenterScene scene_center;
extern TopScene scene_top;
extern LeftScene scene_left;
extern RightScene scene_right;