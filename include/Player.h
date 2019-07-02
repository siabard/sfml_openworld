#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"

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

  // functions
  void updateAttack();
  void updateAnimation(const float& dt);
  void update(const float& dt);
  void render(sf::RenderTarget& target);

};

#endif
