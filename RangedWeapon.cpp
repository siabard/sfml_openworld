#include "include/stdafx.h"
#include "include/RangedWeapon.h"

RangedWeapon::RangedWeapon(unsigned value, std::string texture_file) : Weapon(value, texture_file){
  this->type = ItemTypes::ITRANGEDWEAPON;
}

RangedWeapon::~RangedWeapon() {

}
