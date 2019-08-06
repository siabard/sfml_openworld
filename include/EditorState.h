#ifndef __EDITOR_STATE_H__
#define __EDITOR_STATE_H__

#include "State.h"
#include "Gui.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "GraphicsSettings.h"
#include "EditorMode.h"
#include "EditorModes.h"

/*
 * forward declaration
 */

class State;
class Gui;
class PauseMenu;
class TileMap;
class GraphicsSettings;

enum EditorModes {DEFAULT_EDITOR_MODE = 0, ENEMY_EDITOR_MODE};


class EditorState
  : public State {
 public:

private:
  // Variables
  EditorStateData editorStateData;
  sf::View view;
  float cameraSpeed;
  sf::Font font;
  PauseMenu* pmenu;

  std::map<std::string, gui::Button*> buttons;

  TileMap* tileMap;

  std::vector<EditorMode*> modes;
  unsigned activeMode;

  // functions

  void initVariables();
  void initEditorStateData();
  void initView();
  void initFonts();
  void initKeybinds();
  void initPauseMenu();
  void initButtons();
  void initGui();
  void initTileMap();
  void initModes();

public:
  EditorState(StateData* state_data);
  virtual ~EditorState();

  // fucntions
  void updateButtons();
  void updateInput(const float& dt);
  void updateEditorInput(const float& dt);
  void updatePauseMenuButtons();
  void updateModes(const float& dt);
  void updateGui(const float& dt);
  void update(const float& dt);
  void render(sf::RenderTarget* target = nullptr);
  void renderGui(sf::RenderTarget& target);
  void renderButtons(sf::RenderTarget& target);
  void renderModes(sf::RenderTarget& target);

};

#endif
