#include "include/Entity.h"


Entity::Entity() {
  this->initVariables();


}

Entity::~Entity() {

}


void Entity::initVariables() {
  this->texture = nullptr;
  this->movementComponent = nullptr;
}

void Entity::setTexture(sf::Texture& texture) {

  this->texture = &texture;
  this->sprite.setTexture(*this->texture);

}

void Entity::move(const float& dt, const float dir_x, const float dir_y) {
  if(this->movementComponent) {
    this->movementComponent->move(dir_x, dir_y, dt); // Sets velocity
  }
}

void Entity::update(const float& dt) {

}
void Entity::render(sf::RenderTarget* target) {
    target->draw(this->sprite);
}


void Entity::setPosition(const float x, const float y) {
  this->sprite.setPosition(x, y);
}

void Entity::createMovementComponent(const float maxVelocity) {
  this->movementComponent = new MovementComponent(this->sprite, maxVelocity);
}
