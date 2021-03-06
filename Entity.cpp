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

  if(this->attributeComponent)
    delete this->attributeComponent;

  if(this->skillComponent)
    delete this->skillComponent;
}


void Entity::initVariables() {
  this->movementComponent = nullptr;
  this->animationComponent = nullptr;
  this->hitboxComponent = nullptr;
  this->attributeComponent = nullptr;
  this->skillComponent = nullptr;
}

void Entity::setTexture(sf::Texture& texture) {
  this->sprite.setTexture(texture);

}

void Entity::move(const float dir_x, const float dir_y, const float& dt) {
  if(this->movementComponent) {
    this->movementComponent->move(dir_x, dir_y, dt); // Sets velocity
  }

  if(this->skillComponent) {
    this->skillComponent->gainExp(SKILLS::ENDURANCE, 1);
    //std::cout << "SKILL::ENDURANCE :  " <<this->skillComponent->getSkill(SKILLS::ENDURANCE) << std::endl;
  }

}

void Entity::stopVelocity() {
  if(this->movementComponent) {
    this->movementComponent->stopVelocity();
  }
}
void Entity::stopVelocityX() {
  if(this->movementComponent) {
    this->movementComponent->stopVelocityX();
  }
}
void Entity::stopVelocityY() {
  if(this->movementComponent) {
    this->movementComponent->stopVelocityY();
  }
}

const sf::Vector2f& Entity::getPosition() const {
  if(this->hitboxComponent) {
    return this->hitboxComponent->getPosition();
  }

  return this->sprite.getPosition();
}

const sf::Vector2f Entity::getCenter() const {
  if(this->hitboxComponent) {
    return this->hitboxComponent->getPosition() +
      sf::Vector2f(this->hitboxComponent->getGlobalBounds().width / 2.f,
                   this->hitboxComponent->getGlobalBounds().height / 2.f
                   );
  }

  return this->sprite.getPosition() +
    sf::Vector2f(
                 this->sprite.getGlobalBounds().width / 2.f,
                 this->sprite.getGlobalBounds().height / 2.f
                 );
}

const sf::FloatRect Entity::getGlobalBounds() const {
  if (this->hitboxComponent) {
    return this->hitboxComponent->getGlobalBounds();
  }

  return this->sprite.getGlobalBounds();
}

const sf::Vector2i Entity::getGridPosition(const int gridSizeI) const {
  if (this->hitboxComponent)
    return sf::Vector2i(static_cast<int>(this->hitboxComponent->getPosition().x) / gridSizeI,
                        static_cast<int>(this->hitboxComponent->getPosition().y) / gridSizeI
                        );


  return sf::Vector2i(static_cast<int>(this->sprite.getPosition().x) / gridSizeI,
                      static_cast<int>(this->sprite.getPosition().y) / gridSizeI
                      );

}

const sf::FloatRect Entity::getNextPositionBounds(const float& dt) const {
  if(this->hitboxComponent && this->movementComponent) {
    return this->hitboxComponent->getNextPosition(this->movementComponent->getVelocity() * dt);
  }

  return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
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

void Entity::createAttributeComponent(const unsigned level) {
  this->attributeComponent = new AttributeComponent(level);
}

void Entity::createSkillComponent() {
  this->skillComponent = new SkillComponent();
}

// Calculations
const float Entity::getDistance(const Entity& point) const {
  // sqrt((x2-x1)^2 + (y2-y1)^2);

  return sqrt(pow(this->getCenter().x - point.getCenter().x, 2) + pow(this->getCenter().y - point.getCenter().y ,2));

}
