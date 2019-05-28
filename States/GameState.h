#ifndef __GAME_STATES_H__
#define __GAME_STATES_H__

#include "../include/State.h"

class GameState : public State {

public:
  GameState(sf::RenderWindow* window);
  virtual ~GameState();

  // fucntions
  void endState();
  void updateKeybinds(const float& dt);
  void update(const float& dt);
  void render(sf::RenderTarget* target = nullptr);
};

#endif
