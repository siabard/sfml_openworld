#include "include/stdafx.h"
#include "include/Player.h"

// Initializer Function
void Player::initVariables() {
  this->attacking = false;
}
void Player::initComponents() {

}


Player::Player(float x, float y, sf::Texture& texture) {
  this->initVariables();
  this->initComponents();
  this->setPosition(x, y);

  this->createHitboxComponent(sprite, 10.f, 5.f, 44.f, 54.f);
  this->createMovementComponent(200.f, 1500.f, 900.f);
  this->createAnimationComponent(texture);
  this->createAttributeComponent(1);

  this->animationComponent->addAnimation("IDLE", 15.f, 0, 0, 8, 0, 64, 64);
  this->animationComponent->addAnimation("WALK_DOWN", 12.f, 0, 1, 3, 1, 64, 64);
  this->animationComponent->addAnimation("WALK_LEFT", 12.f, 4, 1, 7, 1, 64, 64);
  this->animationComponent->addAnimation("WALK_RIGHT", 12.f, 8, 1, 11, 1, 64, 64);
  this->animationComponent->addAnimation("WALK_UP", 12.f, 12, 1, 15, 1, 64, 64);
  this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 1, 2, 64, 64);
}

Player::~Player() {}

// accessors
AttributeComponent* Player::getAttributeComponent() {
  return this->attributeComponent;
}

// functions

void Player::loseHP(const int hp) {
  this->attributeComponent->hp -= hp;

  if(this->attributeComponent->hp < 0)
    this->attributeComponent->hp = 0;
}

void Player::gainHP(const int hp) {
  this->attributeComponent->hp += hp;
  if(this->attributeComponent->hp > this->attributeComponent->hpMax)
    this->attributeComponent->hp = this->attributeComponent->hpMax;
}

void Player::loseEXP(const int exp) {
  this->attributeComponent->exp -= exp;

  if(this->attributeComponent->exp < 0) {
    this->attributeComponent->exp = 0;
  }
}

void Player::gainEXP(const int exp) {
  this->attributeComponent->gainExp(exp);

}

void Player::updateAttack() {

  if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    //this->attacking = true;
  }

}
void Player::updateAnimation(const float& dt) {
  if (this->attacking) {

    // set origin depending on direction
    if(this->sprite.getScale().x > 0.f) {
      // facing  left
      this->sprite.setOrigin(96.f, 0.f);
    } else {
      // face  right
      this->sprite.setOrigin(258.f + 96.f, 0.f);
    }

    // animate and check for animation end
    if(this->animationComponent->play("ATTACK", dt, true)) {
      this->attacking = false;

      // set origin depending on direction
      if(this->sprite.getScale().x > 0.f) {
        // facing  left
        this->sprite.setOrigin(0.f, 0.f);
      } else {
        // face  right
        this->sprite.setOrigin(258.f, 0.f);
      }


    }
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


void Player::update(const float& dt) {

  this->movementComponent->update(dt);

  this->updateAttack();

  this->updateAnimation(dt);

  this->hitboxComponent->update();

}


void Player::render(sf::RenderTarget& target, const bool show_hitbox) {
  target.draw(this->sprite);

  if (show_hitbox) {
    if(this->hitboxComponent) {
      this->hitboxComponent->render(target);
    }
  }
}
