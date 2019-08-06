#ifndef __GAME_STATES_H__
#define __GAME_STATES_H__

#include "State.h"
#include "Entity.h"
#include "Player.h"
#include "Enemies_include.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGUI.h"
#include "Swoard.h"
#include "Bow.h"

class PauseMenu;
class Player;
class TileMap;
class GraphicsSettings;

class GameState : public State {

private:
  sf::View view;
  sf::Vector2i viewGridPosition;
  sf::RenderTexture renderTexture;
  sf::Sprite renderSprite;

  Player*  player;
  PlayerGUI* playerGUI;
  sf::Texture texture;

  TileMap* tileMap;

  sf::Font font;
  PauseMenu* pmenu;

  sf::Shader core_shader;

  std::vector<Enemy*> activeEnemies;

  // functions
  void initDeferredRender();
  void initView();
  void initKeybinds();
  void initTextures();
  void initPlayers();
  void initPlayerGUI();
  void initFonts();
  void initPauseMenu();
  void initShaders();
  void initTileMap();

public:
  GameState(StateData* state_date);
  virtual ~GameState();

  // functions
  void updateView(const float& dt);
  void updateInput(const float& dt);
  void updatePlayerInput(const float& dt);
  void updatePlayerGUI(const float& dt);
  void update(const float& dt);
  void updateTileMap(const float& dt);
  void updatePauseMenuButtons();
  void render(sf::RenderTarget* target = nullptr);
};

#endif
