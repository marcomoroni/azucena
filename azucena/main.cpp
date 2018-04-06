#include <Windows.h>
#include "engine.h"
#include "game.h"
#include "scenes/scene_menu.h"

using namespace std;

MenuScene menu;
OptionsScene options;
GameOverScene game_over;
CenterScene center;

int main() {

#ifdef NDEBUG
	// Hide console
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_HIDE);
#endif

  Engine::Start(1000, 600, "Azucena", &menu);
}