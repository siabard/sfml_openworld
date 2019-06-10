#ifndef __MOVEMENT_COMPONENT_H__
#define __MOVEMENT_COMPONENT_H__

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class MovementComponent {
private:
  float maxVelocity;

  sf::Vector2f velocity;
  sf::Vector2f acceleration;
  sf::Vector2f deceleration;

  // Initialize functions

public:
  MovementComponent(float maxVelocity);
  virtual ~MovementComponent();

  // Accessors
  const sf::Vector2f& getVelocity() const;
  // functions

  void move(const float, const float);
  void update(const float& );
};

#endif
