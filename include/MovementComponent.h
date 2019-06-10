#ifndef __MOVEMENT_COMPONENT_H__
#define __MOVEMENT_COMPONENT_H__

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class MovementComponent {
private:
  sf::Sprite& sprite;

  float maxVelocity;
  float acceleration;
  float deceleration;

  sf::Vector2f velocity;
  // Initialize functions

public:
  MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
  virtual ~MovementComponent();

  // Accessors
  const sf::Vector2f& getVelocity() const;
  // functions

  void move(const float, const float, const float&);
  void update(const float& );
};

#endif
