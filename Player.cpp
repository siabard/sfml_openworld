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

  this->createMovementComponent(350.f, 1500.f, 500.f);
  this->createHitboxComponent(sprite, 86.f, 74.f, 86.f, 111.f);
  this->createAnimationComponent(texture);
  this->createAttributeComponent(1);

  this->animationComponent->addAnimation("IDLE", 10.f, 0, 0, 13, 0, 192, 192);
  this->animationComponent->addAnimation("WALK", 7.f, 0, 1, 11, 1, 192, 192);
  this->animationComponent->addAnimation("ATTACK", 6.f, 0, 2, 13, 2, 192*2, 192);
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
    this->attacking = true;
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

    if(this->sprite.getScale().x < 0) {
      this->sprite.setOrigin(0.f, 0.f);
      this->sprite.setScale(1.f, 1.f);
    }

    this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
  } else if(this->movementComponent->getState(movement_state::MOVING_RIGHT)) {
    if(this->sprite.getScale().x > 0.f) {
      this->sprite.setOrigin(258.f, 0.f);
      this->sprite.setScale(-1.f, 1.f);
    }
    this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
  } else if(this->movementComponent->getState(movement_state::MOVING_UP) || this->movementComponent->getState(movement_state::MOVING_DOWN)) {
    this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
  }


}


void Player::update(const float& dt) {

  this->movementComponent->update(dt);

  this->updateAttack();

  this->updateAnimation(dt);

  this->hitboxComponent->update();

}


void Player::render(sf::RenderTarget& target) {
  target.draw(this->sprite);

  if(this->hitboxComponent) {
    this->hitboxComponent->render(target);
  }
}
