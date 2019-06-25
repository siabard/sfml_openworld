#ifndef __EDITOR_STATE_H__
#define __EDITOR_STATE_H__

#include "State.h"
#include "Gui.h"
#include "PauseMenu.h"
#include "TileMap.h"

/*
 * forward declaration
 */

class State;
class Gui;
class PauseMenu;
class TileMap;

class EditorState
  : public State {
 public:

private:
  // Variables
  sf::Font font;
  PauseMenu* pmenu;
  std::map<std::string, gui::Button*> buttons;

  TileMap map;

protected:
  // functions
  void initVariables();
  void initBackground();
  void initFonts();
  void initKeybinds();
  void initPauseMenu();
  void initButtons();

public:
  EditorState(StateData* state_data);
  virtual ~EditorState();

  // fucntions
  void updateButtons();
  void updateInput(const float& dt);
  void updatePauseMenuButtons();
  void update(const float& dt);
  void render(sf::RenderTarget* target = nullptr);
  void renderButtons(sf::RenderTarget& target);

};

#endif
