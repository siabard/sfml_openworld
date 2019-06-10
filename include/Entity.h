#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <stack>
#include <map>

class Entity {
private:
  void initVariables();

protected:

  sf::Texture* texture;
  sf::Sprite* sprite;

  float movementSpeed;

public:
  Entity();
  virtual ~Entity();

  // Component functions
  void createSprite(sf::Texture* Texture);

  // functions
  virtual void setPosition(const float, const float);
  virtual void move(const float& dt, const float, const float);
  virtual void update(const float& dt);
  virtual void render(sf::RenderTarget* target);
};

#endif
