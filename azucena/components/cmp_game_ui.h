#pragma once

#include <ecm.h>
#include "SFML/Graphics.hpp"
#include "cmp_player_health.h"

class GameUIComponent : public Component
{
private:
	std::shared_ptr<Entity> _player;

	std::shared_ptr<sf::Texture> _tex;

	// Player health
	int _player_health_sprite_size;
	sf::Sprite _player_health_left;
	sf::Sprite _player_health_right;
	std::vector<sf::Sprite> _player_health_hearts;

public:
	GameUIComponent() = delete;
	explicit GameUIComponent(Entity* p, std::shared_ptr<Entity> player);
	void update(double dt) override;
	void render() override;
};