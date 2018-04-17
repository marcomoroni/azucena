#include "cmp_text.h"
#include <system_renderer.h>
#include <system_resources.h>

void TextComponent::update(double dt) {
	_text.setPosition(_parent->getPosition());
}

void TextComponent::render() { Renderer::queue(&_text); }

TextComponent::TextComponent(Entity* const p, const std::string& str)
	: Component(p) {
	_font = Resources::get<sf::Font>("monogram_extended.ttf");
	_text.setFont(*_font);
	_text.setString(str);
}