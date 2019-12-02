#include "include/stdafx.h"
#include "include/MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(unsigned value) : Item(value) {
  this->type = ItemTypes::ITMELEEWEAPON;
}

MeleeWeapon::~MeleeWeapon() {}
