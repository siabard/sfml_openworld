#ifndef __RANGED_WEAPON_H__
#define __RANGED_WEAPON_H__

#include "Weapon.h"

class RangedWeapon : public Weapon {
private:

protected:

public:
  RangedWeapon(unsigned value, std::string texture_file);
  virtual ~RangedWeapon();

  virtual RangedWeapon* clone() = 0;

  virtual void update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center)  = 0;
  virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) = 0;
};

#endif
