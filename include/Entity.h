#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <stack>
#include <map>
#include "MovementComponent.h"
#include "AnimationComponent.h"

class Entity {
private:
  void initVariables();

protected:

  sf::Sprite sprite;

  MovementComponent* movementComponent;
  AnimationComponent* animationComponent;
public:
  Entity();
  virtual ~Entity();

  // Component functions
  void setTexture(sf::Texture& Texture);
  void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
  void createAnimationComponent(sf::Texture& texture_sheet);

  // functions
  virtual void setPosition(const float, const float);
  virtual void move(const float, const float, const float& dt);
  virtual void update(const float& dt);
  virtual void render(sf::RenderTarget* target);
};

#endif
