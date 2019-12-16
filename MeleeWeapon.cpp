#include "include/stdafx.h"
#include "include/MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(unsigned value, std::string texture_file) : Weapon(value, texture_file) {
  this->type = ItemTypes::ITMELEEWEAPON;
}

MeleeWeapon::~MeleeWeapon() {}
