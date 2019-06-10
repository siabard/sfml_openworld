#include "include/MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration)
  :  sprite(sprite), maxVelocity(maxVelocity) , acceleration(acceleration), deceleration(deceleration) {
}

MovementComponent::~MovementComponent() {

}

void  MovementComponent::update(const float& dt) {
  // Decelaeration the sprite and control maximum velocity

  // X Acceleration
  if(this->velocity.x > 0.f) {
    // Check Max X Velocity
    if(this->velocity.x > this->maxVelocity)
      this->velocity.x = this->maxVelocity;

    // X Deaceleration
    this->velocity.x -= this->deceleration;

    // Bound Condition
    if(this->velocity.x < 0.f)
      this->velocity.x = 0.f;
  } else if(this->velocity.x < 0.f) {
    // Check Max X Velocity
    if(this->velocity.x < -this->maxVelocity)
      this->velocity.x = -this->maxVelocity;

    // X Deaceleration
    this->velocity.x += this->deceleration;

    // Bound Condition
    if(this->velocity.x > 0.f)
      this->velocity.x = 0.f;
  }


  if(this->velocity.y > 0.f) {
    if(this->velocity.y > this->maxVelocity)
      this->velocity.y = this->maxVelocity;

    this->velocity.y -= this->deceleration;

    if(this->velocity.y < 0.f)
      this->velocity.y = 0.f;
  } else if (this->velocity.y < 0.f) {
    if(this->velocity.y < -this->maxVelocity)
      this->velocity.y = -this->maxVelocity;

    this->velocity.y += this->deceleration;

    if(this->velocity.y > 0.f)
      this->velocity.y = 0.f;
  }
  // Final move here
  this->sprite.move(this->velocity * dt); // Uses velocity
}

void MovementComponent::move(const float dir_x, const float dir_y, const float& dt) {
  // Acceleration a sprite until it reaches the max velocity

  this->velocity.x += this->acceleration * dir_x;
  this->velocity.y += this->acceleration * dir_y;

}

const sf::Vector2f& MovementComponent::getVelocity() const {
  return this->velocity;
}
