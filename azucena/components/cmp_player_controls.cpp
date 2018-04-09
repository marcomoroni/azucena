#include "cmp_player_controls.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include <SFML/Window/Keyboard.hpp>
#include "../constrols.h"
#include "cmp_physics.h"
#include "engine.h"
#include "../prefabs.h"
#include "system_resources.h"

using namespace std;
using namespace sf;
using namespace Physics;

void PlayerControlsComponent::update(double dt) {

	const auto pos = _parent->getPosition();

	auto speed = _groundspeed;

	Vector2f direction = { 0, 0 };

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
			_parent->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().setColor(Color(255, 255, 255));
		}
	}

	// Check if player is still pressing Sprint key
	if (!Keyboard::isKeyPressed(Keyboard::Space))
	{
		_isStillPressingSprintKey = false;
	}

	// Check if player starts sprinting
	if (Keyboard::isKeyPressed(Controls::GetKeyboardKey("Sprint")) && !_isSprinting && direction != Vector2f(0, 0) && !_isStillPressingSprintKey)
	{
#if DEBUG
		cout << "Sprinting" << endl;
#endif
		_isSprinting = true;
		_sprintCooldown = 0.4f;
		_sprintDirection = direction;
		_isStillPressingSprintKey = true;
		_parent->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().setColor(Color(180, 255, 255));
	}

	// Check if player shoots
	if (Keyboard::isKeyPressed(Controls::GetKeyboardKey("Shoot")) && _shootCooldown <= 0.0f)
	{
		create_player_bullet(normalize(_shootDirection));
		_sound_shoot.play();
		_shootCooldown = 0.3f;
	}
	if (_shootCooldown > 0.0f) _shootCooldown -= dt;

	_parent->get_components<PhysicsComponent>()[0]->setVelocity(Vector2f(normalize(direction) * speed));
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

	_buffer_shoot = *(Resources::get<SoundBuffer>("shoot.wav"));
	_sound_shoot.setBuffer(_buffer_shoot);
}
