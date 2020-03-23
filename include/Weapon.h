#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "Item.h"

class Weapon : public Item {
private:
  void initVariables();
  void initCooldown();

protected:
  sf::Sprite weapon_sprite;
  sf::Texture weapon_texture;

  unsigned damageMin;
  unsigned damageMax;
  unsigned range;

  float cooldown;
  float cooldownMax;
  float cooldownIteration;

  sf::Clock attackTimer;
  sf::Int32 attackTimerMax;

public:
  Weapon(unsigned level, unsigned value, std::string texture_file);
  Weapon(unsigned level, unsigned damageMin, unsigned damageMax, unsigned range, unsigned value, std::string texture_file);
  virtual ~Weapon();

  // accessors
  const unsigned getRange() const;
  const unsigned getDamageMin() const;
  const unsigned getDamage() const;
  const unsigned getDamageMax() const;

  const bool getAttackTimer();

  // functions
  virtual void update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center)  = 0;
  virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) = 0;


  virtual Weapon* clone() = 0;
  virtual void generate(const unsigned levelMin, const unsigned levelMax) = 0;
};

#endif
