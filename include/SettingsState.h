#ifndef __SETTINGS_STATE_H__
#define __SETTINGS_STATE_H__

#include "State.h"
#include "Gui.h"
#include "GraphicsSettings.h"

class SettingsState : public State {

private:
  // Variables
  GraphicsSettings& gfxSettings;
  sf::Texture backgroundTexture;
  sf::RectangleShape background;
  sf::Font font;

  std::map<std::string, gui::Button*> buttons;
  std::map<std::string, gui::DropDownList*> dropdownLists;

  sf::Text optionsText;
  std::vector<sf::VideoMode> modes;

  // functions
  void initVariables();
  void initBackground();
  void initFonts();
  void initKeybinds();
  void initGui();
  void initText();

public:
  SettingsState(sf::RenderWindow* window, GraphicsSettings& gfxSettings, std::map<std::string, int>* supportedKeys, std::stack<State*>*  states);
  virtual ~SettingsState();

  // Accessors


  // functions
  void updateGui(const float& dt);
  void updateInput(const float& dt);
  void update(const float& dt);
  void render(sf::RenderTarget* target = nullptr);
  void renderGui(sf::RenderTarget& target);
};

#endif
