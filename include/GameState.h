#ifndef __GAME_STATES_H__
#define __GAME_STATES_H__

#include "State.h"
#include "Entity.h"
#include "Player.h"
#include "PauseMenu.h"

class GameState : public State {

private:
  Player*  player;

protected:
  sf::Font font;
  PauseMenu* pmenu;

  // functions
  void initKeybinds();
  void initTextures();
  void initPlayers();
  void initFonts();
  void initPauseMenu();

public:
  GameState(sf::RenderWindow*,  std::map<std::string, int>*, std::stack<State*>*);
  virtual ~GameState();

  // functions
  void updateInput(const float& dt);
  void updatePlayerInput(const float& dt);
  void update(const float& dt);
  void updatePauseMenuButtons();
  void render(sf::RenderTarget* target = nullptr);
};

#endif
