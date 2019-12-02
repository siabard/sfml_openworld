#ifndef __BOW_H__
#define __BOW_H__

#include "RangedWeapon.h"

class Bow : public RangedWeapon {

private:

public:

  Bow(unsigned value);
  virtual ~Bow();

  virtual Bow* clone();
};

#endif
