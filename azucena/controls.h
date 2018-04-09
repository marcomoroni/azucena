#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>

class Controls
{
private:
	static std::map<std::string, sf::Keyboard::Key> _keyboardLookupTable;

public:
	static void initialise();
	static sf::Keyboard::Key GetKeyboardKey(std::string action);
	static void SetKeyboardKey(std::string action, sf::Keyboard::Key key);
};