#pragma once

#include "cmp_physics.h"

class PlayerPhysicsComponent : public PhysicsComponent {
protected:
  b2Vec2 _size;
  float _groundspeed;
	bool _isSprinting;
	// Timer until player can sprint again
	double _sprintCooldown;
	float _sprintSpeed;
	// Player cannot change direction when sprinting
	sf::Vector2f _sprintDirection;

public:
  void update(double dt) override;

  explicit PlayerPhysicsComponent(Entity* p, const sf::Vector2f& size);

  PlayerPhysicsComponent() = delete;
};
