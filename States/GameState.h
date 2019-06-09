#ifndef __GAME_STATES_H__
#define __GAME_STATES_H__

#include "../include/State.h"
#include "../include/Entity.h"

class GameState : public State {

private:
  Entity player;

protected:
  // functions
  void initKeybinds();

public:
  GameState(sf::RenderWindow*,  std::map<std::string, int>*, std::stack<State*>*);
  virtual ~GameState();

  // fucntions
  void endState();
  void updateInput(const float& dt);
  void update(const float& dt);
  void render(sf::RenderTarget* target = nullptr);
};

#endif
