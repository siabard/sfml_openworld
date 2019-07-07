#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "HitboxComponent.h"

class Entity {
private:
  void initVariables();

protected:

  sf::Sprite sprite;

  HitboxComponent* hitboxComponent;
  MovementComponent* movementComponent;
  AnimationComponent* animationComponent;
public:
  Entity();
  virtual ~Entity();

  // Component functions
  void setTexture(sf::Texture& Texture);
  void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
  void createAnimationComponent(sf::Texture& texture_sheet);
  void createHitboxComponent(sf::Sprite& sprite, const float offset_x, const float offset_y, const float width, const float height);

  // accessors
  virtual const sf::Vector2f& getPosition() const;
  virtual const sf::FloatRect getGlobalBounds() const;
  virtual const sf::Vector2u getGridPosition(const unsigned gridSize) const;
  virtual const sf::FloatRect getNextPositionBounds(const float& dt) const;

  // functions
  virtual void setPosition(const float, const float);
  virtual void move(const float, const float, const float& dt);
  virtual void stopVelocity();
  virtual void stopVelocityX();
  virtual void stopVelocityY();
  virtual void update(const float& dt) = 0;
  virtual void render(sf::RenderTarget& target) = 0;
};

#endif
