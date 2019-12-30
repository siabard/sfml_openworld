#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "HitboxComponent.h"
#include "AttributeComponent.h"
#include "SkillComponent.h"

class Entity {
private:
  void initVariables();

protected:

  sf::Sprite sprite;

  HitboxComponent* hitboxComponent;
  MovementComponent* movementComponent;
  AnimationComponent* animationComponent;
  AttributeComponent* attributeComponent;
  SkillComponent* skillComponent;


public:
  Entity();
  virtual ~Entity();

  // Component functions
  void setTexture(sf::Texture& Texture);
  void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
  void createAnimationComponent(sf::Texture& texture_sheet);
  void createHitboxComponent(sf::Sprite& sprite, const float offset_x, const float offset_y, const float width, const float height);
  void createAttributeComponent(const unsigned level);
  void createSkillComponent();

  // accessors
  virtual const sf::Vector2f& getPosition() const;
  virtual const sf::Vector2f getCenter() const;
  virtual const sf::FloatRect getGlobalBounds() const;
  virtual const sf::Vector2i getGridPosition(const int gridSize) const;
  virtual const sf::FloatRect getNextPositionBounds(const float& dt) const;

  // functions
  virtual void setPosition(const float, const float);
  virtual void move(const float, const float, const float& dt);
  virtual void stopVelocity();
  virtual void stopVelocityX();
  virtual void stopVelocityY();

  // Calculations
  virtual const float getDistance(const Entity& point) const;

  virtual void update(const float& dt, sf::Vector2f& mouse_pos_view) = 0;
  virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false) = 0;

};

#endif
