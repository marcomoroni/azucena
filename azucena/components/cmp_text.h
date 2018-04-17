#pragma once

#include <SFML/Graphics/Text.hpp>
#include <ecm.h>

class TextComponent : public Component {
public:
	TextComponent() = delete;
	explicit TextComponent(Entity* p, const std::string& str = "");
	void update(double dt) override;
	void render() override;
	~TextComponent() override = default;
	sf::Text* getText() { return &_text; }

protected:
	std::shared_ptr<sf::Font> _font;
	sf::Text _text;
};
