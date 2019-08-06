#include "include/stdafx.h"
#include "include/EnemyEditorMode.h"

EnemyEditorMode::EnemyEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data)
  : EditorMode(state_data, tile_map, editor_state_data) {
  this->initVariables();
  this->initGui();
}


EnemyEditorMode::~EnemyEditorMode() {}


void EnemyEditorMode::initVariables() {
  this->type = 0;
  this->amount = 0;
  this->timeToSpawn = 60;
  this->maxDistance = 1000.f;
}


void EnemyEditorMode::initGui() {
  // Text
  this->cursorText.setFont(*this->editorStateData->font);
  this->cursorText.setFillColor(sf::Color::White);
  this->cursorText.setCharacterSize(12);
  this->cursorText.setPosition(this->editorStateData->mousePosView->x, this->editorStateData->mousePosView->y);


  // General GUI
  this->sidebar.setSize(sf::Vector2f(80.f, static_cast<float>(this->stateData->gfxSettings->resolution.height)));
  this->sidebar.setFillColor(sf::Color(50, 50, 50, 100));
  this->sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));
  this->sidebar.setOutlineThickness(1.f);

  this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));

  this->selectorRect.setFillColor(sf::Color(255, 255, 255, 150));
  this->selectorRect.setOutlineThickness(1.f);
  this->selectorRect.setOutlineColor(sf::Color::Green);
}

// functions
void EnemyEditorMode::updateInput(const float& dt) {
  // Add a Tile
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeytime()) {
    if(!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePosWindow))) {
      this->tileMap->addTile(TileTypes::ENEMYSPAWNER, this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0, this->textureRect, false);
    }
  } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeytime()) {
    // remove a tile
    if(!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePosWindow))) {
      this->tileMap->removeTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0, TileTypes::ENEMYSPAWNER);
    }
  }

}

void EnemyEditorMode::updateGui(const float& dt) {

  this->selectorRect.setPosition(this->editorStateData->mousePosGrid->x * this->stateData->gridSize, this->editorStateData->mousePosGrid->y * this->stateData->gridSize);
  this->cursorText.setPosition(this->editorStateData->mousePosView->x + 100, this->editorStateData->mousePosView->y - 50);

  std::stringstream ss;
  ss
    << "Enemy Type: "  << this->type  << std::endl
    << "Enemy amount: " << this->amount  << std::endl
    << "Time to Spawn: " << this->timeToSpawn << std::endl
    << "Max Distance: " << this->maxDistance << std::endl
    ;
  this->cursorText.setString(ss.str());

}

void EnemyEditorMode::update(const float& dt) {
  this->updateInput(dt);
  this->updateGui(dt);
}

void EnemyEditorMode::render(sf::RenderTarget& target) {
  this->renderGui(target);
}

void EnemyEditorMode::renderGui(sf::RenderTarget& target) {
  target.setView(*this->editorStateData->view);
  target.draw(this->selectorRect);
  target.draw(this->cursorText);

  target.setView(target.getDefaultView());
  target.draw(this->sidebar);
}
