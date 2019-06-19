#ifndef __SETTINGS_STATE_H__
#define __SETTINGS_STATE_H__

#include "State.h"
#include "Gui.h"
#include <map>

class SettingsState : public State {

private:
  // Variables
  sf::Texture backgroundTexture;
  sf::RectangleShape background;
  sf::Font font;

  std::map<std::string, gui::Button*> buttons;

  gui::DropDownList* ddl;

  // functions
  void initVariables();
  void initBackground();
  void initFonts();
  void initKeybinds();
  void initButtons();

public:
  SettingsState(sf::RenderWindow* window,  std::map<std::string, int>* supportedKeys, std::stack<State*>*  states);
  virtual ~SettingsState();

  // Accessors


  // functions
  void updateButtons();
  void updateInput(const float& dt);
  void update(const float& dt);
  void render(sf::RenderTarget* target = nullptr);
  void renderButtons(sf::RenderTarget& target);
};

#endif
