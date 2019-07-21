#ifndef __MAIN_MENU_STATE__H__
#define __MAIN_MENU_STATE__H__

#include "State.h"
#include "Gui.h"
#include "GameState.h"
#include "EditorState.h"
#include "SettingsState.h"
#include "GraphicsSettings.h"

class MainMenuState :
  public State {

 private:
  // Variables
  sf::Texture backgroundTexture;
  sf::RectangleShape background;
  sf::Font font;

  std::map<std::string, gui::Button*> buttons;

  // functions
  void initVariables();
  void initBackground();
  void initFonts();
  void initKeybinds();
  void initGui();
  void resetGui();

 public:
  MainMenuState(StateData* state_data);
  virtual ~MainMenuState();

  // fucntions
  void updateButtons();
  void updateInput(const float& dt);
  void update(const float& dt);
  void render(sf::RenderTarget* target = nullptr);
  void renderButtons(sf::RenderTarget& target);
};

#endif
