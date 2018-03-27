#include "cmp_game_ui.h"
#include "engine.h"
#include "system_renderer.h"

using namespace std;
using namespace sf;

RectangleShape r;

GameUIComponent::GameUIComponent(Entity* p)
	: Component(p)
{
	// Draw a red square at top right corner
	// (set origin to correct position)
	r = RectangleShape({ 100.0f, 100.0f });
	r.setFillColor(Color::Red);
	r.setOrigin(100.0f, 0);
}

void GameUIComponent::update(double dt)
{
	// Move elements so that they looked fixed on the screen.
	// This is not the best way, but we would have to change the
	// system renderer otherwise.

	_parent->setPosition({
		Engine::GetWindow().getView().getCenter().x,
		Engine::GetWindow().getView().getCenter().y});

	r.setPosition(
		_parent->getPosition().x + Engine::GetWindow().getSize().x / 2 - 10.0f,
		_parent->getPosition().y - Engine::GetWindow().getSize().y / 2 + 10.0f);
}

void GameUIComponent::render()
{
	Renderer::queue(&r);
}