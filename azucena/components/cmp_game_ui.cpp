#include "cmp_game_ui.h"
#include "engine.h"
#include "system_renderer.h"
#include "system_resources.h"

using namespace std;
using namespace sf;

GameUIComponent::GameUIComponent(Entity* p, shared_ptr<Entity> player)
	: Component(p), _player(player)
{

	_tex = Resources::load<Texture>("game_ui.png");
	_player_health_sprite_size = 64;

	_player_health_left = Sprite(*_tex);
	_player_health_left.setTextureRect(IntRect(0, 0, _player_health_sprite_size, _player_health_sprite_size));

	int i;
	auto phc = _player->get_components<PlayerHealthComponent>()[0];
	for (i = 0; i < phc->getMaxHealth(); i++)
	{
		Sprite s = Sprite(*_tex);
		_player_health_hearts.push_back(s);
		// Set intrect later in update
	}

	_player_health_right = Sprite(*_tex);
	_player_health_right.setTextureRect(IntRect(_player_health_sprite_size * 3, 0, _player_health_sprite_size, _player_health_sprite_size));
}

void GameUIComponent::update(double dt)
{
	// Move elements so that they looked fixed on the screen.
	// This is not the best way, but we would have to change the
	// system renderer otherwise.

	_parent->setPosition({
		Engine::GetWindow().getView().getCenter().x,
		Engine::GetWindow().getView().getCenter().y});

	_player_health_left.setPosition(
		_parent->getPosition().x - Engine::GetWindow().getSize().x / 2 - 30.0f,
		_parent->getPosition().y - Engine::GetWindow().getSize().y / 2 + 30.0f
	);

	for (int i = 0; i < _player_health_hearts.size(); i++)
	{
		_player_health_hearts[i].setPosition(
			_player_health_left.getPosition().x + (_player_health_sprite_size * (i + 1)),
			_player_health_left.getPosition().y
		);
	}

	
	_player_health_right.setPosition(
		_player_health_hearts[_player_health_hearts.size() - 1].getPosition().x + _player_health_sprite_size,
		_player_health_left.getPosition().y
	);

	// Change heart sprite if hit
	for (int i = 0; i < _player_health_hearts.size(); i++)
	{
		if (i < _player->get_components<PlayerHealthComponent>()[0]->getHealth())
		{
			_player_health_hearts[i].setTextureRect(IntRect(_player_health_sprite_size * 2, 0, _player_health_sprite_size, _player_health_sprite_size));
		}
		else
		{
			_player_health_hearts[i].setTextureRect(IntRect(_player_health_sprite_size, 0, _player_health_sprite_size, _player_health_sprite_size));
		}
	}
}

void GameUIComponent::render()
{
	Renderer::queue(&_player_health_left);
	for (auto &s : _player_health_hearts) Renderer::queue(&s);
	Renderer::queue(&_player_health_right);
}