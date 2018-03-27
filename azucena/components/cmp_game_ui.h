#pragma once

#include <ecm.h>
#include "SFML/Graphics.hpp"

class GameUIComponent : public Component
{
private:
	sf::RectangleShape r;
public:
	GameUIComponent() = delete;
	explicit GameUIComponent(Entity* p);
	void update(double dt) override;
	void render() override;
};