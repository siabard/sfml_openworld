#include "include/stdafx.h"
#include "include/RangedWeapon.h"

RangedWeapon::RangedWeapon(unsigned value) : Item(value){
  this->type = ItemTypes::ITRANGEDWEAPON;
}

RangedWeapon::~RangedWeapon() {

}
