#include "cmp_button.h"
#include "engine.h"
#include <SFML/Window/Mouse.hpp>

using namespace std;
using namespace sf;

ButtonComponent::ButtonComponent(Entity* p, shared_ptr<ShapeComponent> s, shared_ptr<TextComponent> t)
	: _shapeCmp(s), _textCmp(t), Component(p)
{
}

void ButtonComponent::update(double dt)
{
	// Highlight button if mouse hovers shape
	auto mousePos = Engine::GetWindow().mapPixelToCoords(Mouse::getPosition(Engine::GetWindow()));
	if (_shapeCmp->getShape().getGlobalBounds().contains(mousePos))
	{
		setHighlight(true);
	}
	else
	{
		setHighlight(false);
	}
}

void ButtonComponent::setHighlight(bool h)
{
	if (h != _isHighlited)
	{
		_isHighlited = h;
		if (h)
		{
			// Highlithed button
			_shapeCmp->getShape().setFillColor(Color(255, 255, 255, 150));
		}
		else
		{
			// Non highlithed button
			_shapeCmp->getShape().setFillColor(Color(255, 255, 255, 80));
		}
	}
}

bool ButtonComponent::isSelected()
{
	if (_isHighlited)
	{
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			return true;
		}
	}
	return false;
}