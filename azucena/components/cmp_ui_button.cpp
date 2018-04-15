#include "cmp_ui_button.h"
#include "system_renderer.h"
#include "system_resources.h"
#include "engine.h"
#include "SFML/Graphics.hpp"
#include "../controls.h"

using namespace std;
using namespace sf;

UIButtonComponent::UIButtonComponent(Entity* p, string label)
	: Component(p)
{
	_label = label;
	_size = { 300.0f, 40.0f };
	_shape = make_shared<RectangleShape>(_size);
	_shape->setOrigin(_shape->getLocalBounds().width / 2, _shape->getLocalBounds().height / 2);
	_text = make_shared<Text>();
	_text->setString(_label);
	_text->setScale(0.8f, 0.8f);
	_text->setFont(*Resources::get<Font>("monogram.ttf"));
	_text->setOrigin(_text->getLocalBounds().width / 2, _text->getLocalBounds().height / 2 + 15.0f); // 15.0f ?

	setHighlighted(true);
	//setHighlighted(false);
	_selected = false;
}

void UIButtonComponent::update(double dt)
{
	_shape->setPosition(_parent->getPosition());
	_text->setPosition(_parent->getPosition());

	// Select
	_selected = false;
	if (_highlighted)
	{
		Event event;
		while (Engine::GetWindow().pollEvent(event))
		{
			if (event.type == Event::KeyReleased)
			{
				printf("---\n");
				if (event.key.code == Controls::GetKeyboardKey("Enter"))
				{
					_selected = true;
					printf("Selected\n");
				}
			}
			if (event.type == Event::MouseButtonPressed)
			{
				printf("Mouse button pressed\n");
			}
		}
	}
}

void UIButtonComponent::render()
{
	Renderer::queue(_shape.get());
	Renderer::queue(_text.get());
}

void UIButtonComponent::setHighlighted(bool h)
{
	_highlighted = h;
	_shape->setFillColor(_highlighted ? _shapeColourHighligted : _shapeColour);
	_text->setColor(_highlighted ? _labelColourHighligted : _labelColour);
}

bool UIButtonComponent::isHighlighted() { return _highlighted; }

bool UIButtonComponent::isSelected() { return _selected; }