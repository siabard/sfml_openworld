#ifndef __RANGED_WEAPON_H__
#define __RANGED_WEAPON_H__

#include "Item.h"

class RangedWeapon : public Item {
public:
  RangedWeapon(unsigned value);
  virtual ~RangedWeapon();

  virtual RangedWeapon* clone() = 0;
};

#endif
