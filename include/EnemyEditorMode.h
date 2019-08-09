#ifndef __ENEMYEDITORMODE_H__
#define __ENEMYEDITORMODE_H__

#include "EditorMode.h"
#include "EnemySpawnerTile.h"

class EnemyEditorMode : public EditorMode {

private:
  sf::Text cursorText;
  sf::RectangleShape sidebar;
  sf::RectangleShape selectorRect;
  sf::IntRect textureRect;

  int type;
  int amount;
  int timeToSpawn;
  float maxDistance;

  void initGui();
  void initVariables();

public:
  EnemyEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
  virtual ~EnemyEditorMode();

  // functions
  void updateInput(const float& dt) ;
  void updateGui(const float& dt) ;
  void update(const float& dt) ;

  void render(sf::RenderTarget& target);
  void renderGui(sf::RenderTarget& target);
};

#endif
