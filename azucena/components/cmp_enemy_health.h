#pragma once

#include <ecm.h>

class EnemyHealthComponent : public Component
{
private:
	int _maxHealth;
	int _health;

public:
	void update(double) override;
	void render() override {}
	explicit EnemyHealthComponent(Entity* p, int maxHealth);
	EnemyHealthComponent() = delete;
	void decreaseHealth();
	void decreaseHealth(int);
	void increaseHealth();
	void increaseHealth(int);
	int GetHealth();
	int GetMaxHealth();
};