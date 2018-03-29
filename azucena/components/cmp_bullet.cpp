#include "cmp_bullet.h"
#include "cmp_physics.h"
#include "cmp_sprite.h"
#include "system_physics.h"

#define M_PI 3.14159265358979323846

using namespace std;
using namespace sf;

void BulletComponent::update(double dt)
{
	// Use teleport because it sould alway go in a straight line
	_parent->get_components<PhysicsComponent>()[0]->teleport(_parent->getPosition() + (normalize(_direction) * _maxSpeed * (float)dt));

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
}

BulletComponent::BulletComponent(Entity* p, shared_ptr<Entity> owner, Vector2f direction)
    : Component(p), _owner(owner), _direction(direction), _lifetime(5.0f), _maxSpeed(600.0f)
{
}
