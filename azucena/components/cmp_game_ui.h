#pragma once

#include <ecm.h>
#include "SFML/Graphics.hpp"

class UIComponent : public Component
{
private:
	sf::RectangleShape r;
public:
	UIComponent() = delete;
	explicit UIComponent(Entity* p);
	void update(double dt) override;
	void render() override;
};