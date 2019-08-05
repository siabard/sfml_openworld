#include "include/stdafx.h"
#include "include/EnemyEditorMode.h"

EnemyEditorMode::EnemyEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data)
  : EditorMode(state_data, tile_map, editor_state_data) {

}


EnemyEditorMode::~EnemyEditorMode() {}


// functions
void EnemyEditorMode::updateInput(const float& dt) {
}

void EnemyEditorMode::updateGui(const float& dt) {
}

void EnemyEditorMode::update(const float& dt) {
}

void EnemyEditorMode::render(sf::RenderTarget& target) {
}

void EnemyEditorMode::renderGui(sf::RenderTarget& target) {
}
