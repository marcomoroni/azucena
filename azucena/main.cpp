#include <Windows.h>
#include "engine.h"
#include "game.h"
#include "scenes/scene_menu.h"

using namespace std;

MenuScene scene_menu;
OptionsScene scene_options;
GameOverScene scene_game_over;
CenterScene scene_center;
TopScene scene_top;
LeftScene scene_left;
RightScene scene_right;

int main() {

#ifdef NDEBUG
	// Hide console
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_HIDE);
#endif

	Engine::Start(game_width, game_heigth, "Azucena", &scene_menu);
}