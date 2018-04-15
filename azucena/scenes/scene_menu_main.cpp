#include "scene_menu_main.h"
#include "../prefabs.h"

using namespace std;
using namespace sf;

void MenuMainScene::Load()
{
	// Game title

	// Buttons
	auto b = create_ui_button("Continue");
	b->setPosition(Vector2f(200.0f, 100.0f));

	setLoaded(true);
}

void MenuMainScene::UnLoad()
{
	Scene::UnLoad();
}

void MenuMainScene::Update(const double& dt)
{
	Scene::Update(dt);
}

void MenuMainScene::Render()
{
	Scene::Render();
}