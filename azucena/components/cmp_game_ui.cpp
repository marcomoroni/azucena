#include "cmp_game_ui.h"
#include "engine.h"
#include "system_renderer.h"

using namespace std;
using namespace sf;

RectangleShape r;

UIComponent::UIComponent(Entity* p)
	: Component(p)
{
	r = RectangleShape({ 100.0f, 100.0f });
	r.setFillColor(Color::Red);
}

void UIComponent::update(double dt)
{
	// Move elements so that they looked fixed on the screen.
	// This is not the best way, but we would have to change the
	// system rendere otherwise.

	r.setPosition(
		Engine::GetWindow().getView().getCenter().x - Engine::GetWindow().getSize().x / 2 + 10.0f,
		Engine::GetWindow().getView().getCenter().y - Engine::GetWindow().getSize().y / 2 + 10.0f);
}

void UIComponent::render()
{
	Renderer::queue(&r);
}