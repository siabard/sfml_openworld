#include "include/stdafx.h"
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
    this->velocity.x -= this->deceleration * dt;

    // Bound Condition
    if(this->velocity.x < 0.f)
      this->velocity.x = 0.f;
  } else if(this->velocity.x < 0.f) {
    // Check Max X Velocity
    if(this->velocity.x < -this->maxVelocity)
      this->velocity.x = -this->maxVelocity;

    // X Deaceleration
    this->velocity.x += this->deceleration * dt;

    // Bound Condition
    if(this->velocity.x > 0.f)
      this->velocity.x = 0.f;
  }


  if(this->velocity.y > 0.f) {
    if(this->velocity.y > this->maxVelocity)
      this->velocity.y = this->maxVelocity;

    this->velocity.y -= this->deceleration * dt;

    if(this->velocity.y < 0.f)
      this->velocity.y = 0.f;
  } else if (this->velocity.y < 0.f) {
    if(this->velocity.y < -this->maxVelocity)
      this->velocity.y = -this->maxVelocity;

    this->velocity.y += this->deceleration * dt;

    if(this->velocity.y > 0.f)
      this->velocity.y = 0.f;
  }
  // Final move here
  this->sprite.move(this->velocity * dt); // Uses velocity
}

void MovementComponent::move(const float dir_x, const float dir_y, const float& dt) {
  // Acceleration a sprite until it reaches the max velocity

  this->velocity.x += this->acceleration * dir_x * dt;
  this->velocity.y += this->acceleration * dir_y * dt;

}


const float& MovementComponent::getMaxVelocity() const {
  return this->maxVelocity;
}


const sf::Vector2f& MovementComponent::getVelocity() const {
  return this->velocity;
}


const bool MovementComponent::getState(const short unsigned state) const {
  switch(state) {
  case movement_state::IDLE:
    if (this->velocity.x == 0.f && this->velocity.y == 0.f)
      return true;

    break;
  case movement_state::MOVING:
    if (this->velocity.x != 0.f || this->velocity.y != 0.f)
      return true;

    break;
  case movement_state::MOVING_LEFT:
    if (this->velocity.x < 0.f)
      return true;

    break;
  case movement_state::MOVING_RIGHT:
    if (this->velocity.x > 0.f)
      return true;

    break;
  case movement_state::MOVING_UP:
    if (this->velocity.y < 0.f)
      return true;
    break;
  case movement_state::MOVING_DOWN:
    if (this->velocity.y > 0.f)
      return true;

    break;
  default:
    break;
  }

  return false;
}


void MovementComponent::stopVelocity() {
  /* Resets the velocity to 0. */

  this->velocity.x = 0.f;
  this->velocity.y = 0.f;
}

void MovementComponent::stopVelocityX() {
  /* Resets the velocity x to 0. */

  this->velocity.x = 0.f;
}

void MovementComponent::stopVelocityY() {
  /* Resets the velocity y to 0. */

  this->velocity.y = 0.f;
}
