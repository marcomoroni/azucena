#include "scene_options.h"
#include "../game.h"
#include "../prefabs.h"
#include "../components/cmp_text.h"
#include "../components/cmp_button.h"

using namespace std;
using namespace sf;

shared_ptr<Entity> btn_Back;
vector<shared_ptr<Entity>> btns;

void OptionsScene::Load()
{
	{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>("Options");
		txt->setPosition({ (float)Engine::GetWindow().getSize().x / 2, 100.0f });
	}

	auto btn = create_button("Move up: ...");
	btns.push_back(btn);

	btn = create_button("Down down: ...");
	btns.push_back(btn);

	btn = create_button("Down left: ...");
	btns.push_back(btn);

	btn = create_button("Down right: ...");
	btns.push_back(btn);

	btn_Back = create_button("Back");
	btns.push_back(btn_Back);

	// Set buttons position
	for (int i = 0; i < btns.size(); i++)
	{
		btns[i]->setPosition({ (float)Engine::GetWindow().getSize().x / 2, (40.0f * i) + 200.0f });
	}

	// Set view
	Engine::GetWindow().setView(Engine::GetWindow().getDefaultView());

	setLoaded(true);
}

void OptionsScene::Update(const double& dt)
{
	if (btn_Back->get_components<ButtonComponent>()[0]->isSelected())
	{
		Engine::ChangeScene(&menu);
	}

	Scene::Update(dt);
}