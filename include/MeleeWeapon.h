#ifndef __MELEE_WEAPON_H__
#define __MELEE_WEAPON_H__

#include "Weapon.h"

class MeleeWeapon : public Weapon {

private:

protected:

public:
  MeleeWeapon(unsigned damageMin, unsigned damageMax, unsigned range, unsigned value, std::string texture_file);

  virtual ~MeleeWeapon();

  virtual MeleeWeapon* clone() = 0;

  virtual void update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center)  = 0;
  virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) = 0;
};

#endif
