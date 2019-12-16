#include "include/stdafx.h"
#include "include/Weapon.h"


void Weapon::initVariables() {
  this->range = 20;
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

Weapon::~Weapon() {}

const unsigned Weapon::getRange() const {
  return this->range;
}
