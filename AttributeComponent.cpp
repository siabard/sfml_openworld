#include "include/stdafx.h"
#include "include/AttributeComponent.h"

AttributeComponent::AttributeComponent(int level) {
  this->level = level;
  this->exp = 0;
  this->expNext = static_cast<int>( (50 / 3) * (pow(this->level + 1, 3) - 6 * pow(this->level + 1, 2) + ((this->level + 1 ) * 17) - 12));
  this->attributePoints = 2;

  this->vitality = 1;
  this->strength = 1;
  this->defence = 1;
  this->agility = 1;
  this->intelligence = 1;

  this->updateLevel();
  this->updateStats(true);
}


AttributeComponent::~AttributeComponent() {

}

// functions
std::string AttributeComponent::debugPrint() const {
  std::stringstream ss;

  ss << "Level: " << this->level << std::endl
     << "Exp: " << this->exp << std::endl
     << "Exp Next: " << this->expNext << std::endl
     << "Attp: " << this->attributePoints << std::endl;

  return ss.str();
}

void AttributeComponent::gainExp(const int exp) {
  this->exp += exp;
  this->updateLevel();
}

void AttributeComponent::updateStats(const bool reset) {
  this->hpMax = this->vitality * 9 + this->vitality + this->strength / 2 + this->intelligence / 5;
  this->damageMin = this->strength * 2 + this->strength / 4 + this->intelligence / 5;
  this->damageMax = this->strength * 2 + this->strength / 2 + this->intelligence / 5;
  this->accuracy = this->dexterity * 4 + this->dexterity / 3 + this->intelligence / 5;
  this->defence = this->agility * 2 + this->agility / 4 + this->intelligence / 5;
  this->luck = this->intelligence * 2 + this->intelligence / 5;

  if(reset) {
    this->hp = this->hpMax;
  }
}

void AttributeComponent::updateLevel() {
  while(this->exp >= this->expNext) {
    this->level++;
    this->exp -= this->expNext;
    this->expNext = static_cast<int>( (50 / 3) * (pow(this->level, 3) - 6 * pow(this->level, 2) + (this->level * 17) - 12));
    this->attributePoints++;
  }
}

void AttributeComponent::update() {
  this->updateLevel();
}
