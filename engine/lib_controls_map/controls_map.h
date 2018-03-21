//https://github.com/SFML/SFML/wiki/Tutorial:-Manage-dynamic-key-binding

#pragma once

#include <SFML\Window.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <fstream>

enum InputType
{
	KeyboardInput,
	MouseInput,
	JoysticInput
};

struct GameKey
{
	InputType inputType;
	sf::Event::EventType eventType;
	sf::Keyboard::Key keyCode;
	sf::Mouse::Button mouseButton;
};

class Controls
{
public:
	static std::map<std::string, GameKey> Keys;
	static bool testEvent(GameKey, sf::Event);
};