#include "cmp_ui_button.h"
#include "system_renderer.h"
#include "system_resources.h"

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
	_text->setFont(*Resources::get<Font>("monogram.ttf"));
	_text->setOrigin(_text->getLocalBounds().width / 2, _text->getLocalBounds().height / 2 + 15.0f); // 15.0f ?

	setHighlighted(false);
	setSelected(false);
}

void UIButtonComponent::update(double dt)
{
	_shape->setPosition(_parent->getPosition());
	_text->setPosition(_parent->getPosition());
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

void UIButtonComponent::setSelected(bool s)
{
	_selected = s;
}

bool UIButtonComponent::isHighlighted() { return _highlighted; }

bool UIButtonComponent::isSelected() { return _selected; }