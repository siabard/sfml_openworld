#include "include/stdafx.h"
#include "include/Enemy.h"

Enemy::Enemy() {

}

Enemy::~Enemy() {}

void Enemy::loseHP(const int hp) {
  if (this->attributeComponent) {
    this->attributeComponent->loseHP(hp);
  }
}

const AttributeComponent* Enemy::getAttributeComp() {
  if (this->attributeComponent) {
    return this->attributeComponent;
  } else {
    std::cout << "ERROR::ENEMY::GETATTRIBUTECOMP::COMPONENT IS NOT INITIALIZED" << std::endl;
    return nullptr;
  }
}
