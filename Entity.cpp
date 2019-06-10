#include "include/Entity.h"


Entity::Entity() {
  this->initVariables();


}

Entity::~Entity() {
  if(this->sprite)
    delete this->sprite;


}


void Entity::initVariables() {
  this->texture = nullptr;
  this->sprite = nullptr;
  this->movementComponent = nullptr;
}

void Entity::createSprite(sf::Texture* texture) {
  std::cout << "ENTITY::CREATESPRITE start" << std::endl;
  this->texture = texture;
  this->sprite = new sf::Sprite(*this->texture);
  //this->sprite->setTexture(*this->texture);
  std::cout << "ENTITY::CREATESPRITE end" << std::endl;
}

void Entity::move(const float& dt, const float dir_x, const float dir_y) {
  if(this->sprite && this->movementComponent) {
    this->movementComponent->move(dir_x, dir_y); // Sets velocity
    this->sprite->move(this->movementComponent->getVelocity() * dt); // Uses velocity
  }
}

void Entity::update(const float& dt) {

}
void Entity::render(sf::RenderTarget* target) {
  if(this->sprite)
    target->draw(*this->sprite);
}


void Entity::setPosition(const float x, const float y) {
  if(this->sprite) {
    this->sprite->setPosition(x, y);
  }
}

void Entity::createMovementComponent(const float maxVelocity) {
  this->movementComponent = new MovementComponent(maxVelocity);
}
