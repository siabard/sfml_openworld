#include "include/stdafx.h"
#include "include/Entity.h"


Entity::Entity() {
  this->initVariables();


}

Entity::~Entity() {
  if(this->movementComponent)
    delete this->movementComponent;

  if(this->animationComponent)
    delete this->animationComponent;

  if(this->hitboxComponent)
    delete this->hitboxComponent;
}


void Entity::initVariables() {
  this->movementComponent = nullptr;
  this->animationComponent = nullptr;
  this->hitboxComponent = nullptr;
}

void Entity::setTexture(sf::Texture& texture) {
  this->sprite.setTexture(texture);

}

void Entity::move(const float dir_x, const float dir_y, const float& dt) {
  if(this->movementComponent) {
    this->movementComponent->move(dir_x, dir_y, dt); // Sets velocity
  }

}

void Entity::update(const float& dt) {

}
void Entity::render(sf::RenderTarget& target) {

}

const sf::Vector2f& Entity::getPosition() const {
  if(this->hitboxComponent) {
    return this->hitboxComponent->getPosition();
  }

  return this->sprite.getPosition();
}

const sf::FloatRect Entity::getGlobalBounds() const {
  if (this->hitboxComponent) {
    return this->hitboxComponent->getGlobalBounds();
  }

  return this->sprite.getGlobalBounds();
}

void Entity::setPosition(const float x, const float y) {
  if(this->hitboxComponent)
    this->hitboxComponent->setPosition(x, y);
  else
    this->sprite.setPosition(x, y);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration) {
  this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture& texture_sheet) {
  this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::createHitboxComponent(sf::Sprite& sprite, const float offset_x, const float offset_y, const float width, const float height) {
  this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}
