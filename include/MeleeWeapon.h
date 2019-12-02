#ifndef __MELEE_WEAPON_H__
#define __MELEE_WEAPON_H__

#include "Item.h"

class MeleeWeapon : public Item {

private:

protected:
  sf::Sprite weapon_sprite;
  sf::Texture weapon_texture;

  int damageMin;
  int damageMax;

public:
  MeleeWeapon(unsigned value);
  virtual ~MeleeWeapon();

  virtual void update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center) = 0;
  virtual void render(sf::RenderTarget& target, sf::Shader* shader) = 0;

  virtual MeleeWeapon* clone() = 0;
};

#endif
