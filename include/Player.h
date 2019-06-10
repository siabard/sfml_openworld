#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"

class Player:
public Entity {
private:
  // variables


  // initializer function
  void initVariables();
  void initComponents();

public:
  Player(float, float, sf::Texture&);
  virtual ~Player();

  // functions
};

#endif
