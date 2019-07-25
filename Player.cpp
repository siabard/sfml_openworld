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

  // Visual Weapon
  if(!this->weapon_texture.loadFromFile("Resource/images/sprites/player/sword.png")) {
    std::cout << "ERROR::PLAYER::COULD NOT LOAD WEAPON TEXTURE" << std::endl;
  }
  this->weapon_sprite.setTexture(this->weapon_texture);

  this->weapon_sprite.setOrigin(this->weapon_sprite.getGlobalBounds().width / 2.f,
                                this->weapon_sprite.getGlobalBounds().height
                                );
}

Player::~Player() {}

// accessors
AttributeComponent* Player::getAttributeComponent() {
  return this->attributeComponent;
}

// functions

void Player::loseHP(const int hp) {
  this->attributeComponent->loseHP(hp);
}

void Player::gainHP(const int hp) {
  this->attributeComponent->gainHP(hp);
}

void Player::loseEXP(const int exp) {
  this->attributeComponent->loseEXP(exp);
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


void Player::update(const float& dt, sf::Vector2f& mouse_pos_view) {

  this->movementComponent->update(dt);

  this->updateAttack();

  this->updateAnimation(dt);

  this->hitboxComponent->update();


  // update visual weapon
  this->weapon_sprite.setPosition(this->getCenter());

  float dX = mouse_pos_view.x - this->weapon_sprite.getPosition().x;
  float dY = mouse_pos_view.y - this->weapon_sprite.getPosition().y;

  const float PI = 3.14159265;
  float deg = atan2(dY, dX) * 180 / PI;

  this->weapon_sprite.setRotation(deg + 90.f);

}


void Player::render(sf::RenderTarget& target, sf::Shader* shader, const bool show_hitbox) {

  if(shader) {
    shader->setUniform("hasTexture", true);
    shader->setUniform("lightPos", this->getCenter());

    target.draw(this->sprite, shader);

    shader->setUniform("hasTexture", true);
    shader->setUniform("lightPos", this->getCenter());

    target.draw(this->weapon_sprite, shader);
  } else {
    target.draw(this->sprite);
    target.draw(this->weapon_sprite);
  }

  if (show_hitbox) {
    if(this->hitboxComponent) {
      this->hitboxComponent->render(target);
    }
  }
}
