#include "cmp_player_controls.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include <SFML/Window/Keyboard.hpp>
#include "../controls.h"
#include "cmp_physics.h"
#include "engine.h"
#include "../prefabs.h"
#include "system_resources.h"
#include "../data.h"

using namespace std;
using namespace sf;
using namespace Physics;

void PlayerControlsComponent::update(double dt) {

	const auto pos = _parent->getPosition();

	auto speed = _groundspeed;

	Vector2f direction = { 0, 0 };

	if (Joystick::isConnected(0))
	{
		float x = Joystick::getAxisPosition(0, Joystick::X);
		float y = Joystick::getAxisPosition(0, Joystick::Y);
		direction = normalize(Vector2f(abs(x) > 10.0f ? x : 0, abs(y) > 10.0f ? -y : 0));
	}
	else
	{
		if (Keyboard::isKeyPressed(Controls::GetKeyboardKey("Right")))
		{
			direction.x += 1.0f;
		}
		if (Keyboard::isKeyPressed(Controls::GetKeyboardKey("Left")))
		{
			direction.x -= 1.0f;
		}
		if (Keyboard::isKeyPressed(Controls::GetKeyboardKey("Up")))
		{
			direction.y += 1.0f;
		}
		if (Keyboard::isKeyPressed(Controls::GetKeyboardKey("Down")))
		{
			direction.y -= 1.0f;
		}
	}

	if (direction != Vector2f(0.0, 0.0f))
	{
		_shootDirection = direction;
		_shootDirection.y *= -1;
	}

	// Sprint
	if (_isSprinting)
	{
		// Apply sprint velocity for a fraction of the cooldown timer
		if (_sprintCooldown > 0.32f)
		{
			speed = _sprintSpeed;
			// If sprinting, direction is fixed
			direction = _sprintDirection;
		}
		// Decrease cooldown timer
		_sprintCooldown -= dt;
		// If timer reaches 0, player is not sprinting anymore
		if (_sprintCooldown < 0)
		{
			_isSprinting = false;
			_parent->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().setTextureRect(_originalPlayerIntRect);
		}
	}

	// Check if player is still pressing Sprint key
	if (Joystick::isConnected(0))
	{
		if (!Joystick::isButtonPressed(0, 5))
		{
			_isStillPressingSprintKey = false;
		}
	}
	else if (!Keyboard::isKeyPressed(Keyboard::Space))
	{
		_isStillPressingSprintKey = false;
	}

	// Check if player starts sprinting
	if ((Keyboard::isKeyPressed(Controls::GetKeyboardKey("Sprint")) || Joystick::isButtonPressed(0, 5)) && !_isSprinting && direction != Vector2f(0, 0) && !_isStillPressingSprintKey && _canMove)
	{
		_sound_dash.play();
		_isSprinting = true;
		_sprintCooldown = 0.4f;
		_sprintDirection = direction;
		_isStillPressingSprintKey = true;
		_parent->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().setTextureRect(IntRect(32 * 5, 32 * 3, 32, 32));
	}

	// Shoot cooldown timer position
	_playerShootCooldownTimerUI->setPosition(Vector2f(_parent->getPosition().x, _parent->getPosition().y + 32.0f));

	// Check if player shoots
	if ((Keyboard::isKeyPressed(Controls::GetKeyboardKey("Shoot")) || Joystick::isButtonPressed(0, 0)) && _shootCooldown <= 0.0f && _canMove)
	{
		create_player_bullet(normalize(_shootDirection));
		_sound_shoot.play();
		_shootCooldown = Data::shootCooldownTime;
		_playerShootCooldownTimerUI->setVisible(true);
	}
	if (_shootCooldown > 0.0f) _shootCooldown -= dt;

	// Shoot cooldown timer sprite
	if (_shootCooldown >= Data::shootCooldownTime / 5 * 4)
		_playerShootCooldownTimerUI->get_components<SpriteComponent>()[0]->getSprite().setTextureRect(IntRect(32 * 6, 32 * 4 + 8 * 4, 32, 8));
	else if (_shootCooldown >= Data::shootCooldownTime / 5 * 3)
		_playerShootCooldownTimerUI->get_components<SpriteComponent>()[0]->getSprite().setTextureRect(IntRect(32 * 6, 32 * 4 + 8 * 3, 32, 8));
	else if (_shootCooldown >= Data::shootCooldownTime / 5 * 2)
		_playerShootCooldownTimerUI->get_components<SpriteComponent>()[0]->getSprite().setTextureRect(IntRect(32 * 6, 32 * 4 + 8 * 2, 32, 8));
	else if (_shootCooldown >= Data::shootCooldownTime / 5 * 1)
		_playerShootCooldownTimerUI->get_components<SpriteComponent>()[0]->getSprite().setTextureRect(IntRect(32 * 6, 32 * 4 + 8 * 1, 32, 8));
	else if (_shootCooldown >= Data::shootCooldownTime / 5 * 0)
		_playerShootCooldownTimerUI->get_components<SpriteComponent>()[0]->getSprite().setTextureRect(IntRect(32 * 6, 32 * 4 + 8 * 0, 32, 8));
	else
		_playerShootCooldownTimerUI->setVisible(false);

	if (_canMove)
		_parent->get_components<PhysicsComponent>()[0]->setVelocity(Vector2f(normalize(direction) * speed));
	else
		_parent->get_components<PhysicsComponent>()[0]->setVelocity(Vector2f(0.0f, 0.0f));
}

PlayerControlsComponent::PlayerControlsComponent(Entity* p)
	: Component(p)
{
	_groundspeed = 160.f;
	_isSprinting = false;
	_sprintSpeed = 1600.f;
	_sprintCooldown = 0.0f;
	_isStillPressingSprintKey = false;
	_shootCooldown = 0.0f;
	_shootDirection = { 1.0f, 0.0f };

	_originalPlayerIntRect = _parent->get_components<SpriteComponent>()[0]->getSprite().getTextureRect();

	// Player shoot cooldown timer
	_playerShootCooldownTimerUI = &(*(Engine::GetActiveScene()->makeEntity()));
	auto s = _playerShootCooldownTimerUI->addComponent<SpriteComponent>();
	auto tex = Resources::get<Texture>("tex.png");
	s->setTexture(tex);
	s->getSprite().setTextureRect(sf::IntRect(32 * 6, 32 * 4, 32, 8));
	s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);
	_playerShootCooldownTimerUI->setVisible(false);

	_canMove = true;

	// Sounds
	_buffer_shoot = *(Resources::get<SoundBuffer>("shoot.wav"));
	_sound_shoot.setBuffer(_buffer_shoot);
	_buffer_dash = *(Resources::get<SoundBuffer>("dash.wav"));
	_sound_dash.setBuffer(_buffer_dash);
}

void PlayerControlsComponent::setCanMove(bool m)
{
	_canMove = m;
}