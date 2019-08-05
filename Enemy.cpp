#include "include/stdafx.h"
#include "include/Enemy.h"

// Initializer Function
void Enemy::initVariables() {
  this->attacking = false;
}

void Enemy::initAnimation() {
  this->animationComponent->addAnimation("IDLE", 25.f, 0, 0, 3, 0, 60, 64);
  this->animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 1, 3, 1, 60, 64);
  this->animationComponent->addAnimation("WALK_LEFT", 11.f, 0, 2, 3, 2, 60, 64);
  this->animationComponent->addAnimation("WALK_RIGHT", 11.f, 0, 3, 3, 3, 60, 64);
  this->animationComponent->addAnimation("WALK_UP", 11.f, 0, 4, 3, 4, 60, 64);
  this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 1, 2, 60, 64);
}

Enemy::Enemy( float x, float y, sf::Texture& texture) {
  this->initVariables();

  this->createHitboxComponent(sprite, 13.f, 39.f, 30.f, 30.f);
  this->createMovementComponent(50.f, 1600.f, 1000.f);
  this->createAnimationComponent(texture);

  this->setPosition(x, y);
  this->initAnimation();
}

Enemy::~Enemy() {}

void Enemy::updateAnimation(const float& dt) {
  if (this->attacking) {

  }

  if(this->movementComponent->getState(movement_state::IDLE)) {
    this->animationComponent->play("IDLE", dt);
  } else if(this->movementComponent->getState(movement_state::MOVING_LEFT)) {

    this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
  } else if(this->movementComponent->getState(movement_state::MOVING_RIGHT)) {
    this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
  } else if(this->movementComponent->getState(movement_state::MOVING_UP)) {
    this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
  } else if(this->movementComponent->getState(movement_state::MOVING_DOWN)) {
    this->animationComponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
  }

}


void Enemy::update(const float& dt, sf::Vector2f& mouse_pos_view) {

  this->movementComponent->update(dt);

  //this->updateAttack();

  this->updateAnimation(dt);

  this->hitboxComponent->update();

}


void Enemy::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox ) {

  if(shader) {
    shader->setUniform("hasTexture", true);
    shader->setUniform("lightPos", light_position);

    target.draw(this->sprite, shader);

  } else {
    target.draw(this->sprite);
  }

  if (show_hitbox) {
    if(this->hitboxComponent) {
      this->hitboxComponent->render(target);
    }
  }
}
