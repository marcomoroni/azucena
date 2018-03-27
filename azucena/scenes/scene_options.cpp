#include "scene_options.h"
#include "../game.h"
#include "../prefabs.h"
#include "../components/cmp_text.h"
#include "../components/cmp_button.h"

using namespace std;
using namespace sf;

shared_ptr<Entity> btn_Back;

void OptionsScene::Load()
{
	{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>("Options");
		txt->setPosition({ (float)Engine::GetWindow().getSize().x / 2, 100.0f });
	}

	btn_Back = create_button("Back");
	btn_Back->setPosition({ (float)Engine::GetWindow().getSize().x / 2, 600.0f });

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