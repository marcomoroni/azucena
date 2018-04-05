#include "LevelSystem.h"
#include <system_resources.h>
#include <fstream>

using namespace std;
using namespace sf;

float LevelSystem::_tileSize(32);

std::map<LevelSystem::Tile, sf::IntRect> LevelSystem::_rectMap{
	{ EMPTY, IntRect(0, _tileSize, _tileSize, _tileSize) },
	{ START, IntRect(0, _tileSize, _tileSize, _tileSize) }, // Same as empty
	{ END, IntRect(_tileSize * 4, _tileSize * 2, _tileSize, _tileSize) },
  { EXIT_1, IntRect(0, _tileSize, _tileSize, _tileSize) },
  { EXIT_2, IntRect(0, _tileSize, _tileSize, _tileSize) },
  { EXIT_3, IntRect(0, _tileSize, _tileSize, _tileSize) },
  { EXIT_4, IntRect(0, _tileSize, _tileSize, _tileSize) },
  { EXIT_5, IntRect(0, _tileSize, _tileSize, _tileSize) },
  { EXIT_6, IntRect(0, _tileSize, _tileSize, _tileSize) },
  { EXIT_7, IntRect(0, _tileSize, _tileSize, _tileSize) },
  { EXIT_8, IntRect(0, _tileSize, _tileSize, _tileSize) },
  { EXIT_9, IntRect(0, _tileSize, _tileSize, _tileSize) },
  { KEY, IntRect(0, _tileSize, _tileSize, _tileSize) },
  { DOOR, IntRect(0, _tileSize, _tileSize, _tileSize) },
	{ WALL, IntRect(0, 0, _tileSize, _tileSize) },
	// All enemies have empty below them
	{ ENEMY_A, IntRect(0, _tileSize, _tileSize, _tileSize) },
	{ ENEMY_B, IntRect(0, _tileSize, _tileSize, _tileSize) },
  { ENEMY_C, IntRect(0, _tileSize, _tileSize, _tileSize) },
	{ MAIN_COLLECTIBLE, IntRect(0, _tileSize, _tileSize, _tileSize) } };

sf::IntRect LevelSystem::getSpriteRect(LevelSystem::Tile t) {
	auto it = _rectMap.find(t);
	if (it == _rectMap.end()) {
		// Pink texture // TODO
		return IntRect(12, 34, _tileSize, _tileSize);
	}
	return _rectMap[t];
}

void LevelSystem::setSpriteRect(LevelSystem::Tile t, sf::IntRect r) {
	_rectMap[t] = r;
}

std::unique_ptr<LevelSystem::Tile[]> LevelSystem::_tiles;
size_t LevelSystem::_width;
size_t LevelSystem::_height;

Vector2f LevelSystem::_offset(0.0f, 0.0f);
Sprite LevelSystem::_map;

void LevelSystem::loadLevelFile(const std::string& path, float tileSize) {

	_tileSize = tileSize;
	size_t w = 0, h = 0;
	string buffer;

	// Load in file to buffer
	ifstream f(path);
	if (f.good()) {
		f.seekg(0, std::ios::end);
		buffer.resize(f.tellg());
		f.seekg(0);
		f.read(&buffer[0], buffer.size());
		f.close();
	}
	else {
		throw string("Couldn't open level file: ") + path;
	}

	std::vector<Tile> temp_tiles;
	int widthCheck = 0;
	for (int i = 0; i < buffer.size(); ++i) {
		const char c = buffer[i];
		if (c == '\0') { break; }
		if (c == '\n') { // newline
			if (w == 0) {  // if we haven't written width yet
				w = i;       // set width
			}
			else if (w != (widthCheck - 1)) {
				throw string("non uniform width:" + to_string(h) + " ") + path;
			}
			widthCheck = 0;
			h++; // increment height
		}
		else {
			temp_tiles.push_back((Tile)c);
		}
		++widthCheck;
	}

	if (temp_tiles.size() != (w * h)) {
		throw string("Can't parse level file") + path;
	}
	_tiles = std::make_unique<Tile[]>(w * h);
	_width = w; // set static class vars
	_height = h;
	std::copy(temp_tiles.begin(), temp_tiles.end(), &_tiles[0]);
	cout << "Level " << path << " Loaded. " << w << "x" << h << std::endl;
	buildSprites();
}

shared_ptr<Texture> tex;
RenderTexture bigMapTexture;

void LevelSystem::buildSprites() {

	struct tp {
		sf::Vector2f pos;
		sf::IntRect intRect;
	};
	vector<tp> tps;
	for (size_t y = 0; y < _height; ++y) {
		for (size_t x = 0; x < _width; ++x) {
			Tile t = getTile({ x, y });
			tps.push_back({ getTilePosition({ x, y }), getSpriteRect(t) });
		}
	}

  tex.reset();
  tex = Resources::get<Texture>("tex.png");
	bigMapTexture.create(_tileSize * _width, _tileSize * _height);
	bigMapTexture.clear(Color::Red);

	// Make everything one big sprite
	for (auto& t : tps) {
		auto s = Sprite();
		s.setTexture(*tex);
		s.setTextureRect(t.intRect);
		s.setPosition(t.pos);
		bigMapTexture.draw(s);
	}

	bigMapTexture.display();
	_map = Sprite(bigMapTexture.getTexture());
}

void LevelSystem::render(RenderWindow& window) {
	window.draw(_map);
}

LevelSystem::Tile LevelSystem::getTile(sf::Vector2ul p) {
	if (p.x > _width || p.y > _height) {
		//throw string("Tile out of range: ") + to_string(p.x) + "," +
		//	to_string(p.y) + ")";
		// Return EMPTY to avoid crash if player goes out of map
		return TILES::EMPTY;
	}
	return _tiles[(p.y * _width) + p.x];
}

size_t LevelSystem::getWidth() { return _width; }

size_t LevelSystem::getHeight() { return _height; }

sf::Vector2f LevelSystem::getTilePosition(sf::Vector2ul p) {
	return (Vector2f(p.x, p.y) * _tileSize) + _offset;
}

std::vector<sf::Vector2ul> LevelSystem::findTiles(LevelSystem::Tile type) {
	auto v = vector<sf::Vector2ul>();
	for (size_t i = 0; i < _width * _height; ++i) {
		if (_tiles[i] == type) {
			v.push_back({ i % _width, i / _width });
		}
	}

	return v;
}

LevelSystem::Tile LevelSystem::getTileAt(Vector2f v) {
	auto a = v - _offset;
	if (a.x < 0 || a.y < 0) {
		throw string("Tile out of range ");
	}
	return getTile(Vector2ul((v - _offset) / (_tileSize)));
}

bool LevelSystem::isOnGrid(sf::Vector2f v) {
	auto a = v - _offset;
	if (a.x < 0 || a.y < 0) {
		return false;
	}
	auto p = Vector2ul((v - _offset) / (_tileSize));
	if (p.x > _width || p.y > _height) {
		return false;
	}
	return true;
}

void LevelSystem::setOffset(const Vector2f& _offset) {
	LevelSystem::_offset = _offset;
	buildSprites();
}

void LevelSystem::unload() {
	cout << "LevelSystem unloading\n";
	//_sprites.clear();
	_tiles.reset();
	_width = 0;
	_height = 0;
	_offset = { 0, 0 };
}

const Vector2f& LevelSystem::getOffset() { return _offset; }

float LevelSystem::getTileSize() { return _tileSize; }