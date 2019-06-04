#ifndef __MAIN_MENU_STATE__H__
#define __MAIN_MENU_STATE__H__

#include "../include/State.h"
#include "../Resource/Button.h"

class MainMenuState :
  public State {

 private:
  // Variables
  sf::RectangleShape background;
  sf::Font font;

  Button* gamestate_btn;

 protected:
  // functions
  void initFonts();
  void initKeybinds();

 public:
  MainMenuState(sf::RenderWindow*,  std::map<std::string, int>*);
  virtual ~MainMenuState();

  // fucntions
  void endState();
  void updateInput(const float& dt);
  void update(const float& dt);
  void render(sf::RenderTarget* target = nullptr);
};

#endif
