#include "include/stdafx.h"
#include "include/Weapon.h"


void Weapon::initVariables() {
  this->range = 30;
  this->damageMin = 1;
  this->damageMax = 2;

  // Timer
  this->attackTimer.restart();
  this->attackTimerMax = 500;
}

void Weapon::initCooldown() {
  this->cooldown = 0.f;
  this->cooldownMax = 10.f;
  this->cooldownIteration = 1.f;
}

Weapon::Weapon(unsigned value, std::string texture_file)
  : Item(value) {

  this->initVariables();
  // Visual Weapon
  if(!this->weapon_texture.loadFromFile(texture_file)) {
    std::cout << "ERROR::PLAYER::COULD NOT LOAD WEAPON TEXTURE::" << texture_file << std::endl;
  }

  this->weapon_sprite.setTexture(this->weapon_texture);


}

Weapon::Weapon(unsigned damageMin, unsigned damageMax, unsigned range, unsigned value, std::string texture_file) : Item(value), damageMin(damageMin), damageMax(damageMax), range(range) {
  this->initVariables();

  // Visual Weapon
  if(!this->weapon_texture.loadFromFile(texture_file)) {
    std::cout << "ERROR::PLAYER::COULD NOT LOAD WEAPON TEXTURE::" << texture_file << std::endl;
  }

  this->weapon_sprite.setTexture(this->weapon_texture);

}

Weapon::~Weapon() {}

const unsigned Weapon::getDamageMin() const {
  return this->damageMin;
}

const unsigned Weapon::getDamageMax() const {
  return this->damageMax;
}


const unsigned Weapon::getDamage() const {
  return rand() % (this->damageMax - this->damageMin + 1) + this->damageMin;
}

const unsigned Weapon::getRange() const {
  return this->range;
}

const bool Weapon::getAttackTimer() {
  if(this->attackTimer.getElapsedTime().asMilliseconds() >= this->attackTimerMax) {

    this->attackTimer.restart();
    return true;
  }

  return false;
}
