#include "cmp_text.h"
#include <system_renderer.h>
#include <system_resources.h>

void TextComponent::update(double dt) {
	_text.setPosition(_parent->getPosition());
}

void TextComponent::render() { Renderer::queue(&_text); }

void TextComponent::setText(const std::string& str) {
	_string = str;
	_text.setString(_string);
	_text.setOrigin(_text.getLocalBounds().width / 2, _text.getLocalBounds().height / 2);
}

TextComponent::TextComponent(Entity* const p, const std::string& str)
    : Component(p), _string(str) {
  _font = Resources::get<sf::Font>("RobotoMono-Regular.ttf");
  _text.setFont(*_font);
	_text.setCharacterSize(10);
	setText(_string);
}