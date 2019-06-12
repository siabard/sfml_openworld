#ifndef __GAME_STATES_H__
#define __GAME_STATES_H__

#include "State.h"
#include "Entity.h"
#include "Player.h"

class GameState : public State {

private:
  Player*  player;

protected:
  // functions
  void initKeybinds();
  void initTextures();
  void initPlayers();

public:
  GameState(sf::RenderWindow*,  std::map<std::string, int>*, std::stack<State*>*);
  virtual ~GameState();

  // fucntions
  void updateInput(const float& dt);
  void update(const float& dt);
  void render(sf::RenderTarget* target = nullptr);
};

#endif
