#ifndef __EDITOR_STATE_H__
#define __EDITOR_STATE_H__

#include "State.h"
#include "Gui.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "GraphicsSettings.h"

/*
 * forward declaration
 */

class State;
class Gui;
class PauseMenu;
class TileMap;
class GraphicsSettings;

class EditorState
  : public State {
 public:

private:
  // Variables
  sf::Font font;
  sf::Text cursorText;
  PauseMenu* pmenu;
  std::map<std::string, gui::Button*> buttons;

  TileMap* tileMap;

  sf::RectangleShape sidebar;

  sf::IntRect textureRect;
  sf::RectangleShape selectorRect;
  gui::TextureSelector* textureSelector;

  // functions
  void initVariables();
  void initBackground();
  void initFonts();
  void initText();
  void initKeybinds();
  void initPauseMenu();
  void initButtons();
  void initGui();
  void initTileMap();

public:
  EditorState(StateData* state_data);
  virtual ~EditorState();

  // fucntions
  void updateButtons();
  void updateInput(const float& dt);
  void updateEditorInput(const float& dt);
  void updatePauseMenuButtons();
  void updateGui(const float& dt);
  void update(const float& dt);
  void render(sf::RenderTarget* target = nullptr);
  void renderGui(sf::RenderTarget& target);
  void renderButtons(sf::RenderTarget& target);

};

#endif
