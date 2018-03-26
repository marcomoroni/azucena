#pragma once

#include "cmp_physics.h"
#include <string>

class HurtComponent : public PhysicsComponent
{
private:
	int _attackValue;
	b2Vec2 _size;
	std::vector<std::string> _tagsToHurt = {};

public:
	void update(double dt) override;
	explicit HurtComponent(Entity* p, const sf::Vector2f& size);
	HurtComponent() = delete;
	void addTagToHurt(std::string);
};