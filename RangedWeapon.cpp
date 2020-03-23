#include "include/stdafx.h"
#include "include/RangedWeapon.h"

RangedWeapon::RangedWeapon(unsigned level, unsigned value, std::string texture_file)
  : Weapon(level, value, texture_file){
  this->type = ItemTypes::ITRANGEDWEAPON;
}

RangedWeapon::~RangedWeapon() {

}

void RangedWeapon::generate(const unsigned int levelMin, const unsigned int levelMax) {

}
