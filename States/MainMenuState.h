#ifndef __MAIN_MENU_STATE__H__
#define __MAIN_MENU_STATE__H__

#include "../include/State.h"
#include "../Resource/Button.h"
#include "GameState.h"
#include <exception>

class MainMenuState :
  public State {

 private:
  // Variables
  sf::Texture backgroundTexture;
  sf::RectangleShape background;
  sf::Font font;

  std::map<std::string, Button*> buttons;

 protected:
  // functions
  void initVariables();
  void initBackground();
  void initFonts();
  void initKeybinds();
  void initButtons();

 public:
  MainMenuState(sf::RenderWindow*,  std::map<std::string, int>*, std::stack<State*>*);
  virtual ~MainMenuState();

  // fucntions
  void endState();
  void updateButtons();
  void updateInput(const float& dt);
  void update(const float& dt);
  void render(sf::RenderTarget* target = nullptr);
  void renderButtons(sf::RenderTarget* target = nullptr);
};

#endif
