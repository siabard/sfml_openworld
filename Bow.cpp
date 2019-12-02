#include "include/stdafx.h"
#include "include/Bow.h"

Bow::Bow(unsigned value) : RangedWeapon(value) {}

Bow::~Bow() {}

Bow* Bow::clone() {
  return new Bow(*this);
}
