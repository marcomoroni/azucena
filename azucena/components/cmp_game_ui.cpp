#include "cmp_game_ui.h"
#include "engine.h"
#include "system_renderer.h"
#include "system_resources.h"

using namespace std;
using namespace sf;

GameUIComponent::GameUIComponent(Entity* p, shared_ptr<Entity> player)
	: Component(p), _player(player)
{

	_tex = Resources::load<Texture>("tex.png");
	_player_health_sprite_size = 32;

	// Note: creating the sptites for the hearts here means that if the player max
	// health changes the ui will not be updated (unless we change scene)
	int i;
	auto phc = _player->get_components<PlayerHealthComponent>()[0];
	for (i = 0; i < phc->getMaxHealth(); i++)
	{
		Sprite s = Sprite(*_tex);
		_player_health_hearts.push_back(s);
		// Set intrect later in update
	}
}

void GameUIComponent::update(double dt)
{
	// Move elements so that they looked fixed on the screen.
	// This is not the best way, but we would have to change the
	// system renderer otherwise.

	_parent->setPosition({
		Engine::GetWindow().getView().getCenter().x,
		Engine::GetWindow().getView().getCenter().y});

  Vector2f top_left_corner = {
    _parent->getPosition().x - Engine::GetWindow().getSize().x / 2 + 32,
    _parent->getPosition().y - Engine::GetWindow().getSize().y / 2 + 32 };

	for (int i = 0; i < _player_health_hearts.size(); i++)
	{
		_player_health_hearts[i].setPosition(
      top_left_corner.x + (_player_health_sprite_size * i),
      top_left_corner.y
		);
	}

	// Change heart sprite if hit
	// (not very efficient)
	for (int i = 0; i < _player_health_hearts.size(); i++)
	{
		if (i < _player->get_components<PlayerHealthComponent>()[0]->getHealth())
		{
			_player_health_hearts[i].setTextureRect(IntRect(_player_health_sprite_size * 6, 0, _player_health_sprite_size, _player_health_sprite_size));
		}
		else
		{
			_player_health_hearts[i].setTextureRect(IntRect(_player_health_sprite_size * 6, _player_health_sprite_size, _player_health_sprite_size, _player_health_sprite_size));
		}
	}
}

void GameUIComponent::render()
{
	for (auto &s : _player_health_hearts) Renderer::queue(&s);
}