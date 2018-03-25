#include "cmp_enemy_health.h"

using namespace std;

EnemyHealthComponent::EnemyHealthComponent(Entity* p, int maxHealth)
	: Component(p), _maxHealth(maxHealth), _health(maxHealth)
{
}

void EnemyHealthComponent::update(double dt)
{
}

void EnemyHealthComponent::decreaseHealth(int h)
{
	int newHealth = _health - h;
	if (newHealth >= 0) _health = newHealth;
}

void EnemyHealthComponent::decreaseHealth()
{
	decreaseHealth(1);
}

void EnemyHealthComponent::increaseHealth(int h)
{
	int newHealth = _health + h;
	if (newHealth < _maxHealth) _health = newHealth;
}

void EnemyHealthComponent::increaseHealth()
{
	increaseHealth(1);
}

int EnemyHealthComponent::GetHealth() { return _health; }

int EnemyHealthComponent::GetMaxHealth() { return _maxHealth; }