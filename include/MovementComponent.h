#ifndef __MOVEMENT_COMPONENT_H__
#define __MOVEMENT_COMPONENT_H__

enum movement_state {IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN};

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
  const float& getMaxVelocity() const;
  const sf::Vector2f& getVelocity() const;
  // functions
  const bool getState(const short unsigned state) const;

  void move(const float, const float, const float&);
  void update(const float& );
};

#endif
