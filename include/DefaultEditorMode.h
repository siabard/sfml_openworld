#ifndef __DEFAULTMODE_H__
#define __DEFAULTMODE_H__

#include "EditorMode.h"

class DefaultEditorMode :
  public EditorMode {
private:

  sf::Text cursorText;
  sf::RectangleShape sidebar;
  sf::RectangleShape selectorRect;
  gui::TextureSelector* textureSelector;
  sf::IntRect textureRect;
  bool collision;
  short type;
  int layer;
  bool tileAddLock;

public:
  DefaultEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
  virtual ~DefaultEditorMode();

  void initVariables();
  void initGui();
  void initText();

  void updateInput(const float& dt);
  void updateGui(const float& dt);
  void update(const float& dt);

  void render(sf::RenderTarget* target = nullptr) ;
  void renderGui(sf::RenderTarget& target);
};

#endif
