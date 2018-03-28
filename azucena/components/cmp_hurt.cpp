#include "cmp_hurt.h"

HurtComponent::HurtComponent(Entity* p)
	: Component(p)
{

}

void HurtComponent::update(double dt)
{

}

void HurtComponent::setDamage(int d) { _damage = d; }