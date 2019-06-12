#include "include/Player.h"

// Initializer Function
void Player::initVariables() {

}
void Player::initComponents() {

}


Player::Player(float x, float y, sf::Texture& texture) {
  this->initVariables();
  this->initComponents();
  this->setPosition(x, y);

  this->createMovementComponent(300.f, 15.f, 5.f);
  this->createAnimationComponent(texture);

  this->animationComponent->addAnimation("IDLE_LEFT", 10.f, 0, 0, 13, 0, 192, 192);
  this->animationComponent->addAnimation("WALK_LEFT", 10.f, 0, 1, 11, 1, 192, 192);
}

Player::~Player() {}

void Player::update(const float& dt) {
  if(this->movementComponent) {
    this->movementComponent->update(dt);
  }

  if(this->animationComponent) {
    if(this->movementComponent->getState(movement_state::IDLE)) {
      this->animationComponent->play("IDLE_LEFT", dt);
    } else if(this->movementComponent->getState(movement_state::MOVING_LEFT)) {
      this->animationComponent->play("WALK_LEFT", dt);
    }
  }
}
