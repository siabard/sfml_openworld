#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <stack>
#include <map>
#include "MovementComponent.h"

class Entity {
private:
  void initVariables();

protected:

  sf::Texture*  texture;
  sf::Sprite sprite;

  MovementComponent* movementComponent;

public:
  Entity();
  virtual ~Entity();

  // Component functions
  void setTexture(sf::Texture& Texture);
  void createMovementComponent(const float maxVelocity);

  // functions
  virtual void setPosition(const float, const float);
  virtual void move(const float& dt, const float, const float);
  virtual void update(const float& dt);
  virtual void render(sf::RenderTarget* target);
};

#endif
