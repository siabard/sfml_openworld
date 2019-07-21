#include "include/stdafx.h"
#include "include/GameState.h"

// Initiaizlier function
void GameState::initDeferredRender() {
  this->renderTexture.create(this->stateData->gfxSettings->resolution.width,
                             this->stateData->gfxSettings->resolution.height
                             );

  this->renderSprite.setTexture(this->renderTexture.getTexture());
  this->renderSprite.setTextureRect(sf::IntRect(0,
                                                0,
                                                this->stateData->gfxSettings->resolution.width,
                                                this->stateData->gfxSettings->resolution.height
                                                ));
}

void GameState::initView() {
  this->view.setSize(sf::Vector2f(
                                  static_cast<float>(this->stateData->gfxSettings->resolution.width),
                                  static_cast<float>(this->stateData->gfxSettings->resolution.height)
                                  ));

  this->view.setCenter(sf::Vector2f(
                                    static_cast<float>(this->stateData->gfxSettings->resolution.width) / 2.f,
                                    static_cast<float>(this->stateData->gfxSettings->resolution.height) / 2.f
                                  ));

}

void GameState::initKeybinds() {
  std::ifstream ifs("config/gamestate_keybinds.ini");
  if(ifs.is_open()) {
    std::string key = "";
    std::string key_binding = "";
    while(ifs >> key_binding >> key) {
      this->keybinds[key_binding] = this->supportedKeys->at(key);
    }
  } else {
    std::cout << "file not exist: gamestate_keybinds.ini" << std::endl;
  }
  ifs.close();
}

void GameState::initTextures() {
  if(!this->textures["PLAYER_SHEET"].loadFromFile("Resource/images/sprites/player/player_sheet.png")) {
    throw "GAMESTATE::PLAYER_SHEET::CANNOT_LOAD_PLAYER_SHEET";
  }

}


void GameState::initPauseMenu() {
  const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
  this->pmenu = new PauseMenu(vm, this->font);

  this->pmenu->addButton("QUIT", gui::p2pY(74.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Quit");

}

void GameState::initPlayers() {
  this->player = new Player(0, 0, this->textures["PLAYER_SHEET"]);

}

void GameState::initPlayerGUI() {
  this->playerGUI = new PlayerGUI(this->player);
}

void GameState::initFonts() {
  if(!this->font.loadFromFile("fonts/DroidSans.ttf")) {
    throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
  }

}

void GameState::initTileMap() {
  this->tileMap = new TileMap( this->stateData->gridSize, 100, 100, "Resource/images/tiles/tilesheet1.png");
  this->tileMap->loadFromFile("text.slmp");
}

// Constructor
GameState::GameState(StateData* state_data) : State(state_data) {
  this->initDeferredRender();
  this->initView();
  this->initKeybinds();
  this->initFonts();
  this->initTextures();
  this->initPauseMenu();
  this->initPlayers();
  this->initPlayerGUI();
  this->initTileMap();
}

GameState::~GameState() {
  if(this->playerGUI) {
    delete this->playerGUI;
  }
  if(this->player) {
    delete this->player;
  }


  delete this->pmenu;

  delete this->tileMap;
}

// functions
void GameState::updateView(const float& dt) {
  this->view.setCenter( std::floor(this->player->getPosition().x), std::floor(this->player->getPosition().y));
}

void GameState::update(const float& dt) {
  this->updateMousePositions(&this->view);
  this->updateInput(dt);
  this->updateKeytime(dt);

  if(!this->paused) {
    // Unpaused update
    this->updateView(dt);
    this->updatePlayerInput(dt);
    this->updateTileMap(dt);
    this->player->update(dt);
    this->playerGUI->update(dt);
  } else {
    // paused update
    this->pmenu->update(this->mousePosWindow);
    this->updatePauseMenuButtons();

  }
}


void GameState::updateInput(const float& dt) {
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime()) {
    if(!this->paused)
      this->pauseState();
    else
      this->unpauseState();
  }
}

void GameState::updatePlayerGUI(const float& dt) {
  this->playerGUI->update(dt);
}

void GameState::updatePlayerInput(const float& dt) {
  // Update player input
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
    this->player->move(-1.f, 0.f, dt);

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
    this->player->move(1.f, 0.f, dt);

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP")))) {
    if(this->getKeytime())
      this->player->gainEXP(10);
    this->player->move(0.f, -1.f, dt);
  }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN")))) {
    this->player->move(0.f, 1.f, dt);
    if(this->getKeytime())
      this->player->loseEXP(10);
  }

}

void GameState::updateTileMap(const float& dt) {
  this->tileMap->update();
  this->tileMap->updateCollision(this->player, dt);
}

void GameState::updatePauseMenuButtons() {
  if(this->pmenu->isButtonPressed("QUIT"))
    this->endState();
}

void GameState::render(sf::RenderTarget* target) {
  if(!target)
    target = this->window;

  this->renderTexture.clear();
  this->renderTexture.setView(this->view);
  this->tileMap->render(this->renderTexture, this->player->getGridPosition(static_cast<int>(this->stateData->gridSize)));
  this->player->render(this->renderTexture);
  this->tileMap->renderDeferred(this->renderTexture);

  // Render GUI
  this->renderTexture.setView(this->renderTexture.getDefaultView());
  this->playerGUI->render(this->renderTexture);

  if (this->paused) {
    // Pause menu render
    // this->renderTexture.setView(this->renderTexture.getDefaultView());
    this->pmenu->render(this->renderTexture);
  }

  // Final Renderer
  this->renderTexture.display();
  this->renderSprite.setTexture(this->renderTexture.getTexture());
  target->draw(this->renderSprite);
}
