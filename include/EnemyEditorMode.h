#ifndef __ENEMYEDITORMODE_H__
#define __ENEMYEDITORMODE_H__

#include "EditorMode.h"
#include "EnemySpawner.h"

class EnemyEditorMode : public EditorMode {

private:
  EnemySpawner* enemySpawner;

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
