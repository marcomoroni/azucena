#include "cmp_hurt.h"
#include "system_physics.h"
#include "engine.h"
#include "cmp_physics.h"
#include "cmp_player_health.h"
#include "cmp_enemy_health.h"

using namespace std;
using namespace sf;

HurtComponent::HurtComponent(Entity* p, string tagToHurt)
	: Component(p), _tagToHurt(tagToHurt), _active(false)
{

}

void HurtComponent::update(double dt)
{
	_isHurting = false;

	if (_active)
	{
		auto cs = _parent->get_components<PhysicsComponent>()[0]->getTouching();
		for (auto c : cs)
		{
			auto entsToHurt = Engine::GetActiveScene()->ents.find(_tagToHurt);
			for (auto entityToHurt : entsToHurt)
			{
				if (c->GetFixtureA() == entityToHurt->get_components<PhysicsComponent>()[0]->getFixture() ||
					c->GetFixtureB() == entityToHurt->get_components<PhysicsComponent>()[0]->getFixture())
				{
					if (_tagToHurt == "player") entityToHurt->get_components<PlayerHealthComponent>()[0]->decreaseHealth(_damage);
					else if (_tagToHurt == "enemy") entityToHurt->get_components<EnemyHealthComponent>()[0]->decreaseHealth(_damage);
					_isHurting = true;
				}
			}
		}
	}
}

void HurtComponent::setDamage(int d) { _damage = d; }

void HurtComponent::setActive(bool a) { _active = a; }

bool HurtComponent::isHurting() { return _isHurting; }