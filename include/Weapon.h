#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "Item.h"

class Weapon : public Item {
private:
  void initVariables();

protected:
  sf::Sprite weapon_sprite;
  sf::Texture weapon_texture;

  int damageMin;
  int damageMax;
  unsigned range;

public:
  Weapon(unsigned value, std::string texture_file);
  virtual ~Weapon();

  // accessors
  const unsigned getRange() const;
  // functions
  virtual void update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center)  = 0;
  virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) = 0;


  virtual Weapon* clone() = 0;
};

#endif
