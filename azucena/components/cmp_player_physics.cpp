#include "cmp_player_physics.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include <SFML/Window/Keyboard.hpp>

using namespace std;
using namespace sf;
using namespace Physics;

void PlayerPhysicsComponent::update(double dt) {

	const auto pos = _parent->getPosition();

	//Teleport to start if we fall off map.
	if (pos.y > ls::getHeight() * ls::getTileSize()) {
		teleport(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	}

	Vector2f direction = { 0, 0 };

	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		direction.x += 1.0f;
	}
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		direction.x -= 1.0f;
	}
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		direction.y += 1.0f;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		direction.y -= 1.0f;
	}

	setVelocity(Vector2f(normalize(direction)  * _groundspeed));

	PhysicsComponent::update(dt);
}

PlayerPhysicsComponent::PlayerPhysicsComponent(Entity* p,
	const Vector2f& size)
	: PhysicsComponent(p, true, size) {
	_size = sv2_to_bv2(size, true);
	_groundspeed = 300.f;
	_body->SetSleepingAllowed(false);
	_body->SetFixedRotation(true);
	//Bullet items have higher-res collision detection
	_body->SetBullet(true);
}
