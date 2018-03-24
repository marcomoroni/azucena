#include "cmp_text.h"
#include <system_renderer.h>
#include <system_resources.h>

using namespace std;
using namespace sf;

void TextComponent::update(double dt) {
	_text.setPosition(_parent->getPosition() /*+ _offset*/);
}

void TextComponent::render() { Renderer::queue(&_text); }

TextComponent::TextComponent(Entity* const p, const std::string& str)
    : Component(p), _string(str) {
  _text.setString(_string);
  _font = Resources::get<sf::Font>("RobotoMono-Regular.ttf");
  _text.setFont(*_font);
}

void TextComponent::SetText(const std::string& str) {
  _string = str;
  _text.setString(_string);
}

Text& TextComponent::getText() { return _text; }