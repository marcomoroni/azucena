#pragma once
#include "cmp_physics.h"
#include <ecm.h>

class BulletComponent : public Component {
protected:
	float _lifetime;
	sf::Vector2f _direction;
	float _maxSpeed;
	Entity* _owner;

public:
	void update(double dt) override;
	void render() override {}
	explicit BulletComponent(Entity* p, Entity* owner, sf::Vector2f direction, float maxSpeed);
	BulletComponent() = delete;
};
