#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "AttributeComponent.h"

class Player :
  public Entity {
private:
  // variables
  bool attacking;

  // initializer function
  void initVariables();
  void initComponents();

public:

  Player(float, float, sf::Texture&);
  virtual ~Player();

  // accessors
  AttributeComponent* getAttributeComponent();

  // functions
  void loseHP(const int hp);
  void gainHP(const int hp);
  void loseEXP(const unsigned exp);
  void gainEXP(const unsigned exp);
  void updateAttack();
  void updateAnimation(const float& dt);
  void update(const float& dt);
  void render(sf::RenderTarget& target);

};

#endif
