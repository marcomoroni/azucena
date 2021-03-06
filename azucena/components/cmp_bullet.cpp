#include "cmp_bullet.h"
#include "cmp_physics.h"
#include "cmp_sprite.h"
#include "system_physics.h"

#define M_PI 3.14159265358979323846

using namespace std;
using namespace sf;

void BulletComponent::update(double dt)
{
	// Move it
	_parent->get_components<PhysicsComponent>()[0]->setVelocity(_direction * _maxSpeed);

	// Delete if hits something (but not the owner)
	auto touching = _parent->get_components<PhysicsComponent>()[0]->getTouching();
	if (touching.size() > 0)
	{
		for (auto t : touching)
		{
			if (t->GetFixtureA() != _owner->get_components<PhysicsComponent>()[0]->getFixture())
			{
				_parent->setForDelete();
			}
		}
	}

	// Or delete if lifetime is over
	_lifetime -= dt;
	if (_lifetime <= 0.f) {
		_parent->setForDelete();
	}

	if (_owner->is_fordeletion()) _parent->setForDelete();
}

BulletComponent::BulletComponent(Entity* p, Entity* owner, Vector2f direction, float maxSpeed)
	: Component(p), _owner(owner), _direction(direction), _lifetime(5.0f), _maxSpeed(maxSpeed)
{
}
