#pragma once

#include "ecm.h"
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class SpriteComponent : public Component {
protected:
  std::shared_ptr<sf::Sprite> _sprite;
	std::shared_ptr<sf::Texture> _tex;

public:
  SpriteComponent() = delete;

  explicit SpriteComponent(Entity* p);
  void update(double dt) override;
  void render() override;

  sf::Sprite& getSprite() const;
	sf::Texture& getTexure() const;
	void setTexture(std::shared_ptr<sf::Texture> tx) { _tex = tx; _sprite->setTexture(*tx); }
  template <typename... Targs> void setSprite(Targs... params) {
    _sprite.reset(new sf::Sprite(params...));
  }
};

class ShapeComponent : public Component {
protected:
  std::shared_ptr<sf::Shape> _shape;
  // sf::Shape _shape;

public:
  ShapeComponent() = delete;

  explicit ShapeComponent(Entity* p);

  void update(double dt) override;
  void render() override;
  sf::Shape& getShape() const;
  template <typename T, typename... Targs> void setShape(Targs... params) {
    _shape.reset(new T(params...));
  }
};