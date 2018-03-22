#include "cmp_player_physics.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include <SFML/Window/Keyboard.hpp>
#include "../constrols.h"

using namespace std;
using namespace sf;
using namespace Physics;

void PlayerPhysicsComponent::update(double dt) {

	const auto pos = _parent->getPosition();

	auto speed = _groundspeed;

	//Teleport to start if we fall off map.
	if (pos.y > ls::getHeight() * ls::getTileSize()) {
		teleport(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	}

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

	setVelocity(Vector2f(normalize(direction)  * speed));

	PhysicsComponent::update(dt);
}

PlayerPhysicsComponent::PlayerPhysicsComponent(Entity* p,
	const Vector2f& size)
	: PhysicsComponent(p, true, size) {
	_size = sv2_to_bv2(size, true);
	_groundspeed = 160.f;
	_isSprinting = false;
	_sprintSpeed = 1200.f;
	_sprintCooldown = 0.0f;
	_isStillPressingSprintKey = false;
	_body->SetSleepingAllowed(false);
	_body->SetFixedRotation(true);
	//Bullet items have higher-res collision detection
	_body->SetBullet(true);
}
