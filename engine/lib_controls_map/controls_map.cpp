#include "controls_map.h"

using namespace sf;

//std::map<std::string, GameKey> Controls::Keys;
std::shared_ptr<std::map<std::string, GameKey>> _keys;

std::map<std::string, GameKey>& Controls::GetKeys()
{
	return *_keys;
}

bool Controls::testEvent(GameKey k, Event e)
{
	// Mouse input
	if (k.inputType == MouseInput &&
		k.eventType == e.type &&
		k.mouseButton == e.mouseButton.button)
	{
		return true;
	}

	// Keyboard event
	if (k.inputType == KeyboardInput &&
		k.eventType == e.type &&
		k.keyCode == e.key.code)
	{
		return true;
	}

	return false;
}