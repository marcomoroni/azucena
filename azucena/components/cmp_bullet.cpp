#include "cmp_bullet.h"
#include "cmp_physics.h"

using namespace std;
using namespace sf;

void BulletComponent::update(double dt)
{
	// Use teleport because it sould alway go in a straight line
	_parent->get_components<PhysicsComponent>()[0]->teleport(_parent->getPosition() + (normalize(_direction) * _maxSpeed * (float)dt));

	// Delete if hits something
	if (_parent->get_components<PhysicsComponent>()[0]->getTouching().size() > 0)
	{
		_parent->setForDelete();
	}

	// Or delete if lifetime is over
  _lifetime -= dt;
  if (_lifetime <= 0.f) {
    _parent->setForDelete();
  }
}

BulletComponent::BulletComponent(Entity* p, Vector2f direction)
    : Component(p), _direction(direction), _lifetime(3.0f), _maxSpeed(600.0f) {}
