#include "include/stdafx.h"
#include "include/Enemy.h"

void Enemy::initVariables() {
  this->gainExp = 10;
}

void Enemy::initAnimation() {}

Enemy::Enemy() {
  this->initVariables();
  this->initAnimation();
}

Enemy::~Enemy() {}

void Enemy::loseHP(const int hp) {
  if (this->attributeComponent) {
    this->attributeComponent->loseHP(hp);
  }
}

const unsigned Enemy::getGainExp() const {
  return this->gainExp;
}

const bool Enemy::isDead() const {
  if(this->attributeComponent) {
    return this->attributeComponent->isDead();
  }

  return false;
}

const AttributeComponent* Enemy::getAttributeComp() {
  if (this->attributeComponent) {
    return this->attributeComponent;
  } else {
    std::cout << "ERROR::ENEMY::GETATTRIBUTECOMP::COMPONENT IS NOT INITIALIZED" << std::endl;
    return nullptr;
  }
}
