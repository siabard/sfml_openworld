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
  this->createHitboxComponent(sprite, 86.f, 74.f, 86.f, 111.f);
  this->createAnimationComponent(texture);

  this->animationComponent->addAnimation("IDLE", 10.f, 0, 0, 13, 0, 192, 192);
  this->animationComponent->addAnimation("WALK", 8.f, 0, 1, 11, 1, 192, 192);
  this->animationComponent->addAnimation("ATTACK", 7.f, 0, 2, 13, 2, 192*2, 192);
}

Player::~Player() {}

void Player::update(const float& dt) {
  if(this->movementComponent) {
    this->movementComponent->update(dt);
  }

  if(this->animationComponent) {
    if(this->movementComponent->getState(movement_state::IDLE)) {
      this->animationComponent->play("IDLE", dt);
    } else if(this->movementComponent->getState(movement_state::MOVING_LEFT)) {
      this->sprite.setOrigin(0.f, 0.f);
      this->sprite.setScale(1.f, 1.f);
      this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
    } else if(this->movementComponent->getState(movement_state::MOVING_RIGHT)) {
      this->sprite.setOrigin(258.f, 0.f);
      this->sprite.setScale(-1.f, 1.f);
      this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
    } else if(this->movementComponent->getState(movement_state::MOVING_UP) || this->movementComponent->getState(movement_state::MOVING_DOWN)) {
      this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
    }
  }

  if(this->hitboxComponent) {
    this->hitboxComponent->update();
  }
}
