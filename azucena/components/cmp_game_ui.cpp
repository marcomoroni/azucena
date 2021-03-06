#include "cmp_game_ui.h"
#include "engine.h"
#include "system_renderer.h"
#include "system_resources.h"
#include "../prefabs.h"
#include "../controls.h"
#include "cmp_text.h"

using namespace std;
using namespace sf;

GameUIComponent::GameUIComponent(Entity* p, shared_ptr<Entity> player)
	: Component(p), _player(player), _margin(32.0f)
{

	_tex = Resources::get<Texture>("tex.png");
	_player_health_sprite_size = 32;
	_player_potion_sprite_size = 32;

	// Note: creating the sptites for the hearts here means that if the player max
	// health changes the ui will not be updated (unless we change scene)
	{
		int i;
		auto phc = _player->get_components<PlayerHealthComponent>()[0];
		for (i = 0; i < phc->getMaxHealth(); i++)
		{
			Sprite s = Sprite(*_tex);
			_player_health_hearts.push_back(s);
			// Set intrect later in update
		}
	}
	{
		int i;
		auto phc = _player->get_components<PlayerHealthComponent>()[0];
		for (i = 0; i < phc->getMaxPotions(); i++)
		{
			Sprite s = Sprite(*_tex);
			_player_potions.push_back(s);
			// Set intrect later in update
		}
	}

	{
		// Exit message
		_exitMessage = Engine::GetActiveScene()->makeEntity();
		_exitMessage->addTag("exit string");
		auto t = _exitMessage->addComponent<TextComponent>("Hold [Esc] to exit.");
		//t->getText()->setCharacterSize(40);
		// Origin is on the top right corner
		t->getText()->setOrigin(t->getText()->getLocalBounds().width, 14.0f);
		t->getText()->setColor(Color(255, 218, 194));
		_exitMessageTimer = 0.0f;
	}

	{
		// Bottom message
		_bottomMessage = Engine::GetActiveScene()->makeEntity();
		_bottomMessage->addTag("bottom string");
		auto t = _bottomMessage->addComponent<TextComponent>("");
		//t->getText()->setCharacterSize(40);
		t->getText()->setColor(Color(255, 218, 194));
		_bottomMessageTimer = 0.0f;
	}
}

void GameUIComponent::update(double dt)
{
	// Move elements so that they looked fixed on the screen.
	// This is not the best way, but we would have to change the
	// system renderer otherwise.

	_parent->setPosition({
		Engine::GetWindow().getView().getCenter().x,
		Engine::GetWindow().getView().getCenter().y });

	Vector2f top_left_corner = {
	  _parent->getPosition().x - Engine::GetWindow().getSize().x / 2 + _margin,
	  _parent->getPosition().y - Engine::GetWindow().getSize().y / 2 + _margin };

	Vector2f top_right_corner = {
	  _parent->getPosition().x + Engine::GetWindow().getSize().x / 2 - _margin,
	  _parent->getPosition().y - Engine::GetWindow().getSize().y / 2 + _margin };

	Vector2f bottom_center_corner = {
		_parent->getPosition().x,
		_parent->getPosition().y + Engine::GetWindow().getSize().y / 2 - 128.0f };

	// Hearts position
	for (int i = 0; i < _player_health_hearts.size(); i++)
	{
		_player_health_hearts[i].setPosition(
			top_left_corner.x + (_player_health_sprite_size * i),
			top_left_corner.y
		);
	}

	// Potions position
	for (int i = 0; i < _player_potions.size(); i++)
	{
		_player_potions[i].setPosition(
			top_left_corner.x + (_player_health_sprite_size * i),
			top_left_corner.y + _player_health_sprite_size
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

	// Change potions sprite when get/use them
	// (not very efficient)
	for (int i = 0; i < _player_potions.size(); i++)
	{
		if (i < _player->get_components<PlayerHealthComponent>()[0]->getPotions())
		{
			_player_potions[i].setTextureRect(IntRect(_player_health_sprite_size * 6, _player_health_sprite_size * 2, _player_health_sprite_size, _player_health_sprite_size));
		}
		else
		{
			_player_potions[i].setTextureRect(IntRect(_player_health_sprite_size * 5, _player_health_sprite_size * 2, _player_health_sprite_size, _player_health_sprite_size));
		}
	}

	// Exit message
	if (Keyboard::isKeyPressed(Controls::GetKeyboardKey("Return to menu")) || Joystick::isButtonPressed(0, 7)) showExitMessage();
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

	// Bottom message
	if (_bottomMessageTimer >= 0.0f)
	{
		// Show message
		_bottomMessage->setPosition(bottom_center_corner);
		_bottomMessageTimer -= dt;
	}
	else
	{
		// hide message
		_bottomMessage->get_components<TextComponent>()[0]->getText()->setString("");
	}
}

void GameUIComponent::render()
{
	for (auto &s : _player_health_hearts) Renderer::queue(&s);
	for (auto &s : _player_potions) Renderer::queue(&s);
}

void GameUIComponent::showExitMessage()
{
	_exitMessageTimer = 3.0f;
}

void GameUIComponent::showBottomMessage(int i)
{
	// Change messages if using controller
	if (Joystick::isConnected(0))
	{
		switch (i)
		{
		case 0: i = 6; break;
		case 1: i = 7; break;
		case 2: i = 8; break;
		default: break;
		}
	}

	_bottomMessageTimer = 8.0f;
	auto t = _bottomMessage->get_components<TextComponent>()[0];
	t->getText()->setString(_bottomMessages[i]);
	t->getText()->setOrigin(t->getText()->getLocalBounds().width / 2, t->getText()->getLocalBounds().height / 2 + 14.0f);
}