#include "constrols.h"

#include <stdexcept>

using namespace std;

std::map<std::string, sf::Keyboard::Key> Controls::_keyboardLookupTable;

sf::Keyboard::Key Controls::GetKeyboardKey(std::string action)
{
	auto k = _keyboardLookupTable.find(action);
	if (k != _keyboardLookupTable.end())
	{
		return k->second;
	}
	else
	{
		throw invalid_argument("Action not known.");
	}
}

void Controls::SetKeyboardKey(std::string action, sf::Keyboard::Key key)
{
	_keyboardLookupTable[action] = key;
}