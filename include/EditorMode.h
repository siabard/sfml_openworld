#ifndef __EDITORMODE_H__
#define __EDITORMODE_H__

#include "State.h"
#include "TileMap.h"
#include "Gui.h"

class EditorStateData {
public:
  EditorStateData() {}

  // Variables
  sf::View* view;

  sf::Font* font;

  float* keytime;
  float* keytimeMax;
  std::map<std::string, int>* keybinds;

  sf::Vector2i* mousePosScreen;
  sf::Vector2i* mousePosWindow;
  sf::Vector2f* mousePosView;
  sf::Vector2i* mousePosGrid;
};


class EditorMode {
protected:
  StateData* stateData;
  TileMap* tileMap;
  EditorStateData* editorStateData;

  sf::Font* font;

public:
  EditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
  virtual ~EditorMode();

  // functions
  const bool getKeytime();
  virtual void updateInput(const float& dt) = 0;
  virtual void updateGui(const float& dt) = 0;
  virtual void update(const float& dt) = 0;

  virtual void render(sf::RenderTarget* target = nullptr) = 0;
  virtual void renderGui(sf::RenderTarget& target) = 0;
};

#endif
