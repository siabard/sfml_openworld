#include "include/stdafx.h"
#include "include/Enemy.h"

// Initializer Function
void Enemy::initVariables() {
  this->attacking = false;
}

void Enemy::initAnimation() {
  this->animationComponent->addAnimation("IDLE", 15.f, 0, 0, 8, 0, 64, 64);
  this->animationComponent->addAnimation("WALK_DOWN", 12.f, 0, 1, 3, 1, 64, 64);
  this->animationComponent->addAnimation("WALK_LEFT", 12.f, 4, 1, 7, 1, 64, 64);
  this->animationComponent->addAnimation("WALK_RIGHT", 12.f, 8, 1, 11, 1, 64, 64);
  this->animationComponent->addAnimation("WALK_UP", 12.f, 12, 1, 15, 1, 64, 64);
  this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 1, 2, 64, 64);
}

Enemy::Enemy(float x, float y, sf::Texture& texture) {
  this->initVariables();

  this->createHitboxComponent(sprite, 10.f, 5.f, 44.f, 54.f);
  this->createMovementComponent(200.f, 1600.f, 1000.f);
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


void Enemy::render(sf::RenderTarget& target, sf::Shader* shader, const bool show_hitbox) {

  if(shader) {
    shader->setUniform("hasTexture", true);
    shader->setUniform("lightPos", this->getCenter());

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
