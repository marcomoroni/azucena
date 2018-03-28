#include "cmp_player_health.h"
#include "system_resources.h"
#include "system_renderer.h"

using namespace std;
using namespace sf;

PlayerHealthComponent::PlayerHealthComponent(Entity* p, int maxHealth)
	: Component(p), _maxHealth(maxHealth), _health(maxHealth)
{
}

void PlayerHealthComponent::update(double dt)
{
	if (_immunity >= 0.0f) _immunity -= dt;
}

void PlayerHealthComponent::render()
{
}

void PlayerHealthComponent::decreaseHealth(int h)
{
	if (_immunity < 0.0f)
	{
		int newHealth = _health - h;
		if (newHealth >= 0) _health = newHealth;
		_immunity = 0.5f;
	}

}

void PlayerHealthComponent::decreaseHealth()
{
	decreaseHealth(1);
}

void PlayerHealthComponent::increaseHealth(int h)
{
	int newHealth = _health + h;
	if (newHealth < _maxHealth) _health = newHealth;
}

void PlayerHealthComponent::increaseHealth()
{
	increaseHealth(1);
}

int PlayerHealthComponent::getHealth() { return _health; }

int PlayerHealthComponent::getMaxHealth() { return _maxHealth; }

void PlayerHealthComponent::usePotion()
{
	if (_potions > 0)
	{
		_health = _maxHealth;
		_potions--;
	}
}

void PlayerHealthComponent::addPotion()
{
	if (_potions + 1 <= _maxPotions)
		_potions++;
}