#pragma once

#include <SFML/Graphics.hpp>
#include <maths.h>
#include <memory>
#include <string>
#include <vector>

#define ls LevelSystem

class LevelSystem {
public:
  static void loadLevelFile(const std::string&, float tileSize = 100.0f);
  static void unload();
  static void render(sf::RenderWindow& window);

  typedef unsigned char Tile;

  enum TILES {
    EMPTY = ' ',
    START = 's',
    END = 'e', // to delete
    EXIT_1 = '1',
    EXIT_2 = '2',
    EXIT_3 = '3',
    EXIT_4 = '4',
    EXIT_5 = '5',
    EXIT_6 = '6',
    EXIT_7 = '7',
    EXIT_8 = '8',
    EXIT_9 = '9',
    WALL = 'w',
    ENEMY = 'n', // to delete
		ENEMY_A = 'A',
		ENEMY_B = 'B',
		ENEMY_C = 'C'
  };

  static Tile getTile(sf::Vector2ul);

  static Tile getTileAt(sf::Vector2f);

  static bool isOnGrid(sf::Vector2f);

  static size_t getWidth();

  static size_t getHeight();

  static sf::Vector2f getTilePosition(sf::Vector2ul);

  static std::vector<sf::Vector2ul> findTiles(Tile);

  //static sf::Color getColor(Tile t);
	static sf::IntRect getSpriteRect(Tile t);

  //static void setColor(Tile t, sf::Color c);
	static void setSpriteRect(Tile t, sf::IntRect r);

  static void setOffset(const sf::Vector2f& _offset);

  static const sf::Vector2f& getOffset();

  static float getTileSize();

protected:
  static std::unique_ptr<Tile[]> _tiles;
  static size_t _width;
  static size_t _height;
  static sf::Vector2f _offset;

	static sf::Sprite _map;

  static void buildSprites();

  static float _tileSize; // for rendering
	static std::map<Tile, sf::IntRect> _rectMap;

private:
  LevelSystem() = delete;

  ~LevelSystem() = delete;
};
