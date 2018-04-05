#include "cmp_game_ui.h"
#include "engine.h"
#include "system_renderer.h"
#include "system_resources.h"
#include "../prefabs.h"
#include "../constrols.h"

using namespace std;
using namespace sf;

GameUIComponent::GameUIComponent(Entity* p, shared_ptr<Entity> player)
	: Component(p), _player(player), _margin(32.0f)
{

	_tex = Resources::get<Texture>("tex.png");
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

  _exitMessage = create_exit_ui_message();
  _exitMessageTimer = 0.0f;
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
    _parent->getPosition().x - Engine::GetWindow().getSize().x / 2 + _margin,
    _parent->getPosition().y - Engine::GetWindow().getSize().y / 2 + _margin };

  Vector2f top_right_corner = {
    _parent->getPosition().x + Engine::GetWindow().getSize().x / 2 - _margin,
    _parent->getPosition().y - Engine::GetWindow().getSize().y / 2 + _margin };

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

  // Exit message
  if (Keyboard::isKeyPressed(Controls::GetKeyboardKey("Return to menu"))) showExitMessage();
  if (_exitMessageTimer >= 0.0f)
  {
    // Show message
    _exitMessage->setPosition(top_right_corner);
    _exitMessageTimer -= dt;
  }
  else
  {
    // hide message
    _exitMessage->setPosition(Vector2f{ _parent->getPosition().x + Engine::GetWindow().getSize().x, _parent->getPosition().y + Engine::GetWindow().getSize().y });
  }
}

void GameUIComponent::render()
{
	for (auto &s : _player_health_hearts) Renderer::queue(&s);
}

void GameUIComponent::showExitMessage()
{
  _exitMessageTimer = 3.0f;
}