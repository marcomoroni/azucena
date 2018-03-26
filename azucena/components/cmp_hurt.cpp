#include "cmp_hurt.h"
#include "system_physics.h"
#include "engine.h"
#include "cmp_player_physics.h"
#include "cmp_player_health.h"
#include "cmp_enemy_health.h"

using namespace std;
using namespace sf;
using namespace Physics;

HurtComponent::HurtComponent(Entity* p, const Vector2f& size)
	: PhysicsComponent(p, true, size)
{
	_size = sv2_to_bv2(size, true);
}

void HurtComponent::update(double dt)
{
	setVelocity({ 0, 0 });

	// Assuming this component is just for enemies:
	// - movement is made in state machine
	// - checks enemy if hits player
	// - check isplayer's sword hits enemy

	// TEST, just rotate player
	
	
	////////////// SUPER SLOW ////////////////////

	/*vector<shared_ptr<Entity>> entsToHurt;
	for (auto t : _tagsToHurt)
	{
		auto ents = Engine::GetActiveScene()->ents.find(t);
		for (auto e : ents)
		{
			entsToHurt.push_back(e);
		}
	}

	auto cs = getTouching();
	for (auto c : cs)
	{
		for (auto e : entsToHurt)
		{
			// If it's player
			if (c->GetFixtureA() == e->get_components<PlayerPhysicsComponent>()[0]->getFixture())
			{
				e->setRotation(90.0f);
			}
		}
	}*/

	PhysicsComponent::update(dt);

	auto p = Engine::GetActiveScene()->ents.find("player")[0];
	auto cs = getTouching();
	for (auto c : cs)
	{
		// If it's player, decrease player's health
		if (c->GetFixtureA() == p->get_components<PlayerPhysicsComponent>()[0]->getFixture())
		{
			p->setRotation(180.0f);
			p->get_components<PlayerHealthComponent>()[0]->decreaseHealth();
		}
		// If it's player's sword, decrease enemy's health // TODO
		if (c->GetFixtureA() == p->get_components<PlayerPhysicsComponent>()[0]->getFixture()) // TEST
		{
			_parent->get_components<EnemyHealthComponent>()[0]->decreaseHealth();
			_parent->setRotation(90.0f);
		}
	}
}

void HurtComponent::addTagToHurt(string t)
{
	_tagsToHurt.push_back(t);
}