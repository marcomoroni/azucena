#pragma once

#include <ecm.h>
#include <SFML/Graphics.hpp>

class UIButtonComponent : public Component
{
public:
	void update(double dt) override;
	void render() override;
	explicit UIButtonComponent(Entity* p, std::string label);
	UIButtonComponent() = delete;
	void setHighlighted(bool);
	void setSelected(bool);
	bool isHighlighted();
	bool isSelected();

protected:
	std::shared_ptr<sf::RectangleShape> _shape;
	std::shared_ptr<sf::Text> _text;
	std::string _label;
	sf::Vector2f _size;
	sf::Color _shapeColour = sf::Color::Red;
	sf::Color _labelColour = sf::Color::White;
	sf::Color _shapeColourHighligted = sf::Color::Yellow;
	sf::Color _labelColourHighligted = sf::Color::Black;
	bool _highlighted;
	bool _selected;
};