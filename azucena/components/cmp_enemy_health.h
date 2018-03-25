#pragma once

#include <ecm.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class EnemyHealthComponent : public Component
{
private:
	int _maxHealth;
	int _health;

	// For health bar
	int _spriteSize = 16;
	std::shared_ptr<sf::Texture> _tex = std::make_shared<sf::Texture>();
	std::shared_ptr<sf::Sprite> _backSprite;
	std::vector<std::shared_ptr<sf::Sprite>> _heartSprites;

public:
	void update(double) override;
	void render() override;
	explicit EnemyHealthComponent(Entity* p, int maxHealth);
	EnemyHealthComponent() = delete;
	void decreaseHealth();
	void decreaseHealth(int);
	void increaseHealth();
	void increaseHealth(int);
	int GetHealth();
	int GetMaxHealth();
};