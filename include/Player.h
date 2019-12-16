#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "AttributeComponent.h"
#include "Items.h"
#include "Inventory.h"

class Player :
  public Entity {
private:
  // variables
  bool attacking;
  Weapon* weapon;

  Inventory* inventory;

  // initializer function
  void initVariables();
  void initInventory();
  void initComponents();
  void initAnimation();

public:

  Player(float, float, sf::Texture&);
  virtual ~Player();

  // accessors
  AttributeComponent* getAttributeComponent();
  const Weapon* getWeapon() const;

  // functions
  void loseHP(const int hp);
  void gainHP(const int hp);
  void loseEXP(const int exp);
  void gainEXP(const int exp);
  void updateAttack();
  void updateAnimation(const float& dt);
  void update(const float& dt, sf::Vector2f& mouse_pos_view);
  void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false);

};

#endif
