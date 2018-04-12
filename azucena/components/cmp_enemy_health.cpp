#include "cmp_enemy_health.h"
#include "system_resources.h"
#include "system_renderer.h"

using namespace std;
using namespace sf;

//RenderTexture backTex;
bool _flagHeathChanged = false;

EnemyHealthComponent::EnemyHealthComponent(Entity* p, int maxHealth)
	: Component(p), _maxHealth(maxHealth), _health(maxHealth)
{

}

void EnemyHealthComponent::update(double dt)
{
	if (_immunity >= 0.0f) _immunity -= dt;

	// Delete if health == 0
	if (_health <= 0)
	{
		_parent->setForDelete();
	}
}

void EnemyHealthComponent::render()
{

}

void EnemyHealthComponent::decreaseHealth(int h)
{
	if (_immunity < 0.0f)
	{
		int newHealth = _health - h;
		if (newHealth >= 0) _health = newHealth;
		_immunity = 0.2f;
		_flagHeathChanged = true;
	}

}

void EnemyHealthComponent::decreaseHealth()
{
	decreaseHealth(1);
}

void EnemyHealthComponent::increaseHealth(int h)
{
	int newHealth = _health + h;
	if (newHealth < _maxHealth) _health = newHealth;
	_flagHeathChanged = true;
}

void EnemyHealthComponent::increaseHealth()
{
	increaseHealth(1);
}

int EnemyHealthComponent::getHealth() { return _health; }

int EnemyHealthComponent::getMaxHealth() { return _maxHealth; }