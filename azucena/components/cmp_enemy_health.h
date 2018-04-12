#pragma once

#include <ecm.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class EnemyHealthComponent : public Component
{
private:
	int _maxHealth;
	int _health;
	float _immunity = -1.0f;

	// For health bar
	std::vector<Entity*> _healthSprites;

public:
	void update(double) override;
	void render() override;
	explicit EnemyHealthComponent(Entity* p, int maxHealth);
	EnemyHealthComponent() = delete;
	void decreaseHealth();
	void decreaseHealth(int);
	void increaseHealth();
	void increaseHealth(int);
	int getHealth();
	int getMaxHealth();
};